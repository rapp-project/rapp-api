#!/usr/bin/env python
# -*- coding: utf-8 -*-


import unittest
import time
import inspect
from os import path

from RappCloud.Utils import datatypeassert as typeassert


class DatatypeAssert(unittest.TestCase):

    def test_args(self):
        """!

        Decorator: args
        Function Declaration: args
        Function Call: args

        Status: Success
        """
        _this = self
        @typeassert(int, float, str, unicode, basestring, object, dict,
                    list, tuple, set)
        def fn(a, b, c, d, e, f, g, h, i, j):
            _this.assertIsInstance(a, int)
            _this.assertIsInstance(b, float)
            _this.assertIsInstance(c, str)
            _this.assertIsInstance(d, unicode)
            _this.assertIsInstance(e, basestring)
            _this.assertIsInstance(f, object)
            _this.assertIsInstance(g, dict)
            _this.assertIsInstance(h, list)
            _this.assertIsInstance(i, tuple)
            _this.assertIsInstance(j, set)

        fn(int(), float(), str(), unicode(), '', object(),
           dict(), list(), tuple(), set())
        fn(int(), float(), str(), unicode(), u'', object(),
           dict(), list(), tuple(), set())


    def test_kwargs(self):
        """!

        Decorator: kwargs
        Function Declaration: kwargs
        Function Call: kwargs

        Status: Success
        """
        _this = self
        @typeassert(int, float, str, unicode, basestring, object, dict,
                    list, tuple, set)
        def fn(a=int(), b=float(), c=str(), d=unicode(), e='', f=object(),
               g=dict(), h=list(), i=tuple(), j=set()):
            _this.assertIsInstance(a, int)
            _this.assertIsInstance(b, float)
            _this.assertIsInstance(c, str)
            _this.assertIsInstance(d, unicode)
            _this.assertIsInstance(e, basestring)
            _this.assertIsInstance(f, object)
            _this.assertIsInstance(g, dict)
            _this.assertIsInstance(h, list)
            _this.assertIsInstance(i, tuple)
            _this.assertIsInstance(j, set)

        fn(a=int(), b=float(), c=str(), d=unicode(), e='', f=object(),
           g=dict(), h=list(), i=tuple(), j=set())
        fn(a=int(), b=float(), c=str(), d=unicode(), e=u'', f=object(),
           g=dict(), h=list(), i=tuple(), j=set())
        fn(a=int(), b=float(), c=str())


    @unittest.expectedFailure
    def test_args_wrong_type(self):
        """!

        Decorator: args
        Function Declaration: args
        Function Call: args

        Status: Expected Failure due to passing int() as 3rd argument
        """
        _this = self
        @typeassert(int, float, str, unicode, basestring, object, dict,
                    list, tuple, set)
        def fn(a, b, c, d, e, f, g, h, i, j):
            pass

        fn(int(), float(), str(), unicode(), '', object(),
           dict(), list(), tuple(), int())


    @unittest.expectedFailure
    def test_kwargs_wrong_type(self):
        """!

        Decorator: kwargs
        Function Declaration: kwargs
        Function Call: kwargs

        Status: Expected Failure due to passing int() as 3rd argument
        to the function call
        """
        _this = self
        @typeassert(int, float, str, unicode, basestring, object, dict,
                    list, tuple, set)
        def fn(a=int(), b=float(), c=str(), d=unicode(), e='', f=object(),
               g=dict(), h=list(), i=tuple(), j=set()):
            _this.assertIsInstance(a, int)
            _this.assertIsInstance(b, float)
            _this.assertIsInstance(c, str)
            _this.assertIsInstance(d, unicode)
            _this.assertIsInstance(e, basestring)
            _this.assertIsInstance(f, object)
            _this.assertIsInstance(g, dict)
            _this.assertIsInstance(h, list)
            _this.assertIsInstance(i, tuple)
            _this.assertIsInstance(j, set)

        fn(a=int(), b=float(), c=str(), d=unicode(), e='', f=object(),
           g=dict(), h=list(), i=int(), j=set())



    def test_dec_kwargs_fun_kwargs_pass_args(self):
        """!

        Decorator: kwargs
        Function Declaration: kwargs
        Function Call: args

        Status: Expected Failure due to passing int() as 3rd argument
        to the function call
        """
        _this = self
        @typeassert(a=int, b=float, c=str, d=unicode, e=basestring, f=object,
                    g=dict, h=list, i=tuple, j=set)
        def fn(a=int(), b=float(), c=str(), d=unicode(), e='', f=object(),
               g=dict(), h=list(), i=tuple(), j=set()):
            _this.assertIsInstance(a, int)
            _this.assertIsInstance(b, float)
            _this.assertIsInstance(c, str)
            _this.assertIsInstance(d, unicode)
            _this.assertIsInstance(e, basestring)
            _this.assertIsInstance(f, object)
            _this.assertIsInstance(g, dict)
            _this.assertIsInstance(h, list)
            _this.assertIsInstance(i, tuple)
            _this.assertIsInstance(j, set)

        fn(int(), float(), str(), unicode(), '', object(),
           dict(), list(), tuple(), set())


    @unittest.expectedFailure
    def test_dec_kwargs_fun_kwargs_pass_args_wrong_type(self):
        """!

        Decorator: kwargs
        Function Declaration: kwargs
        Function Call: args

        Status: Expected Failure due to passing int() as 3rd argument
        to the function call
        """
        _this = self
        @typeassert(a=int, b=float, c=str, d=unicode, e=basestring, f=object,
                    g=dict, h=list, i=tuple, j=set)
        def fn(a=int(), b=float(), c=str(), d=unicode(), e='', f=object(),
               g=dict(), h=list(), i=tuple(), j=set()):
            pass

        fn(int(), float(), str(), unicode(), '', object(),
           dict(), list(), tuple(), int())


    def test_dec_args_fun_kwargs_pass_args(self):
        """!

        Decorator: args
        Function Declaration: kwargs
        Function Call: args

        Status: Success
        """
        _this = self
        @typeassert(int, float, str, unicode, basestring, object, dict,
                    list, tuple, set)
        def fn(a=int(), b=float(), c=str(), d=unicode(), e='', f=object(),
               g=dict(), h=list(), i=tuple(), j=set()):
            _this.assertIsInstance(a, int)
            _this.assertIsInstance(b, float)
            _this.assertIsInstance(c, str)
            _this.assertIsInstance(d, unicode)
            _this.assertIsInstance(e, basestring)
            _this.assertIsInstance(f, object)
            _this.assertIsInstance(g, dict)
            _this.assertIsInstance(h, list)
            _this.assertIsInstance(i, tuple)
            _this.assertIsInstance(j, set)

        fn(int(), float(), str(), unicode(), '', object(),
           dict(), list(), tuple(), set())


    @unittest.expectedFailure
    def test_decorator_args_kwargs_args_wrong_type(self):
        """!

        Decorator: args
        Function Declaration: kwargs
        Function Call: args

        Status: Expected Failure due to passing int() as 3rd argument
        to the function call
        """
        _this = self
        @typeassert(int, float, str, unicode, basestring, object, dict,
                    list, tuple, set)
        def fn(a=int(), b=float(), c=str(), d=unicode(), e='', f=object(),
               g=dict(), h=list(), i=tuple(), j=set()):
            _this.assertIsInstance(a, int)
            _this.assertIsInstance(b, float)
            _this.assertIsInstance(c, str)
            _this.assertIsInstance(d, unicode)
            _this.assertIsInstance(e, basestring)
            _this.assertIsInstance(f, object)
            _this.assertIsInstance(g, dict)
            _this.assertIsInstance(h, list)
            _this.assertIsInstance(i, tuple)
            _this.assertIsInstance(j, set)

        fn(int(), float(), int(), unicode(), '', object(),
           dict(), list(), tuple(), set())


    def test_dec_args_fun_kwargs_pass_kwargs(self):
        """!

        Decorator: args
        Function Declaration: kwargs
        Function Call: kwargs

        Status: Success
        """
        _this = self
        @typeassert(int, float, str, unicode, basestring, object, dict,
                    list, tuple, set)
        def fn(a=int(), b=float(), c=str(), d=unicode(), e='', f=object(),
               g=dict(), h=list(), i=tuple(), j=set()):
            _this.assertIsInstance(a, int)
            _this.assertIsInstance(b, float)
            _this.assertIsInstance(c, str)
            _this.assertIsInstance(d, unicode)
            _this.assertIsInstance(e, basestring)
            _this.assertIsInstance(f, object)
            _this.assertIsInstance(g, dict)
            _this.assertIsInstance(h, list)
            _this.assertIsInstance(i, tuple)
            _this.assertIsInstance(j, set)

        fn(a=int(), b=float(), c=str(), d=unicode(), e=u'', f=object(),
           g=dict(), h=list(), i=tuple(), j=set())
        fn(a=int(), b=float(), c=str(), d=unicode(), e=u'', f=object())


    @unittest.expectedFailure
    def test_dec_args_fun_kwargs_pass_kwargs_wrong_type(self):
        """!

        Decorator: args
        Function Declaration: kwargs
        Function Call: kwargs

        Status: Expected failure due to passing int() as last argument {e}
        """
        _this = self
        @typeassert(int, float, str, unicode, basestring, object, dict,
                    list, tuple, set)
        def fn(a=int(), b=float(), c=str(), d=unicode(), e='', f=object(),
               g=dict(), h=list(), i=tuple(), j=set()):
            _this.assertIsInstance(a, int)
            _this.assertIsInstance(b, float)
            _this.assertIsInstance(c, str)
            _this.assertIsInstance(d, unicode)
            _this.assertIsInstance(e, basestring)
            _this.assertIsInstance(f, object)
            _this.assertIsInstance(g, dict)
            _this.assertIsInstance(h, list)
            _this.assertIsInstance(i, tuple)
            _this.assertIsInstance(j, set)

        fn(a=int(), b=float(), c=str(), d=str(), e=u'', f=object(),
           g=dict(), h=list(), i=tuple(), j=set())


    def test_dec_args_fun_args_pass_kwargs(self):
        """!

        Decorator: args
        Function Declaration: args
        Function Call: kwargs

        Status: Success
        """
        _this = self
        @typeassert(int, float, str, unicode, basestring, object, dict,
                    list, tuple, set)
        def fn(a, b, c, d, e, f, g, h, i, j):
            _this.assertIsInstance(a, int)
            _this.assertIsInstance(b, float)
            _this.assertIsInstance(c, str)
            _this.assertIsInstance(d, unicode)
            _this.assertIsInstance(e, basestring)
            _this.assertIsInstance(f, object)
            _this.assertIsInstance(g, dict)
            _this.assertIsInstance(h, list)
            _this.assertIsInstance(i, tuple)
            _this.assertIsInstance(j, set)

        fn(a=int(), b=float(), c=str(), d=unicode(), e=u'', f=object(),
           g=dict(), h=list(), i=tuple(), j=set())


    @unittest.expectedFailure
    def test_dec_args_fun_args_pass_kwargs_wrong_type(self):
        """!

        Decorator: args
        Function Declaration: args
        Function Call: kwargs

        Status: Expected failure due to passing list to argument {e}
        """
        _this = self
        @typeassert(int, float, str, unicode, basestring, object, dict,
                    list, tuple, set)
        def fn(a, b, c, d, e, f, g, h, i, j):
            pass

        fn(a=float(), b=float(), c=str(), d=unicode(), e=u'', f=object(),
           g=dict(), h=list(), i=tuple(), j=set())




if __name__ == '__main__':
    # unittest.main(verbosity=2)
    suite = unittest.TestLoader().loadTestsFromTestCase(DatatypeAssert)
    unittest.TextTestRunner(verbosity=2).run(suite)
