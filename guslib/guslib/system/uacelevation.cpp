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
// Own header
//
#include "guslib/system/uacelevation.h"

//
// C system headers
//

#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
#include <guslib/system/systemwindowsfwd.h>
#else
# pragma message("Warning: UAC elevation not defined for non-windows environments")
#endif

//
// C++ system headers
//
#include <exception>

namespace guslib
{
  /**
    Check to see whether the application is running as an administrator.
    The current user needs to be in the administrators group.
    @return True if the application is running with administrator rights.
  */
  bool UAC::isRunningAsAdmin()
  {
#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
    BOOL isBeingRunAsAdmin = FALSE;
    DWORD dwError = ERROR_SUCCESS;
    PSID ptrAdministratorsGroup = NULL;

    // Allocate and initialize a SID of the administrators group.
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(
          &NtAuthority,
          2,
          SECURITY_BUILTIN_DOMAIN_RID,
          DOMAIN_ALIAS_RID_ADMINS,
          0, 0, 0, 0, 0, 0,
          &ptrAdministratorsGroup))
    {
      dwError = GetLastError();

      // Centralized cleanup for all allocated resources.
      if (ptrAdministratorsGroup)
      {
        FreeSid(ptrAdministratorsGroup);
        ptrAdministratorsGroup = NULL;
      }

      // Throw the error if something failed in the function.
      if (ERROR_SUCCESS != dwError)
      {
        throw dwError;
      }
    }

    // Determine whether the SID of administrators group is enabled in
    // the primary access token of the process.
    if (!CheckTokenMembership(NULL, ptrAdministratorsGroup, &isBeingRunAsAdmin))
    {
      dwError = GetLastError();

      // Centralized cleanup for all allocated resources.
      if (ptrAdministratorsGroup)
      {
        FreeSid(ptrAdministratorsGroup);
        ptrAdministratorsGroup = NULL;
      }

      // Throw the error if something failed in the function.
      if (ERROR_SUCCESS != dwError)
      {
        throw dwError;
      }
    }

    return isBeingRunAsAdmin != 0;
#else
    return false;
#endif
  }


  /**
    Checks to see whether the application is running with elevated permissions.
    @return True if the application has elevated permissions, False otherwise.
  */
  bool UAC::isElevated()
  {
#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
    bool elevated = false;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) 
    {
      TOKEN_ELEVATION Elevation;
      DWORD cbSize = sizeof(TOKEN_ELEVATION);
      if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) 
      {
        elevated = Elevation.TokenIsElevated != 0;
      }
    }

    if (hToken) 
    {
      CloseHandle(hToken);
    }

    return elevated;
#else
    return false;
#endif
  }
  

  /**
    Attempt to relaunch the current process, while also calling for a
    manual elevation from the Windows User Account Control.
    @param Specifies if the application should quit if the user does not allow the elevation.
    @return True if the application should quit, False otherwise.
  */
  bool UAC::relaunchForManualElevation(bool quitIfElevationDenied)
  {
#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
    wchar_t szPath[MAX_PATH];
    if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath)))
    {
      // Launch itself as administrator.
      SHELLEXECUTEINFO sei = { sizeof(sei) };
      sei.lpVerb = L"runas";
      sei.lpFile = szPath;
      sei.nShow = SW_NORMAL;

      if (!ShellExecuteEx(&sei))
      {
        DWORD dwError = GetLastError();
        if (dwError == ERROR_CANCELLED)
        {
          // The user refused the elevation.
          return quitIfElevationDenied;
        }

        // Some other error.

        return false;
      }
      else
      {
        // Managed to launch a second instance of itself...
        // Ok... let's quit.
        // This is a quick and dirty solution; no cleanup of used resources (handles/open connections/ports).
        // Note: look at guslib/system/apprestart.h for a more thorough use of a restarter.
        return true;
      }
    }

    return false;
#else
    return false;
#endif
  }
}
