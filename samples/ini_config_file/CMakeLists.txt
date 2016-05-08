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

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET (guslibtest_project_name config_file_sample)
PROJECT (${guslibtest_project_name})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake/;${CMAKE_MODULE_PATH}")
SET(guslibtest_project_type SHARED)

MESSAGE(STATUS "Building ${guslibtest_project_name}")
MESSAGE(STATUS "")

SET(guslibtest_project_DEPENDENCIES "guslib")

# Preprocessor definitions
ADD_DEFINITIONS(-DUNICODE -D_UNICODE )

# 
# -------------------------------------------------- File section ------------------------------------------------------
#

SET(SRCS
  ./src/config_sample_main.cpp
)

# More include directories.
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../guslib)


ADD_EXECUTABLE(${guslibtest_project_name} 
    ${SRCS})

#
# Link to dependencies
#
TARGET_LINK_LIBRARIES(${guslibtest_project_name} 
      ${guslibtest_project_DEPENDENCIES} )

#
# Set the default location of the output executable file.
#
IF (WIN32)
    IF (CMAKE_BUILD_TYPE STREQUAL "Release")
      SET (guslibtest_project_out_dir "../../bin/Release")
    ELSE ()
      IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
        SET (guslibtest_project_out_dir "../../bin/Debug")
      ELSE ()
        SET (guslibtest_project_out_dir "../../bin")
      ENDIF ()
    ENDIF ()
ELSE()
    SET (guslibtest_project_out_dir "bin")
ENDIF()

SET_TARGET_PROPERTIES (${guslibtest_project_name} 
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${guslibtest_project_out_dir}
        CXX_STANDARD 11
    	CXX_STANDARD_REQUIRED YES
)

