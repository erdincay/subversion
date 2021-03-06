/*
 * translate-test.c -- test the eol and keyword translation subroutine
 *
 * ====================================================================
 * Copyright (c) 2000-2002 CollabNet.  All rights reserved.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at http://subversion.tigris.org/license-1.html.
 * If newer versions of this license are posted there, you may use a
 * newer version instead, at your option.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://subversion.tigris.org/.
 * ====================================================================
 */



/* Advice to those adding new tests to this file: 
 * ==============================================
 *
 * Read the doc string for substitute_and_verify(), then read the
 * test functions themselves -- they're small, and they'll be very
 * easy to understand once you know substitute_and_verify().
 */



#include <stdio.h>
#include <string.h>
#include <apr_general.h>
#include <apr_file_io.h>
#include <apr_time.h>
#include <svn_wc.h>
#include "svn_test.h"



/*** Helpers ***/

/* (Almost) all the tests share the same test data. */
const char *lines[] =
  {
    "Line 1: fairly boring subst test data... blah blah",
    "Line 2: fairly boring subst test data... blah blah.",
    "Line 3: Valid $LastChangedRevision$, started unexpanded.",
    "Line 4: fairly boring subst test data... blah blah.",
    "Line 5: Valid $Rev$, started unexpanded.",
    "Line 6: fairly boring subst test data... blah blah.",
    "Line 7: fairly boring subst test data... blah blah.",
    "Line 8: Valid $LastChangedBy$, started unexpanded.",
    "Line 9: Valid $Author$, started unexpanded.",
    "Line 10: fairly boring subst test data... blah blah.",
    "Line 11: fairly boring subst test data... blah blah.",
    "Line 12: Valid $LastChangedDate$, started unexpanded.",
    "Line 13: Valid $Date$, started unexpanded.",
    "Line 14: fairly boring subst test data... blah blah.",
    "Line 15: fairly boring subst test data... blah blah.",
    "Line 16: Valid $HeadURL$, started unexpanded.",
    "Line 17: Valid $URL$, started unexpanded.",
    "Line 18: fairly boring subst test data... blah blah.",
    "Line 19: Invalid expanded keyword spanning two lines: $Author: ",
    /* The idea here is that, were it not broken across two lines,
       "$Author: Line 20: jrandom$" would be a valid if odd, keyword. */ 
    "Line 20: jrandom$ remainder of invalid keyword spanning two lines.",
    "Line 21: fairly boring subst test data... blah blah.",
    "Line 22: an unknown keyword $LastChangedSocks$.",
    "Line 23: fairly boring subst test data... blah blah.",
    /* In line 24, the third dollar sign terminates the first, and the
       fourth should therefore remain a literal dollar sign. */
    "Line 24: keyword in a keyword: $Author: $Date$ $",
    "Line 25: fairly boring subst test data... blah blah.",
    "Line 26: Emptily expanded keyword $Rev: $.",
    "Line 27: fairly boring subst test data... blah blah.",
    "Line 28: fairly boring subst test data... blah blah.",
    "Line 29: Valid $LastChangedRevision: 1729 $, started expanded.",
    "Line 30: Valid $Rev: 1729 $, started expanded.",
    "Line 31: fairly boring subst test data... blah blah.",
    "Line 32: fairly boring subst test data... blah blah.",
    "Line 33: Valid $LastChangedDate: 2002-01-01 $, started expanded.",
    "Line 34: Valid $Date: 2002-01-01 $, started expanded.",
    "Line 35: fairly boring subst test data... blah blah.",
    "Line 36: fairly boring subst test data... blah blah.",
    "Line 37: Valid $LastChangedBy: jrandom $, started expanded.",
    "Line 38: Valid $Author: jrandom $, started expanded.",
    "Line 39: fairly boring subst test data... blah blah.",
    "Line 40: fairly boring subst test data... blah blah.",
    "Line 41: Valid $HeadURL: http://tomato/mauve $, started expanded.",
    "Line 42: Valid $URL: http://tomato/mauve $, started expanded.",
    "Line 43: fairly boring subst test data... blah blah.",
    "Line 44: fairly boring subst test data... blah blah.",
    "Line 45: Invalid $LastChangedRevisionWithSuffix$, started unexpanded.",
    "Line 46: Invalid $Rev:$ is missing a space.",
    "Line 47: fairly boring subst test data... blah blah.",
    "Line 48: Two keywords back to back: $Author$$Rev$.",
    "Line 49: One keyword, one not, back to back: $Author$Rev$.",
    "Line 50: a series of dollar signs $$$$$$$$$$$$$$$$$$$$$$$$$$$$.",
    "Line 51: same, but with embedded keyword $$$$$$$$Date$$$$$$$$$$.",
    "Line 52: same, with expanded, empty keyword $$$$$$Date: $$$$$$.",
    "", /* Lines 53-69 are blank to test consecutive newlines */
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "Line 70: end of subst test data."
  };


