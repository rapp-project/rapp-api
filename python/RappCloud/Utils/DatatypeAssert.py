#!/usr/bin/env python
# -*- coding: utf-8 -*-


# Copyright 2016 RAPP

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

    #http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Authors: Konstantinos Panayiotou
# contact: klpanagi@gmail.com


## @file Utils/DataTypeAssert.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


# Import functools.wraps to wrap functions
from functools import wraps
import inspect


def datatypeassert(*decargs, **deckwargs):

    def decorador(fn):


        @wraps(fn)
        def wrapper(*args, **kwargs):
            # Bind *args and **kwargs to the input function
            _boundFn = inspect.getcallargs(fn, *args, **kwargs)
            # Map decorators *args and **kwargs to the function declaration *args
            # and **kwargs.
            _boundDec = inspect.getcallargs(fn, *decargs, **deckwargs)

            # Iterate through _boundDec: Decorators arguments
            for key, value in _boundDec.iteritems():
                if key not in _boundFn:
                    # If keyword decorador argument does not exist in
                    # function kwargs, skip.
                    continue
                if not isinstance(_boundFn[key], value):
                    # Raise TypeError Exception if passed argument type
                    # does not correspond to the value forced by the
                    # decorator
                    raise TypeError(
                        'Argument {0} must be of data type {1}'.format(key, value)
                        )

            return fn(*args, **kwargs)
        return wrapper
    return decorador

