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
// Own header
//
#include "guslib/util/config/configuration.h"

//
// C++ system headers
//
#include <map>
#include <memory>
#include <string>
#include <vector>

//
// This libraries' headers
//
#include "guslib/common/simpleexception.h"
#include "guslib/trace/trace.h"
#include "guslib/util/config/loader.h"
#include "guslib/util/config.h"
#include "guslib/util/stringutil.h"



namespace guslib
{
  //
  // Store the factory instance here.
  //
  GUSLIB_EXPIMP_TEMPLATE guslib::AbstractFactory < config::Loader, std::string, config::Loader*(*)() >* ExternalSingleton<guslib::AbstractFactory <
    config::Loader, std::string, config::Loader*(*)() >
  >::objectPtr_ = nullptr;

  namespace config
  {
    class IniLoader;

    //
    //  ------------------------------------ Configuration Internals ------------------------------------------------
    //

    //
    //  Opaque pointer: private implementation of the configuration class.
    //
    class Configuration::Impl
    {
    public:
      std::shared_ptr<Loader> loader_ptr_;

      std::map <std::string, PropertyGroup> groups_;

      // the default group to use for setting/retrieving properties.
      std::string defaultGroup_;

      //
      // Constructor.
      //
      Impl()
        : loader_ptr_(nullptr)
        , defaultGroup_("general")
        , groups_(std::map <std::string, PropertyGroup>())
      {
        GTRACE(7, "Config-Internal CTOR");
      }

      //
      // Copy constructor.
      //
      Impl(const Impl& rhs)
        : loader_ptr_(rhs.loader_ptr_)
        , defaultGroup_(rhs.defaultGroup_)
        , groups_(rhs.groups_)
      {
        GTRACE(7, "Config-Internal COPY CTOR");
      }

      ~Impl()
      {
        GTRACE(7, "Config-Internal DTOR");
        groups_.clear();
        //delete loader_ptr_;
      }
    };

    //
    // -------------------- Configuration main class ----------------------------
    //

    //
    //  Constructor.
    //
    Configuration::Configuration()
      : impl_(new Configuration::Impl())
    {
      Config::init();
      GTRACE(3, "Created Configuration. Impl addr: " << impl_);
    }

    //
    //  Copy Constructor.
    //
    Configuration::Configuration(const Configuration& rhs)
      : impl_(new Configuration::Impl(*rhs.impl_))
    {
      GTRACE(3, "copied Configuration. Impl addr: " << impl_);
    }

    //
    //  Destructor.
    //
    Configuration::~Configuration()
    {
      GTRACE(3, "Destroying Configuration. Impl addr: " << impl_);
      delete impl_;
      GTRACE(3, "Destroyed.");
    }

    const std::map <std::string, PropertyGroup>& Configuration::getGroups()
    {
      return impl_->groups_;
    }

    PropertyGroup& Configuration::getGroup(const std::string& name)
    {
      std::map <std::string, PropertyGroup>::iterator it = impl_->groups_.find(name);

      if (it != impl_->groups_.end())
      {
        return it->second;
      }

      // error scenario
      // a group was requested; this was previously unknown.
      // add it to the group list?

      addGroup(name);
      it = impl_->groups_.find(name);
      if (it != impl_->groups_.end())
      {
        return it->second;
      }

      // exception scenario... we just added it to the map... what gives?
      throw guslib::SimpleException("Get group: could not add a group");
    }

    Configuration& Configuration::operator = (const Configuration& rhs)
    {
      if (this != &rhs)
      {
        if (this->impl_)
        {
          delete this->impl_;
        }

        this->impl_ = new Configuration::Impl(*rhs.impl_);
      }

      return *this;
    }

    PropertyGroup& Configuration::operator[](const std::string& name)
    {
      return getGroup(name);
    }

    void Configuration::clear()
    {
      impl_->groups_.clear();
    }

    void Configuration::addGroup(const std::string& name)
    {
      impl_->groups_.insert(std::make_pair(name, PropertyGroup(name)));
    }

    void Configuration::addGroup(const PropertyGroup & group)
    {
      impl_->groups_.insert(std::make_pair(group.getName(), group));
    }

    bool Configuration::load(const std::string & fileName)
    {
      bool result(false);

      GTRACE(3, "Configuration - loading from " << fileName);
      std::string fileExtension = stringutil::GetExtensionFromFileName(fileName);   // E.g. "ini";

      // Use the loader based on the extension.
      impl_->loader_ptr_.reset(config::LoaderFactory::getPtr()->CreateObject(fileExtension));
      //impl_->loader_ptr_ = config::LoaderFactory::getPtr()->CreateObject(fileExtension);
      if (!impl_->loader_ptr_)
      {
        // No loader for this extension!
        std::string exception_message("Data cannot be loaded using this extension: \"");
        exception_message.append(fileExtension);
        exception_message.append("\". No factory detected");
        throw guslib::SimpleException(exception_message.c_str());
      }

      result = impl_->loader_ptr_->load(*this, fileName);

      GTRACE(5, "Configuration - DONE loading from " << fileName);

      return result;
    }


    void Configuration::save()
    {
      if (nullptr == impl_->loader_ptr_)
      {
        GTRACE(3, "Tried to save configuration, but no loader is available");
        return;
      }

      GTRACE(5, "Configuration - saving");
      impl_->loader_ptr_->save(*this);
    }

    void Configuration::saveAs(const std::string& fileName)
    {
      if (nullptr == impl_->loader_ptr_)
      {
        GTRACE(3, "Tried to save configuration, but no loader is available");
        return;
      }

      GTRACE(5, "Configuration - saving as...");
      impl_->loader_ptr_->save(*this, fileName);
    }

  }
}
