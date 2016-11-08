#ifndef GUSLIB_UTIL_PORTTESTER_H_
#define GUSLIB_UTIL_PORTTESTER_H_

//   This file is part of the guslib library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2016  Augustin Preda (thegusty999@gmail.com)
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
//   A simple port tester class.
//

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
    Provides support for testing whether ports are used or not.
  */
  class PortTester
  {
  public:

    /**
     * Checks to see whether a TCP port can be opened.
     * @param address The address to connect to.
     * @param port_number The port number to use.
     * @return True if the port can be opened (port currently closed)
     *         False otherwise (port opened and in use; some error scenario)
     * @authors Augustin Preda.
     */
    static GUSLIB_EXPORT_SYMBOL bool CanOpenTCPPort(const char* address, unsigned int port_number);
  };
}

#endif  // GUSLIB_UTIL_PORTTESTER_H_
