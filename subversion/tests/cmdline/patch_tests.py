import filecmp
  mu_path = sbox.ospath('A/mu')
    'U         %s\n' % sbox.ospath('A/D/gamma'),
    'U         %s\n' % sbox.ospath('iota'),
    'A         %s\n' % sbox.ospath('new'),
    'U         %s\n' % sbox.ospath('A/mu'),
    'D         %s\n' % sbox.ospath('A/B/E/beta'),
  sbox.build(read_only = True)
  ] + svntest.main.summary_of_conflicts(skipped_paths=1)
  expected_status = svntest.actions.get_virginal_state('', 1)
    lambda_path:  Item(verb='Skipped missing target'),
  svntest.actions.run_and_verify_patch('', os.path.abspath(patch_file_path),
  mu_path = sbox.ospath('A/mu')
  iota_path = sbox.ospath('iota')
  expected_status = svntest.actions.get_virginal_state('', 1)
  svntest.actions.run_and_verify_patch('', os.path.abspath(patch_file_path),
  mu_path = sbox.ospath('A/mu')
    'U         %s\n' % sbox.ospath('A/D/gamma'),
    'U         %s\n' % sbox.ospath('iota'),
    'A         %s\n' % sbox.ospath('new'),
    'U         %s\n' % sbox.ospath('A/mu'),
    'D         %s\n' % sbox.ospath('A/B/E/beta'),
  mu_path = sbox.ospath('A/mu')
    'U         %s\n' % sbox.ospath('A/D/gamma'),
    'U         %s\n' % sbox.ospath('iota'),
    'A         %s\n' % sbox.ospath('new'),
    'U         %s\n' % sbox.ospath('A/mu'),
    'D         %s\n' % sbox.ospath('A/B/E/beta'),
  gamma_path = sbox.ospath('A/D/gamma')
  iota_path = sbox.ospath('iota')
    'U         %s\n' % sbox.ospath('A/D/gamma'),
    'U         %s\n' % sbox.ospath('iota'),
  sbox.build(read_only = True)
  C_path = sbox.ospath('A/C')
  E_path = sbox.ospath('A/B/E')

  svntest.main.safe_rmtree(C_path)
  svntest.main.safe_rmtree(E_path)
  A_B_E_Y_new_path = sbox.ospath('A/B/E/Y/new')
  A_C_new_path = sbox.ospath('A/C/new')
  A_Z_new_path = sbox.ospath('A/Z/new')
    'A         %s\n' % sbox.ospath('X'),
    'A         %s\n' % sbox.ospath('X/Y'),
    'A         %s\n' % sbox.ospath('X/Y/new'),
  ] + svntest.main.summary_of_conflicts(skipped_paths=3)
  expected_disk.remove('A/B/E', 'A/B/E/alpha', 'A/B/E/beta', 'A/C')
           'X'          : Item(status='A ', wc_rev=0),
           'X/Y'        : Item(status='A ', wc_rev=0),
           'X/Y/new'    : Item(status='A ', wc_rev=0),
           'A/B/E'      : Item(status='! ', wc_rev=1),
           'A/B/E/alpha': Item(status='! ', wc_rev=1),
           'A/B/E/beta' : Item(status='! ', wc_rev=1),
           'A/C'        : Item(status='! ', wc_rev=1),
  expected_skip = wc.State(
    '',
    {A_Z_new_path     : Item(verb='Skipped missing target'),
     A_B_E_Y_new_path : Item(verb='Skipped missing target'),
     A_C_new_path     : Item(verb='Skipped missing target')})
  sbox.build(read_only = True)
  F_path = sbox.ospath('A/B/F')
  os.remove(sbox.ospath('A/D/H/chi'))
    'D         %s\n' % sbox.ospath('A/D/H/psi'),
    'D         %s\n' % sbox.ospath('A/D/H/omega'),
    'D         %s\n' % sbox.ospath('A/B/lambda'),
    'D         %s\n' % sbox.ospath('A/B/E/alpha'),
    'D         %s\n' % sbox.ospath('A/B/E/beta'),
    'D         %s\n' % sbox.ospath('A/B/E'),
    'D         %s\n' % sbox.ospath('A/B'),
  expected_disk.remove('A/D/H/chi',
                       'A/D/H/psi',
                       'A/D/H/omega',
                       'A/B/lambda',
                       'A/B',
                       'A/B/E',
                       'A/B/E/alpha',
                       'A/B/E/beta',
                       'A/B/F')
  gamma_path = sbox.ospath('A/D/gamma')
    'C         %s\n' % sbox.ospath('A/D/gamma'),
  ] + svntest.main.summary_of_conflicts(text_conflicts=1)
  gamma_path = sbox.ospath('A/D/gamma')
                       sbox.ospath('A/D/gamma'))
    'U         %s\n' % sbox.ospath('A/D/gamma'),
  mu_path = sbox.ospath('A/mu')
    'U         %s\n' % sbox.ospath('A/mu'),
  mu_path = sbox.ospath('A/mu')
    'U         %s\n' % sbox.ospath('A/D/gamma'),
    'U         %s\n' % sbox.ospath('iota'),
    'A         %s\n' % sbox.ospath('new'),
    'U         %s\n' % sbox.ospath('A/mu'),
    'D         %s\n' % sbox.ospath('A/B/E/beta'),
  sbox.build(read_only = True)
  mu_path = sbox.ospath('A/mu')
  # CRLF is a string that will match a CRLF sequence read from a text file.
  # ### On Windows, we assume CRLF will be read as LF, so it's a poor test.
  eols = [crlf, '\015', '\n', '\012']
        'G         %s\n' % sbox.ospath('A/mu'),
  mu_path = sbox.ospath('A/mu')
  # CRLF is a string that will match a CRLF sequence read from a text file.
  # ### On Windows, we assume CRLF will be read as LF, so it's a poor test.
        'U         %s\n' % sbox.ospath('A/mu'),
  sbox.build(read_only = True)
  mu_path = sbox.ospath('A/mu')
  # CRLF is a string that will match a CRLF sequence read from a text file.
  # ### On Windows, we assume CRLF will be read as LF, so it's a poor test.
        'G         %s\n' % sbox.ospath('A/mu'),
  mu_path = sbox.ospath('A/mu')
    'U         %s\n' % sbox.ospath('A/mu'),
  mu_path = sbox.ospath('A/mu')
  iota_path = sbox.ospath('iota')
    'U         %s\n' % sbox.ospath('iota'),
  iota_path = sbox.ospath('iota')
    ' U        %s\n' % sbox.ospath('iota'),
  mu_path = sbox.ospath('A/mu')
  beta_path = sbox.ospath('A/B/E/beta')
    'U         %s\n' % sbox.ospath('A/D/gamma'),
    'U         %s\n' % sbox.ospath('iota'),
    'A         %s\n' % sbox.ospath('new'),
    'U         %s\n' % sbox.ospath('A/mu'),
    'G         %s\n' % sbox.ospath('A/D/gamma'),
    'G         %s\n' % sbox.ospath('iota'),
    'G         %s\n' % sbox.ospath('new'),
    'G         %s\n' % sbox.ospath('A/mu'),
  ] + svntest.main.summary_of_conflicts(skipped_paths=1)
  expected_skip = wc.State('', {beta_path : Item(verb='Skipped')})
  B_path = sbox.ospath('A/B')
    ' C        %s\n' % sbox.ospath('A/B'),
  ] + svntest.main.summary_of_conflicts(prop_conflicts=1)
  sbox.build(read_only = True)
  iota_path = sbox.ospath('iota')
    'A         %s\n' % sbox.ospath('new'),
    'A         %s\n' % sbox.ospath('X'),
  iota_path = sbox.ospath('iota')
  expected_status = svntest.actions.get_virginal_state('', 1)
  svntest.actions.run_and_verify_patch('', os.path.abspath(patch_file_path),
  mu_path = sbox.ospath('A/mu')
    ' U        %s\n' % sbox.ospath('A/mu'),
  sbox.build(read_only = True)
  new_path = sbox.ospath('new')
    'A         %s\n' % sbox.ospath('new'),
    'D         %s\n' % sbox.ospath('iota'),
  mu_path = sbox.ospath('A/mu')
    'U         %s\n' % sbox.ospath('A/mu'),
  mu_path = sbox.ospath('A/mu')
    'U         %s\n' % sbox.ospath('A/D/gamma'),
    'U         %s\n' % sbox.ospath('iota'),
    'A         %s\n' % sbox.ospath('new'),
    'U         %s\n' % sbox.ospath('A/mu'),
    'D         %s\n' % sbox.ospath('A/B/E/beta'),
    'G         %s\n' % sbox.ospath('A/D/gamma'),
    'G         %s\n' % sbox.ospath('iota'),
    'D         %s\n' % sbox.ospath('new'),
    'G         %s\n' % sbox.ospath('A/mu'),
    'A         %s\n' % sbox.ospath('A/B/E/beta'),
  sbox.build(read_only = True)
  mu_path = sbox.ospath('A/mu')
  sbox.build(read_only = True)
    'A         %s\n' % sbox.ospath('iota_symlink'),
def patch_moved_away(sbox):
  "patch a file that was moved away"

  sbox.build()
  wc_dir = sbox.wc_dir

  patch_file_path = make_patch_path(sbox)
  mu_path = sbox.ospath('A/mu')

  mu_contents = [
    "Dear internet user,\n",
    "\n",
    "We wish to congratulate you over your email success in our computer\n",
    "Balloting. This is a Millennium Scientific Electronic Computer Draw\n",
    "in which email addresses were used. All participants were selected\n",
    "through a computer ballot system drawn from over 100,000 company\n",
    "and 50,000,000 individual email addresses from all over the world.\n",
    "\n",
    "Your email address drew and have won the sum of  750,000 Euros\n",
    "( Seven Hundred and Fifty Thousand Euros) in cash credited to\n",
    "file with\n",
    "    REFERENCE NUMBER: ESP/WIN/008/05/10/MA;\n",
    "    WINNING NUMBER : 14-17-24-34-37-45-16\n",
    "    BATCH NUMBERS :\n",
    "    EULO/1007/444/606/08;\n",
    "    SERIAL NUMBER: 45327\n",
    "and PROMOTION DATE: 13th June. 2009\n",
    "\n",
    "To claim your winning prize, you are to contact the appointed\n",
    "agent below as soon as possible for the immediate release of your\n",
    "winnings with the below details.\n",
    "\n",
    "Again, we wish to congratulate you over your email success in our\n"
    "computer Balloting.\n"
  ]

  # Set mu contents
  svntest.main.file_write(mu_path, ''.join(mu_contents))
  expected_output = svntest.wc.State(wc_dir, {
    'A/mu'       : Item(verb='Sending'),
    })
  expected_status = svntest.actions.get_virginal_state(wc_dir, 1)
  expected_status.tweak('A/mu', wc_rev=2)
  svntest.actions.run_and_verify_commit(wc_dir, expected_output,
                                        expected_status, None, wc_dir)

  # Move mu away
  sbox.simple_move("A/mu", "A/mu2")

  # Apply patch
  unidiff_patch = [
    "--- A/mu.orig	2009-06-24 15:23:55.000000000 +0100\n",
    "+++ A/mu	2009-06-24 15:21:23.000000000 +0100\n",
    "@@ -6,6 +6,9 @@\n",
    " through a computer ballot system drawn from over 100,000 company\n",
    " and 50,000,000 individual email addresses from all over the world.\n",
    " \n",
    "+It is a promotional program aimed at encouraging internet users;\n",
    "+therefore you do not need to buy ticket to enter for it.\n",
    "+\n",
    " Your email address drew and have won the sum of  750,000 Euros\n",
    " ( Seven Hundred and Fifty Thousand Euros) in cash credited to\n",
    " file with\n",
    "@@ -14,11 +17,8 @@\n",
    "     BATCH NUMBERS :\n",
    "     EULO/1007/444/606/08;\n",
    "     SERIAL NUMBER: 45327\n",
    "-and PROMOTION DATE: 13th June. 2009\n",
    "+and PROMOTION DATE: 14th June. 2009\n",
    " \n",
    " To claim your winning prize, you are to contact the appointed\n",
    " agent below as soon as possible for the immediate release of your\n",
    " winnings with the below details.\n",
    "-\n",
    "-Again, we wish to congratulate you over your email success in our\n",
    "-computer Balloting.\n",
  ]

  svntest.main.file_write(patch_file_path, ''.join(unidiff_patch))

  mu_contents = [
    "Dear internet user,\n",
    "\n",
    "We wish to congratulate you over your email success in our computer\n",
    "Balloting. This is a Millennium Scientific Electronic Computer Draw\n",
    "in which email addresses were used. All participants were selected\n",
    "through a computer ballot system drawn from over 100,000 company\n",
    "and 50,000,000 individual email addresses from all over the world.\n",
    "\n",
    "It is a promotional program aimed at encouraging internet users;\n",
    "therefore you do not need to buy ticket to enter for it.\n",
    "\n",
    "Your email address drew and have won the sum of  750,000 Euros\n",
    "( Seven Hundred and Fifty Thousand Euros) in cash credited to\n",
    "file with\n",
    "    REFERENCE NUMBER: ESP/WIN/008/05/10/MA;\n",
    "    WINNING NUMBER : 14-17-24-34-37-45-16\n",
    "    BATCH NUMBERS :\n",
    "    EULO/1007/444/606/08;\n",
    "    SERIAL NUMBER: 45327\n",
    "and PROMOTION DATE: 14th June. 2009\n",
    "\n",
    "To claim your winning prize, you are to contact the appointed\n",
    "agent below as soon as possible for the immediate release of your\n",
    "winnings with the below details.\n",
  ]

  expected_output = [
    'U         %s\n' % sbox.ospath('A/mu2'),
  ]

  expected_disk = svntest.main.greek_state.copy()
  expected_disk.add({'A/mu2': Item(contents=''.join(mu_contents))})
  expected_disk.remove('A/mu')

  expected_status = svntest.actions.get_virginal_state(wc_dir, 1)
  expected_status.add({
    'A/mu2' : Item(status='A ', copied='+', wc_rev='-', moved_from='A/mu'),
  })

  expected_status.tweak('A/mu', status='D ', wc_rev=2, moved_to='A/mu2')

  expected_skip = wc.State('', { })

  svntest.actions.run_and_verify_patch(wc_dir, os.path.abspath(patch_file_path),
                                       expected_output,
                                       expected_disk,
                                       expected_status,
                                       expected_skip,
                                       None, # expected err
                                       1, # check-props
                                       1) # dry-run

@Issue(3991)
def patch_lacking_trailing_eol(sbox):
  "patch file lacking trailing eol"

  sbox.build(read_only = True)
  wc_dir = sbox.wc_dir

  patch_file_path = make_patch_path(sbox)
  iota_path = sbox.ospath('iota')
  mu_path = sbox.ospath('A/mu')

  # Prepare
  expected_status = svntest.actions.get_virginal_state(wc_dir, 1)

  # Apply patch
  unidiff_patch = [
    "Index: iota\n",
    "===================================================================\n",
    "--- iota\t(revision 1)\n",
    "+++ iota\t(working copy)\n",
    # TODO: -1 +1
    "@@ -1 +1,2 @@\n",
    " This is the file 'iota'.\n",
    "+Some more bytes", # No trailing \n on this line!
  ]

  svntest.main.file_write(patch_file_path, ''.join(unidiff_patch))

  gamma_contents = "It is the file 'gamma'.\n"
  iota_contents = "This is the file 'iota'.\n"
  new_contents = "new\n"

  expected_output = [
    'U         %s\n' % sbox.ospath('iota'),
  ]

  # Expect a newline to be appended
  expected_disk = svntest.main.greek_state.copy()
  expected_disk.tweak('iota', contents=iota_contents + "Some more bytes")

  expected_status = svntest.actions.get_virginal_state(wc_dir, 1)
  expected_status.tweak('iota', status='M ')

  expected_skip = wc.State('', { })

  svntest.actions.run_and_verify_patch(wc_dir, os.path.abspath(patch_file_path),
                                       expected_output,
                                       expected_disk,
                                       expected_status,
                                       expected_skip,
                                       None, # expected err
                                       1, # check-props
                                       1) # dry-run
  iota_path = sbox.ospath('iota')
    ' U        %s\n' % sbox.ospath('iota'),
  # Apply patch
                                       1, # dry-run
                                       '--reverse-diff')
  sbox.build(read_only = True)
  newfile_path = sbox.ospath('newfile')
                                       1, # dry-run
                                       '--reverse-diff')
  newfile_path = sbox.ospath('newfile')
                                       1, # dry-run
                                       '--reverse-diff')
  sbox.build(read_only = True)
    'A         %s\n' % sbox.ospath('new'),
    'D         %s\n' % sbox.ospath('A/B/E/beta'),
  sbox.build(read_only = True)
    'Skipped missing target: \'%s\'\n' % skipped_path,
  ] + svntest.main.summary_of_conflicts(skipped_paths=1)
  expected_status = svntest.actions.get_virginal_state('', 1)
  expected_skip = wc.State(
    '',
    {skipped_path: Item(verb='Skipped missing target')})
  svntest.actions.run_and_verify_patch('', os.path.abspath(patch_file_path),
  iota_path = sbox.ospath('iota')
    'U         %s\n' % sbox.ospath('A/mu'),
    'U         %s\n' % sbox.ospath('iota'),
    'A         %s\n' % sbox.ospath('P'),
    'A         %s\n' % sbox.ospath('P/Q'),
    'A         %s\n' % sbox.ospath('P/Q/foo'),
    'D         %s\n' % sbox.ospath('iota'),
      'src'                             : Item(status='A ', wc_rev=0),
      'src/tools/ConsoleRunner'         : Item(status='A ', wc_rev=0),
@Issue(4273)
def patch_change_symlink_target(sbox):
  "patch changes symlink target"

  sbox.build()
  wc_dir = sbox.wc_dir
  patch_file_path = make_patch_path(sbox)
  svntest.main.file_write(patch_file_path, '\n'.join([
    "Index: link",
    "===================================================================",
    "--- link\t(revision 1)",
    "+++ link\t(working copy)",
    "@@ -1 +1 @@",
    "-link foo",
    "\\ No newline at end of file",
    "+link bardame",
    "\\ No newline at end of file",
    "",
    ]))

  # r2 - Try as plain text with how we encode the symlink
  svntest.main.file_write(sbox.ospath('link'), 'link foo')
  sbox.simple_add('link')

  expected_output = svntest.wc.State(wc_dir, {
    'link'       : Item(verb='Adding'),
  })
  svntest.actions.run_and_verify_commit(wc_dir, expected_output,
                                        None, None, wc_dir)

  patch_output = [
    'U         %s\n' % sbox.ospath('link'),
  ]

  svntest.actions.run_and_verify_svn(None, patch_output, [],
                                     'patch', patch_file_path, wc_dir)

  # r3 - Store result
  expected_output = svntest.wc.State(wc_dir, {
    'link'       : Item(verb='Sending'),
  })
  svntest.actions.run_and_verify_commit(wc_dir, expected_output,
                                        None, None, wc_dir)

  # r4 - Now as symlink
  sbox.simple_rm('link')
  sbox.simple_add_symlink('foo', 'link')
  expected_output = svntest.wc.State(wc_dir, {
    'link'       : Item(verb='Replacing'),
  })
  svntest.actions.run_and_verify_commit(wc_dir, expected_output,
                                        None, None, wc_dir)

  svntest.actions.run_and_verify_svn(None, patch_output, [],
                                     'patch', patch_file_path, wc_dir)

  # TODO: when it passes, verify that the on-disk 'link' is correct ---
  #       symlink to 'bar' (or "link bar" on non-HAVE_SYMLINK platforms)

  # BH: easy check for node type: a non symlink would show as obstructed
  expected_status = svntest.actions.get_virginal_state(wc_dir, 1)
  expected_status.add({
    'link'              : Item(status='M ', wc_rev='4'),
  })
  svntest.actions.run_and_verify_status(wc_dir, expected_status)

def patch_replace_dir_with_file_and_vv(sbox):
  "replace dir with file and file with dir"
  sbox.build(read_only=True)

  patch_file_path = make_patch_path(sbox)
  svntest.main.file_write(patch_file_path, ''.join([
  # Delete all files in D and descendants to delete D itself
    "Index: A/D/G/pi\n",
    "===================================================================\n",
    "--- A/D/G/pi\t(revision 1)\n",
    "+++ A/D/G/pi\t(working copy)\n",
    "@@ -1 +0,0 @@\n",
    "-This is the file 'pi'.\n",
    "Index: A/D/G/rho\n",
    "===================================================================\n",
    "--- A/D/G/rho\t(revision 1)\n",
    "+++ A/D/G/rho\t(working copy)\n",
    "@@ -1 +0,0 @@\n",
    "-This is the file 'rho'.\n",
    "Index: A/D/G/tau\n",
    "===================================================================\n",
    "--- A/D/G/tau\t(revision 1)\n",
    "+++ A/D/G/tau\t(working copy)\n",
    "@@ -1 +0,0 @@\n",
    "-This is the file 'tau'.\n",
    "Index: A/D/H/chi\n",
    "===================================================================\n",
    "--- A/D/H/chi\t(revision 1)\n",
    "+++ A/D/H/chi\t(working copy)\n",
    "@@ -1 +0,0 @@\n",
    "-This is the file 'chi'.\n",
    "Index: A/D/H/omega\n",
    "===================================================================\n",
    "--- A/D/H/omega\t(revision 1)\n",
    "+++ A/D/H/omega\t(working copy)\n",
    "@@ -1 +0,0 @@\n",
    "-This is the file 'omega'.\n",
    "Index: A/D/H/psi\n",
    "===================================================================\n",
    "--- A/D/H/psi\t(revision 1)\n",
    "+++ A/D/H/psi\t(working copy)\n",
    "@@ -1 +0,0 @@\n",
    "-This is the file 'psi'.\n",
    "Index: A/D/gamma\n",
    "===================================================================\n",
    "--- A/D/gamma\t(revision 1)\n",
    "+++ A/D/gamma\t(working copy)\n",
    "@@ -1 +0,0 @@\n",
    "-This is the file 'gamma'.\n",
  # Delete iota
    "Index: iota\n",
    "===================================================================\n",
    "--- iota\t(revision 1)\n",
    "+++ iota\t(working copy)\n",
    "@@ -1 +0,0 @@\n",
    "-This is the file 'iota'.\n",

  # Add A/D as file
    "Index: A/D\n",
    "===================================================================\n",
    "--- A/D\t(revision 0)\n",
    "+++ A/D\t(working copy)\n",
    "@@ -0,0 +1 @@\n",
    "+New file\n",
    "\ No newline at end of file\n",

  # Add iota as directory
    "Index: iota\n",
    "===================================================================\n",
    "--- iota\t(revision 1)\n",
    "+++ iota\t(working copy)\n",
    "\n",
    "Property changes on: iota\n",
    "___________________________________________________________________\n",
    "Added: k\n",
    "## -0,0 +1 ##\n",
    "+v\n",
    "\ No newline at end of property\n",
  ]))

  expected_output = [
    'D         %s\n' % sbox.ospath('A/D/G/pi'),
    'D         %s\n' % sbox.ospath('A/D/G/rho'),
    'D         %s\n' % sbox.ospath('A/D/G/tau'),
    'D         %s\n' % sbox.ospath('A/D/G'),
    'D         %s\n' % sbox.ospath('A/D/H/chi'),
    'D         %s\n' % sbox.ospath('A/D/H/omega'),
    'D         %s\n' % sbox.ospath('A/D/H/psi'),
    'D         %s\n' % sbox.ospath('A/D/H'),
    'D         %s\n' % sbox.ospath('A/D/gamma'),
    'D         %s\n' % sbox.ospath('A/D'),
    'D         %s\n' % sbox.ospath('iota'),
    'A         %s\n' % sbox.ospath('A/D'),
    'A         %s\n' % sbox.ospath('iota'),
  ]

  svntest.actions.run_and_verify_svn(None, expected_output, [],
                                     'patch', patch_file_path, sbox.wc_dir)

@Issue(4297)
def single_line_mismatch(sbox):
  "single line replacement mismatch"

  sbox.build()
  wc_dir = sbox.wc_dir
  patch_file_path = make_patch_path(sbox)
  svntest.main.file_write(patch_file_path, ''.join([
    "Index: test\n",
    "===================================================================\n",
    "--- test\t(revision 1)\n",
    "+++ test\t(working copy)\n",
    "@@ -1 +1 @@\n",
    "-foo\n",
    "\\ No newline at end of file\n",
    "+bar\n",
    "\\ No newline at end of file\n"
    ]))

  # r2 - Try as plain text with how we encode the symlink
  svntest.main.file_write(sbox.ospath('test'), 'line')
  sbox.simple_add('test')
  sbox.simple_commit()

  # And now this patch should fail, as 'line' doesn't equal 'foo'
  # But yet it shows up as deleted instead of conflicted
  expected_output = [
    'C         %s\n' % sbox.ospath('test'),
    '>         rejected hunk @@ -1,1 +1,1 @@\n',
  ] + svntest.main.summary_of_conflicts(text_conflicts=1)

  svntest.actions.run_and_verify_svn(None, expected_output, [],
                                     'patch', patch_file_path, wc_dir)

@Issue(3644)
def patch_empty_file(sbox):
  "apply a patch to an empty file"

  sbox.build()
  wc_dir = sbox.wc_dir

  patch_file_path = make_patch_path(sbox)
  svntest.main.file_write(patch_file_path, ''.join([
  # patch a file containing just '\n' to 'replacement\n'
    "Index: lf.txt\n",
    "===================================================================\n",
    "--- lf.txt\t(revision 2)\n",
    "+++ lf.txt\t(working copy)\n",
    "@@ -1 +1 @@\n",
    "\n"
    "+replacement\n",

  # patch a new file 'new.txt\n'
    "Index: new.txt\n",
    "===================================================================\n",
    "--- new.txt\t(revision 0)\n",
    "+++ new.txt\t(working copy)\n",
    "@@ -0,0 +1 @@\n",
    "+new file\n",

  # patch a file containing 0 bytes to 'replacement\n'
    "Index: empty.txt\n",
    "===================================================================\n",
    "--- empty.txt\t(revision 2)\n",
    "+++ empty.txt\t(working copy)\n",
    "@@ -0,0 +1 @@\n",
    "+replacement\n",
  ]))

  sbox.simple_add_text('', 'empty.txt')
  sbox.simple_add_text('\n', 'lf.txt')
  sbox.simple_commit()

  expected_output = [
    'U         %s\n' % sbox.ospath('lf.txt'),
    'A         %s\n' % sbox.ospath('new.txt'),
    'U         %s\n' % sbox.ospath('empty.txt'),
    # Not sure if this line is necessary, but it doesn't hurt
    '>         applied hunk @@ -0,0 +1,1 @@ with offset 0\n',
  ]

  # Current result: lf.txt patched ok, new created, empty succeeds with offset.
  svntest.actions.run_and_verify_svn(None, expected_output, [],
                                     'patch', patch_file_path, wc_dir)

  expected_disk = svntest.main.greek_state.copy()
  expected_disk.add({
    'lf.txt'            : Item(contents="\n"),
    'new.txt'           : Item(contents="new file\n"),
    'empty.txt'         : Item(contents="replacement\n"),
  })

  svntest.actions.verify_disk(wc_dir, expected_disk)

@Issue(3362)
def patch_apply_no_fuz(sbox):
  "svn diff created patch should apply without fuz"

  sbox.build(read_only=True)
  wc_dir = sbox.wc_dir

  svntest.main.file_write(sbox.ospath('test.txt'), '\n'.join([
      "line_1",
      "line_2",
      "line_3",
      "line_4",
      "line_5",
      "line_6",
      "line_7",
      "line_8",
      "line_9",
      "line_10",
      "line_11",
      "line_12",
      "line_13",
      "line_14",
      "line_15",
      "line_16",
      "line_17",
      "line_18",
      "line_19",
      "line_20",
      "line_21",
      "line_22",
      "line_23",
      "line_24",
      "line_25",
      "line_26",
      "line_27",
      "line_28",
      "line_29",
      "line_30",
      ""
    ]))
  svntest.main.file_write(sbox.ospath('test_v2.txt'), '\n'.join([
      "line_1a",
      "line_1b",
      "line_1c",
      "line_1",
      "line_2",
      "line_3",
      "line_4",
      "line_5a",
      "line_5b",
      "line_5c",
      "line_6",
      "line_7",
      "line_8",
      "line_9",
      "line_10",
      "line_11a",
      "line_11b",
      "line_11c",
      "line_12",
      "line_13",
      "line_14",
      "line_15",
      "line_16",
      "line_17",
      "line_18",
      "line_19a",
      "line_19b",
      "line_19c",
      "line_20",
      "line_21",
      "line_22",
      "line_23",
      "line_24",
      "line_25",
      "line_26",
      "line_27a",
      "line_27b",
      "line_27c",
      "line_28",
      "line_29",
      "line_30",
      ""
    ]))

  sbox.simple_add('test.txt', 'test_v2.txt')

  result, out_text, err_text = svntest.main.run_svn(None,
                                                    'diff',
                                                    '--old',
                                                    sbox.ospath('test.txt'),
                                                    '--new',
                                                    sbox.ospath('test_v2.txt'))

  patch_path = sbox.ospath('patch.diff')
  svntest.main.file_write(patch_path, ''.join(out_text))

  expected_output = [
    'G         %s\n' % sbox.ospath('test.txt'),
  ]

  # Current result: lf.txt patched ok, new created, empty succeeds with offset.
  svntest.actions.run_and_verify_svn(None, expected_output, [],
                                     'patch', patch_path, wc_dir)

  if not filecmp.cmp(sbox.ospath('test.txt'), sbox.ospath('test_v2.txt')):
    raise svntest.Failure("Patch result not identical")

@XFail()
def patch_lacking_trailing_eol_on_context(sbox):
  "patch file lacking trailing eol on context"

  # Apply a patch where a hunk (the only hunk, in this case) ends with a
  # context line that has no EOL, where this context line is going to
  # match an existing line that *does* have an EOL.
  #
  # Around trunk@1443700, 'svn patch' wrongly removed an EOL from the
  # target file at that position.

  sbox.build(read_only = True)
  wc_dir = sbox.wc_dir

  patch_file_path = make_patch_path(sbox)

  # Prepare
  expected_status = svntest.actions.get_virginal_state(wc_dir, 1)
  expected_disk = svntest.main.greek_state.copy()

  # Prepare the patch
  unidiff_patch = [
    "Index: iota\n",
    "===================================================================\n",
    "--- iota\t(revision 1)\n",
    "+++ iota\t(working copy)\n",
    # TODO: -1 +1
    "@@ -1 +1,2 @@\n",
    "+Some more bytes\n",
    " This is the file 'iota'.", # No trailing \n on this context line!
  ]
  svntest.main.file_write(patch_file_path, ''.join(unidiff_patch))

  iota_contents = "This is the file 'iota'.\n"

  expected_output = [ 'U         %s\n' % sbox.ospath('iota') ]

  # Test where the no-EOL context line is the last line in the target.
  expected_disk.tweak('iota', contents="Some more bytes\n" + iota_contents)
  expected_status.tweak('iota', status='M ')
  expected_skip = wc.State('', { })
  svntest.actions.run_and_verify_patch(wc_dir, os.path.abspath(patch_file_path),
                                       expected_output, expected_disk,
                                       expected_status, expected_skip)

  # Test where the no-EOL context line is a non-last line in the target.
  sbox.simple_revert('iota')
  sbox.simple_append('iota', "Another line.\n")
  expected_disk.tweak('iota', contents="Some more bytes\n" + iota_contents +
                                       "Another line.\n")
  expected_output = [ 'G         %s\n' % sbox.ospath('iota') ]
  svntest.actions.run_and_verify_patch(wc_dir, os.path.abspath(patch_file_path),
                                       expected_output, expected_disk,
                                       expected_status, expected_skip)

def patch_with_custom_keywords(sbox):
  """patch with custom keywords"""

  sbox.build()
  wc_dir = sbox.wc_dir

  sbox.simple_append('A/mu', '$Qq$\nAB\nZZ\n', truncate=True)
  sbox.simple_propset('svn:keywords', 'Qq=%R', 'A/mu')
  sbox.simple_commit()
  expected_disk = svntest.main.greek_state.copy()
  expected_disk.tweak('A/mu',
                      contents='$Qq: %s $\nAB\nZZ\n' % sbox.repo_url)
  svntest.actions.verify_disk(sbox.wc_dir, expected_disk)

  unidiff_patch = [
    "Index: A/mu\n",
    "===================================================================\n",
    "--- A/mu\t(revision 2)\n",
    "+++ A/mu\t(working copy)\n",
    "@@ -1,3 +1,3 @@\n",
    " $Qq$\n",
    "-AB\n",
    "+ABAB\n",
    " ZZ\n"
    ]

  patch_file_path = make_patch_path(sbox)
  svntest.main.file_write(patch_file_path, ''.join(unidiff_patch))

  expected_output = [ 'U         %s\n' % sbox.ospath('A/mu') ]
  expected_disk.tweak('A/mu',
                      contents='$Qq: %s $\nABAB\nZZ\n' % sbox.repo_url)
  expected_status = svntest.actions.get_virginal_state(wc_dir, 1)
  expected_status.tweak('A/mu', wc_rev=2)
  expected_status.tweak('A/mu', status='M ')
  expected_skip = wc.State('', { })
  svntest.actions.run_and_verify_patch(wc_dir, os.path.abspath(patch_file_path),
                                       expected_output, expected_disk,
                                       expected_status, expected_skip)

def patch_git_rename(sbox):
  """--git patch with rename header"""

  sbox.build()
  wc_dir = sbox.wc_dir

  # a simple --git rename patch
  unidiff_patch = [
    "diff --git a/iota b/iota2\n",
    "similarity index 100%\n",
    "rename from iota\n",
    "rename to iota2\n",
  ]

  patch_file_path = make_patch_path(sbox)
  svntest.main.file_write(patch_file_path, ''.join(unidiff_patch))

  expected_output = [ 'A         %s\n' % sbox.ospath('iota2'),
                      'D         %s\n' % sbox.ospath('iota')]
  expected_disk = svntest.main.greek_state.copy()
  expected_disk.remove('iota')
  expected_disk.add({'iota2' : Item(contents="This is the file 'iota'.\n")})
  expected_status = svntest.actions.get_virginal_state(wc_dir, 1)
  expected_status.add({
    'iota2' : Item(status='A ', copied='+', wc_rev='-', moved_from='iota'),
  })
  expected_status.tweak('iota', status='D ', wc_rev=1, moved_to='iota2')
  expected_skip = wc.State('', { })
  svntest.actions.run_and_verify_patch(wc_dir, os.path.abspath(patch_file_path),
                                       expected_output, expected_disk,
                                       expected_status, expected_skip)

              patch_moved_away,
              patch_lacking_trailing_eol,
              patch_change_symlink_target,
              patch_replace_dir_with_file_and_vv,
              single_line_mismatch,
              patch_empty_file,
              patch_apply_no_fuz,
              patch_lacking_trailing_eol_on_context,
              patch_with_custom_keywords,
              patch_git_rename