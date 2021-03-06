/*  svn_quoprint.h:  quoted-printable encoding and decoding functions.
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



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef SVN_QUOPRINT_H
#define SVN_QUOPRINT_H

#include "svn_io.h"

/* Return a writable generic stream which will encode binary data in
   quoted-printable format and write the encoded data to OUTPUT.  Be
   sure to close the stream when done writing in order to squeeze out
   the last bit of encoded data.  */
svn_stream_t *svn_quoprint_encode (svn_stream_t *output, apr_pool_t *pool);

/* Return a writable generic stream which will decode
   quoted-printable-encoded data and write the decoded data to OUTPUT.  */
svn_stream_t *svn_quoprint_decode (svn_stream_t *output, apr_pool_t *pool);


/* Simpler interfaces for encoding and decoding quoted-printable data
   assuming we have all of it present at once.  The returned string
   will be allocated from POOL.  */
svn_stringbuf_t *svn_quoprint_encode_string (svn_stringbuf_t *str, apr_pool_t *pool);
svn_stringbuf_t *svn_quoprint_decode_string (svn_stringbuf_t *str, apr_pool_t *pool);


#endif /* SVN_QUOPRINT_H */

#ifdef __cplusplus
}
#endif /* __cplusplus */


/* --------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../tools/dev/svn-dev.el")
 * end:
 */
