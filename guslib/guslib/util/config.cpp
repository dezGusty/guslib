//   This file is part of the guslib library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2014  Augustin Preda (thegusty999@gmail.com)
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
//   Application configuration utility.

//
// Includes
//

//
// Own header.
//
#include "guslib/util/config.h"

//
// This library's headers
//

// Add the configuration class.
#include "guslib/util/config/configuration.h"

// Add the "ini" configuration to the factory.
#include "guslib/util/config/iniconfig.h"

namespace guslib
{
  bool Config::calledInit_ = false;

  //
  //  Initialize the factory.
  //
  void Config::init()
  {
    if (calledInit_)
    {
      // ran once, no need to run again!
      return;
    }

    calledInit_ = true;
    config::LoaderFactory::getPtr()->Register("ini", config::IniLoader::createLoader);
  }

  //
  //  Perform cleanup for the factory.
  //
  void Config::terminate()
  {
    if (false == calledInit_)
    {
      return;
    }

    config::LoaderFactory::getPtr()->Unregister("ini");
    config::LoaderFactory::destroy();
  }
}
