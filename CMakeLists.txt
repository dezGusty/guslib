#-------------------------------------------------------------------
# This file is part of the CMake build system for the guslib library
#-------------------------------------------------------------------
# The MIT License
# Copyright (C) 2010-2015  Augustin Preda (thegusty999@gmail.com)
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#-------------------------------------------------------------------

# Configure Components build
cmake_minimum_required(VERSION 3.0)

# 
# Specify some user configurable options
# 
OPTION(GUSLIB_BUILD_CORE "Build the core lib" ON)
OPTION(GUSLIB_BUILD_SAMPLES "Build the sample projects" ON)
OPTION(GUSLIB_BUILD_TESTS "Build the tests (requires the google test framework)" ON)


PROJECT(guslib)

IF (GUSLIB_BUILD_CORE)
  ADD_SUBDIRECTORY(guslib)
ENDIF ()


IF (GUSLIB_BUILD_SAMPLES)
	ADD_SUBDIRECTORY(samples)
ENDIF ()

IF (GUSLIB_BUILD_TESTS)
	ADD_SUBDIRECTORY(tests)
ENDIF ()