/* Return a randomly selected eol sequence. */
static const char *
random_eol_marker (void)
{
  /* Select a random eol marker from this set. */
  static int seeded = 0;

  /* ### todo: allowing '\r' to be in this list of possible random
     eol_markers causes problems for the current testing framework
     which expects a 1:1 ratio of input-line-count to output-line-count.  
     Problems occur when there are two consecutive line ending markers
     where the first is '\r' and the second is '\n' -- our
     translation routine reads that as a single '\r\n' which throws
     off the linecount on the output side, and fouls up substitute_and_verify.
  */
  const char *eol_markers[] = { "\n", "\r\n" };

  if (! seeded)
    {
      srand (1729);  /* we want errors to be reproducible */
      seeded = 1;
    }

  return eol_markers[rand()
                     % ((sizeof (eol_markers)) / (sizeof (*eol_markers)))];
}


/* Create FNAME with global `lines' as initial data.  Use EOL_STR as
 * the end-of-line marker between lines, or if EOL_STR is NULL, choose
 * a random marker at each opportunity.  Use POOL for any temporary
 * allocation.
 */
static svn_error_t *
create_file (const char *fname, const char *eol_str, apr_pool_t *pool)
{
  apr_status_t apr_err;
  apr_file_t *f;
  int i, j;

  apr_err = apr_file_open (&f, fname,
                           (APR_WRITE | APR_CREATE | APR_EXCL | APR_BINARY),
                           APR_OS_DEFAULT, pool);
  if (! APR_STATUS_IS_SUCCESS (apr_err))
    return svn_error_create (apr_err, 0, NULL, pool, fname);
  
  for (i = 0; i < (sizeof (lines) / sizeof (*lines)); i++)
    {
      const char *this_eol_str = eol_str ? eol_str : random_eol_marker ();
          
      apr_err = apr_file_printf (f, lines[i]);

      /* Is it overly paranoid to use putc(), because of worry about
         fprintf() doing a newline conversion? */ 
      for (j = 0; this_eol_str[j]; j++)
        {
          apr_err = apr_file_putc (this_eol_str[j], f);
          if (! APR_STATUS_IS_SUCCESS (apr_err))
            return svn_error_create (apr_err, 0, NULL, pool, fname);
        }
    }

  apr_err = apr_file_close (f);
  if (! APR_STATUS_IS_SUCCESS (apr_err))
    return svn_error_create (apr_err, 0, NULL, pool, fname);
  
  return SVN_NO_ERROR;
}


/* If FNAME is a regular file, remove it; if it doesn't exist at all,
   return success.  Otherwise, return error. */
static svn_error_t *
remove_file (const char *fname, apr_pool_t *pool)
{
  apr_status_t apr_err;
  apr_finfo_t finfo;

  if (APR_STATUS_IS_SUCCESS (apr_stat (&finfo, fname, APR_FINFO_TYPE, pool)))
    {
      if (finfo.filetype == APR_REG)
        {
          apr_err = apr_file_remove (fname, pool);
          if (! APR_STATUS_IS_SUCCESS (apr_err))
            return svn_error_create (apr_err, 0, NULL, pool, fname);
        }
      else
        return svn_error_createf (SVN_ERR_TEST_FAILED, 0, NULL, pool,
                                  "non-file `%s' is in the way", fname);
    }

  return SVN_NO_ERROR;
}


/* Set up, run, and verify the results of a substitution.
 *
 * Create a file TEST_NAME.src using global `lines' as the initial
 * data, with SRC_EOL as the line separator, then convert it to file
 * TEST_NAME.dst (using DST_EOL, REPAIR, EXPAND, REV, AUTHOR, DATE,
 * and URL as svn_wc_copy_and_translate() does), and verify that the
 * conversion worked.  Null SRC_EOL means create a mixed eol src
 * file.
 *
 * If the verification succeeds, remove both files and return
 * SVN_NO_ERROR.
 * 
 * If the verification fails, leave the files for post-mortem.  If the
 * failure is due to non-eol data being wrong, return
 * SVN_ERR_MALFORMED_FILE.  If the problem is an incorrect eol marker,
 * return SVN_ERR_CORRUPT_EOL.  If the problem is that a mixed eol
 * style was repaired even though no repair flag was passed, return
 * SVN_ERR_TEST_FAILED.
 *
 * Use POOL for temporary allocation.
 *
 * Note: as with svn_wc_copy_and_translate(), if any of DST_EOL, REV,
 * AUTHOR, DATE, and/or URL is null, then that substitution is not
 * performed.
 */
