#ifndef GUSLIB_UACELEVATION_H
#define GUSLIB_UACELEVATION_H

//   This file is part of the guslib library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2015  Augustin Preda (thegusty999@gmail.com)
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.
//
//   Windows User Account Control (UAC) Elevation class.
//   Based on the sample code
//   https://code.msdn.microsoft.com/windowsdesktop/CppUACSelfElevation-981c0160
//   and here
//   http://jagt.github.io/clumsy/
//
//   Last change:  $LastChangedDate$
//   Revision:    $Revision$


//
// Includes
//

//
// Platform specific definitions and overall build options for the library.
//
#include <guslib/guslibbuildopts.h>

namespace guslib
{
  /**
    A class to assist with the permission elevation for the Windows User Account Control (UAC).
    This should allow the user to request the application to run with elevated permissions, so
    that the user does not need to manually right-click and select "Run as Administrator" for
    the application to access certain features.
    Please note that the user will still need to manually accept the process elevation.
  */
  class GUSLIB_EXPORT_SYMBOL UAC
  {
  public:
    /**
      Check to see whether the application is running as an administrator.
      The current user needs to be in the administrators group.
      @return True if the application is running with administrator rights.
    */
    static bool isRunningAsAdmin();

    /**
      Checks to see whether the application is running with elevated permissions.
      @return True if the application has elevated permissions, False otherwise.
    */
    static bool isElevated();

    /**
      Attempt to relaunch the current process, while also calling for a
      manual elevation from the Windows User Account Control.
      @param Specifies if the application should quit if the user does not allow the elevation.
      @return True if the application should quit, False otherwise.
    */
    static bool relaunchForManualElevation(bool quitIfElevationDenied);
  };
}

#endif  // GUSLIB_UACELEVATION_H
