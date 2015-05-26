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
//   Last change:  $LastChangedDate: 2014-07-04 08:56:45 +0300 (V, 04 iul. 2014) $
//   Revision:    $Revision: 663 $

//
// Includes
//

//
// Own header.
//
#include "guslib/util/config/propertygroup.h"

//
// C++ system includes
//

#include <string>
#include <vector>

//
// This library's headers
//

#include "guslib/trace/trace.h"
#include "guslib/util/config/property.h"

namespace guslib
{
  namespace config
  {
    //
    // Opaque pointer implementation for property group.
    //
    class PropertyGroup::Impl
    {
    public:
      std::string name_;

      std::vector <Property> contained_properties_;

      bool savable_;

      Impl(const std::string& name, bool savable)
        : name_(name)
        , savable_(savable)
        , contained_properties_(0)
      {
        GTRACE(8, "[impl] Property group CTOR: " << name_);
      }

      explicit Impl(const PropertyGroup::Impl& rhs)
        : name_(rhs.name_)
        , savable_(rhs.savable_)
        , contained_properties_(rhs.contained_properties_)
      {
        GTRACE(8, "[impl] Property group impl COPY CTOR: " << name_);
      }

      ~Impl()
      {
        GTRACE(8, "[impl] Property group impl DTOR: " << name_);
        contained_properties_.clear();
      }
    };

    //
    // Constructor with name.
    //
    PropertyGroup::PropertyGroup(const std::string& name)
      : impl_(new PropertyGroup::Impl(name, true))
    {
      GTRACE(7, "Property Group CTor [" << getName() << "]");
    }

    PropertyGroup::PropertyGroup()
      : impl_(new PropertyGroup::Impl("general", true))
    {
      GTRACE(7, "Property Group CTor [" << getName() << "]");
    }

    PropertyGroup::PropertyGroup(const PropertyGroup& rhs)
      : impl_(new PropertyGroup::Impl(*rhs.impl_))
    {
      GTRACE(7, "Property Group COPY CTor [" << getName() << "]");
    }

    PropertyGroup::~PropertyGroup()
    {
      GTRACE(7, "Property Group DTor [" << getName() << "]");
      delete impl_;
    }

    const std::string& PropertyGroup::getName() const
    {
      return impl_->name_;
    }

    const std::vector <Property>& PropertyGroup::getProperties() const
    {
      return impl_->contained_properties_;
    }

    const bool PropertyGroup::isSavable() const
    {
      return impl_->savable_;
    }

    void PropertyGroup::setSavable(bool rhs)
    {
      impl_->savable_ = rhs;
    }

    void PropertyGroup::addProperty(const Property & prop)
    {
      impl_->contained_properties_.push_back(prop);
    }

    void PropertyGroup::operator=(const PropertyGroup &rhs)
    {
      this->impl_ = new PropertyGroup::Impl(*rhs.impl_);
    }


    Property& PropertyGroup::operator[](const std::string& name)
    {
      for (Property& item : impl_->contained_properties_)
      {
        if (item.getName() == name)
        {
          return item;
        }
      }

      // if this region is reached, no such property was found... what to do?
      // create an empty one.

      impl_->contained_properties_.push_back(Property(name));
      return impl_->contained_properties_.back();
    }
  }
}   // end namespace guslib