static svn_error_t *
substitute_and_verify (const char *test_name,
                       const char *src_eol,
                       const char *dst_eol,
                       svn_boolean_t repair,
                       const char *rev,
                       const char *date,
                       const char *author,
                       const char *url,
                       svn_boolean_t expand,
                       apr_pool_t *pool)
{
  svn_error_t *err;
  svn_stringbuf_t *contents;
  svn_wc_keywords_t keywords;
  int idx = 0;
  int i;
  const char *expect[(sizeof (lines) / sizeof (*lines))];
  const char *src_fname = apr_pstrcat (pool, test_name, ".src", NULL);
  const char *dst_fname = apr_pstrcat (pool, test_name, ".dst", NULL);

  /** Clean up from previous tests, set up src data, and convert. **/
  SVN_ERR (remove_file (src_fname, pool));
  SVN_ERR (remove_file (dst_fname, pool));
  SVN_ERR (create_file (src_fname, src_eol, pool));

  keywords.revision = rev    ? svn_string_create (rev, pool)    : NULL;
  keywords.date     = date   ? svn_string_create (date, pool)   : NULL;
  keywords.author   = author ? svn_string_create (author, pool) : NULL;
  keywords.url      = url    ? svn_string_create (url, pool)    : NULL;

  err = svn_wc_copy_and_translate (src_fname, dst_fname, dst_eol, repair,
                                   &keywords, expand, pool);


  /* Conversion should have failed, if src has mixed eol, and the
     repair flag was not set, and we requested eol translation. */
  if ((! src_eol) && dst_eol && (! repair))
    {
      if (! err)
        {
          return svn_error_createf
            (SVN_ERR_TEST_FAILED, 0, NULL, pool,
             "translation of %s should have failed, but didn't", src_fname);
        }
      else if (err->apr_err != SVN_ERR_IO_INCONSISTENT_EOL)
        {
          char buf[1024];

          svn_strerror (err->apr_err, buf, sizeof (buf));

          return svn_error_createf
            (SVN_ERR_TEST_FAILED, 0, NULL, pool,
             "translation of %s should fail, but not with error \"%s\"",
             src_fname, buf);
        }
      else
        return SVN_NO_ERROR;

    }
  else if (err)
    return err;

      
  /** Verify that the conversion worked. **/

  for (i = 0; i < (sizeof (expect) / sizeof (*expect)); i++)
    expect[i] = lines[i];

  /* Certain lines contain keywords; expect their expansions. */
  if (rev)
    {
      if (expand)
        {
          expect[3 - 1] =
            apr_pstrcat (pool, "Line 3: ",
                         "Valid $LastChangedRevision: ",
                         rev,
                         " $, started unexpanded.",
                         NULL);
          expect[5 - 1] =
            apr_pstrcat (pool, "Line 5: ",
                         "Valid $Rev: ", rev, " $, started unexpanded.",
                         NULL);
          expect[26 - 1] =
            apr_pstrcat (pool, "Line 26: ",
                         "Emptily expanded keyword $Rev: ", rev," $.",
                         NULL);
          expect[29 - 1] =
            apr_pstrcat (pool, "Line 29: ",
                         "Valid $LastChangedRevision: ",
                         rev,
                         " $, started expanded.",
                         NULL);
          expect[30 - 1] =
            apr_pstrcat (pool, "Line 30: ",
                         "Valid $Rev: ",
                         rev,
                         " $, started expanded.",
                         NULL);
        }
      else  /* unexpand */
        {
          /* Lines 3 and 5 remain unchanged. */
          expect[26 - 1] = "Line 26: Emptily expanded keyword $Rev$.";
          expect[29 - 1] =
            "Line 29: Valid $LastChangedRevision$, started expanded.";
          expect[30 - 1] =
            "Line 30: Valid $Rev$, started expanded.";
        }
    }

  if (date)
    {
      if (expand)
        {
          expect[12 - 1] =
            apr_pstrcat (pool, "Line 12: ",
                         "Valid $LastChangedDate: ",
                         date,
                         " $, started unexpanded.",
                         NULL);
          expect[13 - 1] =
            apr_pstrcat (pool, "Line 13: ",
                         "Valid $Date: ", date, " $, started unexpanded.",
                         NULL);
          expect[33 - 1] =
            apr_pstrcat (pool, "Line 33: ",
                         "Valid $LastChangedDate: ",
                         date,
                         " $, started expanded.",
                         NULL);
          expect[34 - 1] =
            apr_pstrcat (pool, "Line 34: ",
                         "Valid $Date: ", date, " $, started expanded.",
                         NULL);
          expect[51 - 1] =
            apr_pstrcat (pool, "Line 51: ",
                         "same, but with embedded keyword ",
                         "$$$$$$$$Date: ", date, " $$$$$$$$$$.",
                         NULL);
          expect[52 - 1] =
            apr_pstrcat (pool, "Line 52: ",
                         "same, with expanded, empty keyword ",
                         "$$$$$$Date: ", date, " $$$$$$.",
                         NULL);
        }
      else  /* unexpand */
        {
          /* Lines 12 and 13 remain unchanged. */
          expect[33 - 1] =
            "Line 33: Valid $LastChangedDate$, started expanded.";
          expect[34 - 1] =
            "Line 34: Valid $Date$, started expanded.";
          expect[51 - 1] =
            "Line 51: same, but with embedded keyword $$$$$$$$Date$$$$$$$$$$.";
          expect[52 - 1] =
            "Line 52: same, with expanded, empty keyword $$$$$$Date$$$$$$.";
        }
    }

  if (author)
    {
      if (expand)
        {
          expect[8 - 1] =
            apr_pstrcat (pool, "Line 8: ",
                         "Valid $LastChangedBy: ",
                         author,
                         " $, started unexpanded.",
                         NULL);
          expect[9 - 1] =
            apr_pstrcat (pool, "Line 9: ",
                         "Valid $Author: ", author, " $, started unexpanded.",
                         NULL);
          expect[37 - 1] =
            apr_pstrcat (pool, "Line 37: ",
                         "Valid $LastChangedBy: ", author, 
                         " $, started expanded.", NULL);
          expect[38 - 1] =
            apr_pstrcat (pool, "Line 38: ",
                         "Valid $Author: ", author, " $, started expanded.",
                         NULL);
        }
      else  /* unexpand */
        {
          /* Lines 8 and 9 remain unchanged. */
          expect[37 - 1] =
            "Line 37: Valid $LastChangedBy$, started expanded.";
          expect[38 - 1] =
            "Line 38: Valid $Author$, started expanded.";
        }
    }

  if (url)
    {
      if (expand)
        {
          expect[16 - 1] =
            apr_pstrcat (pool, "Line 16: ",
                         "Valid $HeadURL: ", url, " $, started unexpanded.",
                         NULL);
          expect[17 - 1] =
            apr_pstrcat (pool, "Line 17: ",
                         "Valid $URL: ", url, " $, started unexpanded.",
                         NULL);
          expect[41 - 1] =
            apr_pstrcat (pool, "Line 41: ",
                         "Valid $HeadURL: ", url, " $, started expanded.",
                         NULL);
          expect[42 - 1] =
            apr_pstrcat (pool, "Line 42: ",
                         "Valid $URL: ", url, " $, started expanded.",
                         NULL);
        }
      else  /* unexpand */
        {
          /* Lines 16 and 17 and remain unchanged. */
          expect[41 - 1] =
            "Line 41: Valid $HeadURL$, started expanded.";
          expect[42 - 1] =
            "Line 42: Valid $URL$, started expanded.";
        }
    }

  /* Handle line 48 specially, as it contains two valid keywords. */
  if (rev && author)
    {
      if (expand)
        {
          expect[48 - 1] =
            apr_pstrcat (pool, "Line 48: ",
                         "Two keywords back to back: "
                         "$Author: ", author, " $"
                         "$Rev: ", rev, " $.",
                         NULL);
          expect[49 - 1] =
            apr_pstrcat (pool, "Line 49: ",
                         "One keyword, one not, back to back: "
                         "$Author: ", author, " $Rev$.",
                         NULL);
        }
      /* Else Lines 48 and 49 remain unchanged. */
    }
  else if (rev && (! author))
    {
      if (expand)
        {
          expect[48 - 1] =
            apr_pstrcat (pool, "Line 48: ",
                         "Two keywords back to back: "
                         "$Author$$Rev: ", rev, " $.",
                         NULL);
          expect[49 - 1] =
            apr_pstrcat (pool, "Line 49: ",
                         "One keyword, one not, back to back: "
                         "$Author$Rev: ", rev, " $.",
                         NULL);

        }
      /* Else Lines 48 and 49 remain unchanged. */
    }
  else if ((! rev) && author)
    {
      if (expand)
        {
          expect[48 - 1] =
            apr_pstrcat (pool, "Line 48: ",
                         "Two keywords back to back: "
                         "$Author: ", author, " $$Rev$.",
                         NULL);
          expect[49 - 1] =
            apr_pstrcat (pool, "Line 49: ",
                         "One keyword, one not, back to back: "
                         "$Author: ", author, " $Rev$.",
                         NULL);
        }
      /* Else Lines 48 and 49 remain unchanged. */
    }
  /* Else neither rev nor author, so Lines 48 and 49 remain unchanged. */

  /* Handle line 24 specially, as it contains two valid keywords. */
  if (date && author)
    {
      if (expand)
        {
          expect[24 - 1] =
            apr_pstrcat (pool, "Line 24: ",
                         "keyword in a keyword: $Author: ",
                         author,
                         " $Date$ $",
                         NULL);
        }
      else  /* unexpand */
        {
          expect[24 - 1] =
            apr_pstrcat (pool, "Line 24: ",
                         "keyword in a keyword: $Author$Date$ $",
                         NULL);
        }
    }
  else if (date && (! author))
    {
      if (expand)
        {
          expect[24 - 1] =
            apr_pstrcat (pool, "Line 24: ",
                         "keyword in a keyword: $Author: $Date: ",
                         date,
                         " $ $",
                         NULL);
        }
      /* Else Line 24 remains unchanged. */
    }
  else if ((! date) && author)
    {
      if (expand)
        {
          expect[24 - 1] =
            apr_pstrcat (pool, "Line 24: ",
                         "keyword in a keyword: $Author: ",
                         author,
                         " $Date$ $",
                         NULL);
        }
      else  /* unexpand */
        {
          expect[24 - 1] =
            apr_pstrcat (pool, "Line 24: ",
                         "keyword in a keyword: $Author$Date$ $",
                         NULL);
        }
    }
  /* Else neither author nor date, so Line 24 remains unchanged. */

  /** Ready to verify. **/

  SVN_ERR (svn_string_from_file (&contents, dst_fname, pool));

  for (i = 0; i < (sizeof (expect) / sizeof (*expect)); i++)
    {
      if (contents->len < idx)
        return svn_error_createf
          (SVN_ERR_MALFORMED_FILE, 0, NULL, pool,
           "%s has short contents at line %d", dst_fname, i + 1);

      if (strncmp (contents->data + idx, expect[i], strlen (expect[i])) != 0)
        return svn_error_createf
          (SVN_ERR_MALFORMED_FILE, 0, NULL, pool, 
           "%s has wrong contents at line %d", dst_fname, i + 1);

      /* Else, the data is correct, at least up to the next eol. */

      idx += strlen (expect[i]);

      if (dst_eol)  /* verify the promised consistent eol style */
        {
          if (strncmp (contents->data + idx, dst_eol, strlen (dst_eol)) != 0)
            return svn_error_createf
              (SVN_ERR_IO_CORRUPT_EOL, 0, NULL, pool, 
               "%s has wrong eol style at line %d", dst_fname, i + 1);
          else
            idx += strlen (dst_eol);
        }
      else  /* allow any eol style, even inconsistent ones, loosely */
        {
          while ((*(contents->data + idx) == '\r')
                 || (*(contents->data + idx) == '\n'))
            idx++;
        }
    }

  /* Clean up this test, since successful. */
  SVN_ERR (remove_file (src_fname, pool));
  SVN_ERR (remove_file (dst_fname, pool));

  return SVN_NO_ERROR;
}



