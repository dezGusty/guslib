# guslib
========

guslib (short for General UtilitieS LIBrary) is a C++ library, licensed under the terms of the MIT software license.

## Introduction
---------------
guslib is a small C++ utility library. It includes other small libraries to provide basic functionality for:
- handling XML files
- handling INI files 
- logging/tracing
- clock and timer

## Author(s)
------------
Augustin Preda

## Status
---------
- Travis Build (Continuous Integration)
  - ![](https://travis-ci.org/dezGusty/guslib.svg?branch=master) (master branch)

## 3rd party libraries
----------------------
- Dirent API for Microsoft Visual Studio (http://softagalleria.net/dirent.php)
      - version: 1.20s
      - licenst: MIT
- SimpleIni (http://code.jellycan.com/simpleini/) 
      - version: 4.14
      - license: MIT 
- TinyXML (http://www.grinninglizard.com/tinyxml/)
      - version: 2.6.2
      - license: zlib/libpng - compatible
- Yasper (http://yasper.sourceforge.net/)
      - version: 1.0.4
      - license: zlib/libpng

## Using the library
--------------------
The library can be used either in a project:
- by including the code directly into the project
- by linking the library dinamically into the project (**recommended**). One needs to **build** the library (or obtain a **built** copy), 
then to include the required headers in the project and also link to the library (.lib) file.
- by linking the library statically into the project. You would nee to manually update your generated project file, or the CMakeLists.txt file for this.

### Recommended environment variables
It is recommended to create an environment variable named **GUSLIB_DIR** to point to the location where the guslib library is located.
E.g. The following paths should be available after defining the **GUSLIB_DIR** environment variable:
* %GUSLIB_DIR%/guslib/guslib/guslibbuildopts.h.in
* %GUSLIB_DIR%/README.md
* %GUSLIB_DIR%/cmake/FindGuslib.cmake

### Building the library
It is recommended to use CMake to build the guslib library.
Launch the CMake GUI, open the %GUSLIB_DIR%/CMakeLists.txt ("Where is the source code" : %GUSLIB_DIR%)
As a guideline, when setting the directory for "Where to build the binaries" specify a new subfolder such as: "%GUSLIB_DIR%/build" or "%GUSLIB_DIR%/build64"
You can customize the build options as you see fit, but the defaults should be good enough for most use cases.

### Using the library in a project Visual Studio
Add the following directory to the "Additional Include Directories" entry (C/C++ -> General):
* $(GUSLIB_DIR)\guslib;

Adjust and add the following directory to the "Additional Library Directories" entry (Linker -> General):
* $(GUSLIB_DIR)/build/lib/
(**adjust the entry based on what you specify in "Where to build the binaries" when building the library with CMake**)

Add the following library to the "Additional Dependencies" entry (Linker -> Input)
* guslib.lib

Keep in mind that the recommended use of the library would also imply (at least under Windows) copying the shared library binaries (dlls) to your project's output.

### Using the library with CMake
If you are using CMake in your project, you can add the files in the cmake directory to your project's cmake modules.
FindGuslib.cmake will facilitate the finding of the library's location.


## History
----------
### 2015.01.29
- Version 1.8.0
- Added a small helper class for UAC elevation.
