#!/usr/bin/env python
# -*- coding: utf-8 -*-


import unittest
import time
import inspect
from os import path

from RappCloud.Utils import datatypeassert as typeassert


class DatatypeAssert(unittest.TestCase):
    # Overwrite
    def setUp(self):
        self.startTime = time.time()


    def tearDown(self):
        t = time.time() - self.startTime
        print "%s: %.3f" % (self.id(), t)


    # def test_decorator_args(self):
        # @typeassert(int, int, int)
        # def fn(a, b, c):
            # pass
        # fn(1, 2, 3)


    # def test_decorator_kwargs_buildin_types(self):
        # @typeassert(a=int, b=str, c=dict, d=list, e=tuple)
        # def fn(a=1, b="1", c={'x': 1, 'y': '1'}, d=[1, 2], e=("test", 1)):
            # return [a, b, c, d, e]
        # fn(a=2, b="2", c={'x': 5, 'y': '3'}, d=[3, 5], e=(2, "test"))


    # def test_decorator_kwargs_general(self):
        # @typeassert(a=int, b=str, c=dict, d=list)
        # def fn(a=1, b='', c={}, d=[]):
            # return [a, b, c, d]

        # a, b, c, d = fn(a=2, b="1", c={'y': 'test'}, d=[1, 2])
        # self.assertEqual(a, 2)
        # self.assertEqual(b, "1")
        # self.assertEqual(c, {'y': 'test'})
        # self.assertEqual(d, [1, 2])
        # a, b, c, d = fn(a=5, b="3", c={'x': 'test2'})
        # self.assertEqual(a, 5)
        # self.assertEqual(b, "3")
        # self.assertEqual(c, {'x': 'test2'})
        # self.assertEqual(d, [])


    # def test_decorator_args_buildin_types(self):
        # @typeassert(int, str, dict, list)
        # def fn(a, b, c, d):
            # pass
        # fn(1, "1", {'y': ''}, [1, 2])


    # @unittest.expectedFailure
    # def test_decorator_args_wrong_type(self):
        # @typeassert(int, str, dict, list, tuple)
        # def fn(a, b, c, d, e):
            # pass
        # fn(int(), str(), int(), list(), tupe())


    @unittest.expectedFailure
    def test_decorator_kwargs_wrong_type(self):
        @typeassert(a=int, b=str, c=dict, d=list, e=tuple)
        def fn(a=1, b=1, c=1, d=1, e=1):
            pass
        fn(a=int(), b=str(), c=int(), d=list(), e=tuple())


if __name__ == '__main__':
    # unittest.main(verbosity=2)
    suite = unittest.TestLoader().loadTestsFromTestCase(DatatypeAssert)
    unittest.TextTestRunner(verbosity=2).run(suite)