static svn_error_t *
noop (const char **msg,
      svn_boolean_t msg_only,
      apr_pool_t *pool)
{
  *msg = "no conversions";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("noop", NULL, NULL, 0, NULL, NULL, NULL, NULL, 1, pool));

  SVN_ERR (substitute_and_verify
           ("noop", "\r", NULL, 0, NULL, NULL, NULL, NULL, 1, pool));

  SVN_ERR (substitute_and_verify
           ("noop", "\n", NULL, 0, NULL, NULL, NULL, NULL, 1, pool));

  SVN_ERR (substitute_and_verify
           ("noop", "\r\n", NULL, 0, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}




/** EOL conversion alone. **/

static svn_error_t *
crlf_to_crlf (const char **msg,
              svn_boolean_t msg_only,
              apr_pool_t *pool)
{
  *msg = "convert CRLF to CRLF";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("crlf_to_crlf", "\r\n", "\r\n", 0,
            NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
lf_to_crlf (const char **msg,
            svn_boolean_t msg_only,
            apr_pool_t *pool)
{
  *msg = "convert LF to CRLF";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("lf_to_crlf", "\n", "\r\n", 0, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
cr_to_crlf (const char **msg,
            svn_boolean_t msg_only,
            apr_pool_t *pool)
{
  *msg = "convert CR to CRLF";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("cr_to_crlf", "\r", "\r\n", 0, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
mixed_to_crlf (const char **msg,
               svn_boolean_t msg_only,
               apr_pool_t *pool)
{
  *msg = "convert mixed line endings to CRLF";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("mixed_to_crlf", NULL, "\r\n", 1,
            NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
lf_to_lf (const char **msg,
          svn_boolean_t msg_only,
          apr_pool_t *pool)
{
  *msg = "convert LF to LF";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("lf_to_lf", "\n", "\n", 0, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
crlf_to_lf (const char **msg,
            svn_boolean_t msg_only,
            apr_pool_t *pool)
{
  *msg = "convert CRLF to LF";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("crlf_to_lf", "\r\n", "\n", 0, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
cr_to_lf (const char **msg,
          svn_boolean_t msg_only,
          apr_pool_t *pool)
{
  *msg = "convert CR to LF";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("cr_to_lf", "\r", "\n", 0, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
mixed_to_lf (const char **msg,
             svn_boolean_t msg_only,
             apr_pool_t *pool)
{
  *msg = "convert mixed line endings to LF";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("cr_to_lf", NULL, "\n", 1, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
crlf_to_cr (const char **msg,
            svn_boolean_t msg_only,
            apr_pool_t *pool)
{
  *msg = "convert CRLF to CR";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("crlf_to_cr", "\r\n", "\r", 0, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
lf_to_cr (const char **msg,
          svn_boolean_t msg_only,
          apr_pool_t *pool)
{
  *msg = "convert LF to CR";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("lf_to_cr", "\n", "\r", 0, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
cr_to_cr (const char **msg,
          svn_boolean_t msg_only,
          apr_pool_t *pool)
{
  *msg = "convert CR to CR";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("cr_to_cr", "\r", "\r", 0, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
mixed_to_cr (const char **msg,
             svn_boolean_t msg_only,
             apr_pool_t *pool)
{
  *msg = "convert mixed line endings to CR";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("mixed_to_cr", NULL, "\r", 1, NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
mixed_no_repair (const char **msg,
                 svn_boolean_t msg_only,
                 apr_pool_t *pool)
{
  *msg = "don't convert mixed line endings in absence of repair flag";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("mixed_no_repair", NULL, "\n", 0,
            NULL, NULL, NULL, NULL, 1, pool));

  SVN_ERR (substitute_and_verify
           ("mixed_no_repair", NULL, "\r\n", 0,
            NULL, NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}



/** Keyword expansion alone. **/

static svn_error_t *
expand_author (const char **msg,
               svn_boolean_t msg_only,
               apr_pool_t *pool)
{
  *msg = "expand author keyword";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("author", "\n", NULL, 0, NULL, NULL, "jrandom", NULL, 1, pool));

  SVN_ERR (substitute_and_verify
           ("author", "\r\n", NULL, 0, NULL, NULL, "jrandom", NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
expand_date (const char **msg,
             svn_boolean_t msg_only,
             apr_pool_t *pool)
{
  *msg = "expand date keyword";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("date", "\n", NULL, 0,
            NULL, "Wed Jan  9 07:49:05 2002", NULL, NULL, 1, pool));

  SVN_ERR (substitute_and_verify
           ("date", "\r\n", NULL, 0,
            NULL, "Wed Jan  9 07:49:05 2002", NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
expand_author_date (const char **msg,
                    svn_boolean_t msg_only,
                    apr_pool_t *pool)
{
  *msg = "expand author and date keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("author_date", "\n", NULL, 0,
            NULL, "Wed Jan  9 07:49:05 2002", "jrandom", NULL, 1, pool));

  SVN_ERR (substitute_and_verify
           ("author_date", "\r\n", NULL, 0,
            NULL, "Wed Jan  9 07:49:05 2002", "jrandom", NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
expand_author_rev (const char **msg,
                   svn_boolean_t msg_only,
                   apr_pool_t *pool)
{
  *msg = "expand author and rev keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("author_rev", "\n", NULL, 0,
            "1729", NULL, "jrandom", NULL, 1, pool));

  SVN_ERR (substitute_and_verify
           ("author_rev", "\r\n", NULL, 0,
            "1729", NULL, "jrandom", NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
expand_rev (const char **msg,
            svn_boolean_t msg_only,
            apr_pool_t *pool)
{
  *msg = "expand rev keyword";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("rev", "\n", NULL, 0,
            "1729", NULL, NULL, NULL, 1, pool));

  SVN_ERR (substitute_and_verify
           ("rev", "\r\n", NULL, 0,
            "1729", NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
expand_rev_url (const char **msg,
                svn_boolean_t msg_only,
                apr_pool_t *pool)
{
  *msg = "expand rev and url keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("rev_url", "\n", NULL, 0,
            "1729", NULL, NULL, "http://subversion.tigris.org", 1, pool));

  SVN_ERR (substitute_and_verify
           ("rev_url", "\r\n", NULL, 0,
            "1729", NULL, NULL, "http://subversion.tigris.org", 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
expand_author_date_rev_url (const char **msg,
                            svn_boolean_t msg_only,
                            apr_pool_t *pool)
{
  *msg = "expand author, date, rev, and url keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("author_date_rev_url", "\n", NULL, 0,
            "1729",
            "Wed Jan  9 07:49:05 2002",
            "jrandom",
            "http://subversion.tigris.org",
            1, pool));

  SVN_ERR (substitute_and_verify
           ("author_date_rev_url", "\r\n", NULL, 0,
            "1729",
            "Wed Jan  9 07:49:05 2002",
            "jrandom",
            "http://subversion.tigris.org",
            1, pool));

  return SVN_NO_ERROR;
}



/** Keyword expansion and EOL conversion together. **/

static svn_error_t *
lf_to_crlf_expand_author (const char **msg,
                          svn_boolean_t msg_only,
                          apr_pool_t *pool)
{
  *msg = "lf_to_crlf, plus expand author keyword";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("lf_to_crlf_author", "\n", "\r\n", 0,
            NULL, NULL, "jrandom", NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
mixed_to_lf_expand_author_date (const char **msg,
                                svn_boolean_t msg_only,
                                apr_pool_t *pool)
{
  *msg = "mixed_to_lf, plus expand author and date keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("mixed_to_lf_author_date", NULL, "\n", 1,
            NULL, "Wed Jan  9 07:49:05 2002", "jrandom", NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
crlf_to_cr_expand_author_rev (const char **msg,
                              svn_boolean_t msg_only,
                              apr_pool_t *pool)
{
  *msg = "crlf_to_cr, plus expand author and rev keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("crlf_to_cr_author_rev", "\r\n", "\r", 0,
            "1729", NULL, "jrandom", NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
cr_to_crlf_expand_rev (const char **msg,
                       svn_boolean_t msg_only,
                       apr_pool_t *pool)
{
  *msg = "cr_to_crlf, plus expand rev keyword";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("cr_to_crlf_rev", "\r", "\r\n", 0,
            "1729", NULL, NULL, NULL, 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
cr_to_crlf_expand_rev_url (const char **msg,
                           svn_boolean_t msg_only,
                           apr_pool_t *pool)
{
  *msg = "cr_to_crlf, plus expand rev and url keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("cr_to_crlf_rev_url", "\r", "\r\n", 0,
            "1729", NULL, NULL, "http://subversion.tigris.org", 1, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
mixed_to_crlf_expand_author_date_rev_url (const char **msg,
                                          svn_boolean_t msg_only,
                                          apr_pool_t *pool)
{
  *msg = "mixed_to_crlf, plus expand author, date, rev, and url keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("mixed_to_crlf_author_date_rev_url", NULL, "\r\n", 1,
            "1729",
            "Wed Jan  9 07:49:05 2002",
            "jrandom",
            "http://subversion.tigris.org",
            1,
            pool));

  return SVN_NO_ERROR;
}



/** Keyword unexpansion alone. **/

static svn_error_t *
unexpand_author (const char **msg,
                 svn_boolean_t msg_only,
                 apr_pool_t *pool)
{
  *msg = "unexpand author keyword";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("author", "\n", NULL, 0, NULL, NULL, "jrandom", NULL, 0, pool));

  SVN_ERR (substitute_and_verify
           ("author", "\r\n", NULL, 0, NULL, NULL, "jrandom", NULL, 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
unexpand_date (const char **msg,
               svn_boolean_t msg_only,
               apr_pool_t *pool)
{
  *msg = "unexpand date keyword";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("date", "\n", NULL, 0,
            NULL, "Wed Jan  9 07:49:05 2002", NULL, NULL, 0, pool));

  SVN_ERR (substitute_and_verify
           ("date", "\r\n", NULL, 0,
            NULL, "Wed Jan  9 07:49:05 2002", NULL, NULL, 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
unexpand_author_date (const char **msg,
                      svn_boolean_t msg_only,
                      apr_pool_t *pool)
{
  *msg = "unexpand author and date keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("author_date", "\n", NULL, 0,
            NULL, "Wed Jan  9 07:49:05 2002", "jrandom", NULL, 0, pool));

  SVN_ERR (substitute_and_verify
           ("author_date", "\r\n", NULL, 0,
            NULL, "Wed Jan  9 07:49:05 2002", "jrandom", NULL, 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
unexpand_author_rev (const char **msg,
                     svn_boolean_t msg_only,
                     apr_pool_t *pool)
{
  *msg = "unexpand author and rev keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("author_rev", "\n", NULL, 0,
            "1729", NULL, "jrandom", NULL, 0, pool));

  SVN_ERR (substitute_and_verify
           ("author_rev", "\r\n", NULL, 0,
            "1729", NULL, "jrandom", NULL, 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
unexpand_rev (const char **msg,
              svn_boolean_t msg_only,
              apr_pool_t *pool)
{
  *msg = "unexpand rev keyword";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("rev", "\n", NULL, 0,
            "1729", NULL, NULL, NULL, 0, pool));

  SVN_ERR (substitute_and_verify
           ("rev", "\r\n", NULL, 0,
            "1729", NULL, NULL, NULL, 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
unexpand_rev_url (const char **msg,
                  svn_boolean_t msg_only,
                  apr_pool_t *pool)
{
  *msg = "unexpand rev and url keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("rev_url", "\n", NULL, 0,
            "1729", NULL, NULL, "http://subversion.tigris.org", 0, pool));

  SVN_ERR (substitute_and_verify
           ("rev_url", "\r\n", NULL, 0,
            "1729", NULL, NULL, "http://subversion.tigris.org", 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
unexpand_author_date_rev_url (const char **msg,
                              svn_boolean_t msg_only,
                              apr_pool_t *pool)
{
  *msg = "unexpand author, date, rev, and url keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("author_date_rev_url", "\n", NULL, 0,
            "1729",
            "Wed Jan  9 07:49:05 2002",
            "jrandom",
            "http://subversion.tigris.org",
            1, pool));

  SVN_ERR (substitute_and_verify
           ("author_date_rev_url", "\r\n", NULL, 0,
            "1729",
            "Wed Jan  9 07:49:05 2002",
            "jrandom",
            "http://subversion.tigris.org",
            1, pool));

  return SVN_NO_ERROR;
}



/** Keyword unexpansion and EOL conversion together. **/

static svn_error_t *
lf_to_crlf_unexpand_author (const char **msg,
                            svn_boolean_t msg_only,
                            apr_pool_t *pool)
{
  *msg = "lf_to_crlf, plus unexpand author keyword";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("lf_to_crlf_author", "\n", "\r\n", 0,
            NULL, NULL, "jrandom", NULL, 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
mixed_to_lf_unexpand_author_date (const char **msg,
                                  svn_boolean_t msg_only,
                                  apr_pool_t *pool)
{
  *msg = "mixed_to_lf, plus unexpand author and date keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("mixed_to_lf_author_date", NULL, "\n", 1,
            NULL, "Wed Jan  9 07:49:05 2002", "jrandom", NULL, 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
crlf_to_cr_unexpand_author_rev (const char **msg,
                                svn_boolean_t msg_only,
                                apr_pool_t *pool)
{
  *msg = "crlf_to_cr, plus unexpand author and rev keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("crlf_to_cr_author_rev", "\r\n", "\r", 0,
            "1729", NULL, "jrandom", NULL, 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
cr_to_crlf_unexpand_rev (const char **msg,
                         svn_boolean_t msg_only,
                         apr_pool_t *pool)
{
  *msg = "cr_to_crlf, plus unexpand rev keyword";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("cr_to_crlf_rev", "\r", "\r\n", 0,
            "1729", NULL, NULL, NULL, 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
cr_to_crlf_unexpand_rev_url (const char **msg,
                             svn_boolean_t msg_only,
                             apr_pool_t *pool)
{
  *msg = "cr_to_crlf, plus unexpand rev and url keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("cr_to_crlf_rev_url", "\r", "\r\n", 0,
            "1729", NULL, NULL, "http://subversion.tigris.org", 0, pool));

  return SVN_NO_ERROR;
}


static svn_error_t *
mixed_to_crlf_unexpand_author_date_rev_url (const char **msg,
                                            svn_boolean_t msg_only,
                                            apr_pool_t *pool)
{
  *msg = "mixed_to_crlf, plus unexpand author, date, rev, and url keywords";

  if (msg_only)
    return SVN_NO_ERROR;

  SVN_ERR (substitute_and_verify
           ("mixed_to_crlf_author_date_rev_url", NULL, "\r\n", 1,
            "1729",
            "Wed Jan  9 07:49:05 2002",
            "jrandom",
            "http://subversion.tigris.org",
            0,
            pool));

  return SVN_NO_ERROR;
}



/* The test table.  */

svn_error_t * (*test_funcs[]) (const char **msg,
                               svn_boolean_t msg_only,
                               apr_pool_t *pool) = {
  0,
  /* The no-op conversion. */
  noop,
  /* Conversions resulting in crlf, no keywords involved. */
  crlf_to_crlf,
  lf_to_crlf,
  cr_to_crlf,
  mixed_to_crlf,
  /* Conversions resulting in lf, no keywords involved. */
  lf_to_lf,
  crlf_to_lf,
  cr_to_lf,
  mixed_to_lf,
  /* Conversions resulting in cr, no keywords involved. */
  crlf_to_cr,
  lf_to_cr,
  cr_to_cr,
  mixed_to_cr,
  /* Random eol stuff. */
  mixed_no_repair,
  /* Keyword expansion alone, no eol conversion involved. */
  expand_author,
  expand_date,
  expand_author_date,
  expand_author_rev,
  expand_rev,
  expand_rev_url,
  expand_author_date_rev_url,
  /* Keyword expansion and eol conversion together. */
  lf_to_crlf_expand_author,
  mixed_to_lf_expand_author_date,
  crlf_to_cr_expand_author_rev,
  cr_to_crlf_expand_rev,
  cr_to_crlf_expand_rev_url,
  mixed_to_crlf_expand_author_date_rev_url,
  /* Keyword unexpansion alone, no eol conversion involved. */
  unexpand_author,
  unexpand_date,
  unexpand_author_date,
  unexpand_author_rev,
  unexpand_rev,
  unexpand_rev_url,
  unexpand_author_date_rev_url,
  /* Keyword unexpansion and eol conversion together. */
  lf_to_crlf_unexpand_author,
  mixed_to_lf_unexpand_author_date,
  crlf_to_cr_unexpand_author_rev,
  cr_to_crlf_unexpand_rev,
  cr_to_crlf_unexpand_rev_url,
  mixed_to_crlf_unexpand_author_date_rev_url,
  0
};



/* 
 * local variables:
 * eval: (load-file "../../../tools/dev/svn-dev.el")
 * end:
 */

