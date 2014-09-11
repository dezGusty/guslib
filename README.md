# guslib
========

guslib (short for General UtilitieS LIBrary) is a C++ library, licensed under the terms of the MIT software license.

## Introduction
===============
guslib is a small C++ utility library. It includes other small libraries to provide basic functionality for:
- handling XML files
- handling INI files 
- logging/tracing
- clock and timer

## Author(s)
============
Augustin Preda

## 3rd party libraries
======================
- Dirent API for Microsoft Visual Studio (http://softagalleria.net/dirent.php)
      - version:
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
====================
The library can be used either in a project:
- by including the code directly into the project
- by linking the library dinamically into the project. One needs to generate the library (or obtain a generated copy), 
then to include the required headers in the project and also link to the library (.lib) file.
- by linking the library statically into the project. You would nee to manually update your generated project file, or the CMakeLists.txt file for this.
