# This file is part of the guslib library, licensed under the terms of the MIT License.
# 
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

# 
# Use this file to locate the guslib library via CMake.
# Add this file to your project's cmake modules folder if you want to have an easier
# time linking to the library as a shared lib/dll.
# Note: it's recommended to define the environment variable GUSLIB_DIR to point to the
# location of the guslib directory.
# 

INCLUDE(${CMAKE_SOURCE_DIR}/CMake/HandleLibraryTypes.cmake)

# Set the paths to search for as possible locations of the library.
SET (GUSLIB_SEARCH_PATH 
        $ENV{GUSLIB_DIR}
        $ENV{GUSLIB_HOME}
        $ENV{GUSLIB_ROOT}
        ${PROJECT_SOURCE_DIR}/../guslib
        ${PROJECT_SOURCE_DIR}/../
        ${PROJECT_SOURCE_DIR}/../../guslib
)

FIND_PATH(GUSLIB_INCLUDE_DIR guslib/guslib_version.hpp
    PATHS  ${GUSLIB_SEARCH_PATH}
    PATH_SUFFIXES guslib
                guslib/guslib
)

#
# Locate the link libraries (lib files)
# A recommended setting is to use a "build" directory to build guslib with CMake.
#     E.g. Where is the source code: c:/code/guslib
#          Where to build the binaries: c:/code/guslib/build
#
FIND_LIBRARY(GUSLIB_LIBRARY_OPTIMIZED
    NAMES guslib
    PATHS ${GUSLIB_SEARCH_PATH}
    PATH_SUFFIXES bin/Release lib libs bin
                  bin/Release-DLL-Win32 
                  build/lib build/Release
                  build/lib/Release  
                  lib/Relase /lib/Release
)

FIND_LIBRARY(GUSLIB_LIBRARY_DEBUG
    NAMES guslib
    PATHS ${GUSLIB_SEARCH_PATH}
    PATH_SUFFIXES bin/Debug lib libs bin
                  bin/Debug-DLL-Win32 
                  build/lib build/Debug
                  build/lib/Debug 
                  lib/Debug /lib/Debug
)

#
# Locate the shared libraries / binaries (dll files)
#
FIND_FILE (GUSLIB_BINARY_REL 
    NAMES guslib.dll
    HINTS ${GUSLIB_SEARCH_PATH}
    PATH_SUFFIXES "" lib libs bin Release 
                  build/bin/Release build/bin 
                  build/lib build/Release 
                  bin/Release-DLL-Win32 lib/Relase /lib/Release
)
 
FIND_FILE (GUSLIB_BINARY_DBG
    NAMES guslib.dll
    HINTS ${GUSLIB_SEARCH_PATH}
    PATH_SUFFIXES "" lib libs bin Debug
                  build/bin/Debug build/bin
                  build/lib build/Debug
                  bin/Debug-DLL-Win32 lib/Debug /lib/Debug
)
 
# Collect debug and optimized libraries.
HANDLE_LIBRARY_TYPES(GUSLIB)

