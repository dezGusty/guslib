#ifndef GUSLIB_UTIL_CONFIG_PROPERTYGROUP_H_
#define GUSLIB_UTIL_CONFIG_PROPERTYGROUP_H_

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
//   Application configuration utility.
//

//
// Includes
//

//
// Platform specific definitions and overall build options for the library.
//
#include <guslib/guslibbuildopts.h>

//
// C++ system includes
//

#include <string>
#include <vector>

//
// This library's headers
//

#include "guslib/util/config/property.h"

namespace guslib
{
  namespace config
  {
    //
    //  A group of configuration properties.
    //  E.g. A set of network related application options could be a group. A set of UI related options could be
    //  another group.
    // 
    class GUSLIB_EXPORT_SYMBOL PropertyGroup
    {
    private:
      // Opaque pointer.
      class Impl;
      Impl* impl_;

    public:
      //
      // Default constructor.
      //
      PropertyGroup();

      //
      // Constructor with name.
      //
      explicit PropertyGroup(const std::string &name);

      //
      //  Copy constructor. Needed to copy the pimpl.
      //
      PropertyGroup(const PropertyGroup& rhs);

      //
      // Destructor.
      //
      ~PropertyGroup();

      //
      // Assignment operator overloading.
      //
      void operator=(const PropertyGroup &rhs);

      //
      // Property getter via operator.
      //
      Property& operator[](const std::string& name);

      //
      // Property getter.
      //
      Property& getPropertyByName(const std::string& name);

      void addProperty(const Property & prop);

      const std::string& getName() const;

      const std::vector <Property>& getProperties() const;

      const bool isSavable() const;

      void setSavable(bool rhs);
    };
  }   // end namespace config
}   // end namespace guslib

#endif  // GUSLIB_UTIL_CONFIG_PROPERTYGROUP_H_
