#!/usr/bin/env python
# -*- coding: utf-8 -*-


import unittest
import time
import inspect
from os import path

from RappCloud.Objects import (
    Payload,
    File)

global testdatadir
testdatadir = path.realpath(
    path.join(path.dirname(path.realpath(__file__)), '../../testdata')
    )



class TestFile(unittest.TestCase):
    # Overwrite
    def setUp(self):
        self.startTime = time.time()


    def tearDown(self):
        t = time.time() - self.startTime
        print "%s: %.3f" % (self.id(), t)


    def test_file_resolve_path(self):
        f = File(filepath='~/Desktop/../Lenna.png')
        self.assertEqual(f.path, path.expanduser('~/Lenna.png'))
        f.path = '~/test'
        self.assertEqual(f.path, path.expanduser('~/test'))
        f.path = '../../testdata/Lenna.png'
        self.assertEqual(f.path, '../../testdata/Lenna.png')


    def test_make_tuple(self):
        f = File(filepath=path.join(testdatadir, 'Lenna.png'))
        f.make_tuple()

    @unittest.expectedFailure
    def test_wrong_filepath_constructor(self):
        f = File(filepath='/non-exist-file')
        f.make_tuple()


    @unittest.expectedFailure
    def test_wrong_filepath(self):
        f = File()
        f.path = '/non-exist-file'
        f.make_tuple()



if __name__ == '__main__':
    # unittest.main(verbosity=2)
    suite = unittest.TestLoader().loadTestsFromTestCase(TestFile)
    unittest.TextTestRunner(verbosity=2).run(suite)
