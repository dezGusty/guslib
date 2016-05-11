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
//   A simple plugin class.
//
//   Last change:  $LastChangedDate: 2013-06-20 23:19:27 +0200 (J, 20 iun. 2013) $
//   Revision:    $Revision: 574 $

//
// Includes
//

//
// Own header
//
#include "guslib/util/pluginmanager.h"

//
// C++ system headers
//
#include <algorithm>
#include <string>
#include <vector>

//
// This library's headers
//
#include "guslib/common/simpleexception.h"
#include "guslib/system/dynamiclibmanager.h"

namespace guslib
{
  //
  // ----------------------------- Plugin manager internals ---------------------------------
  //

  class PluginManagerUtil::Impl
  {
  public:
    std::vector<Plugin*> pluginList_;
    std::vector<DynamicLib*> dynLibList_;

    Impl()
    {
    }
  };

  //
  // ----------------------------- Dynamic Lib Manager ---------------------------------
  //

  PluginManagerUtil::PluginManagerUtil()
    : impl_(new PluginManagerUtil::Impl())
  {

  }

  PluginManagerUtil::~PluginManagerUtil()
  {
    delete impl_;
  }

  void PluginManagerUtil::install(Plugin* pluginPtr)
  {
    impl_->pluginList_.push_back(pluginPtr);
    pluginPtr->install();
    pluginPtr->initialize();
  }

  void PluginManagerUtil::uninstall(Plugin* pluginPtr)
  {
    std::vector<Plugin*>::iterator it =
      std::find(impl_->pluginList_.begin(), impl_->pluginList_.end(), pluginPtr);
    if (it != impl_->pluginList_.end())
    {
      pluginPtr->shutdown();

      pluginPtr->uninstall();
      impl_->pluginList_.erase(it);
    }
  }

  
  void PluginManagerUtil::loadPluginByName(const std::string& pluginName)
  {
    // Load plugin library
    DynamicLib* libPtr = DynamicLibManager::get().load(pluginName);

    // Store for later unload
    // Check for existence, because if called 2+ times DynLibManager returns existing entry
    if (std::find(impl_->dynLibList_.begin(), impl_->dynLibList_.end(), libPtr) == impl_->dynLibList_.end())
    {
      // Plugin not yet loaded.
      impl_->dynLibList_.push_back(libPtr);

      // Call startup function
#ifdef __GNUC__
      __extension__
#endif
      
      DLL_START_PLUGIN pFunc = (DLL_START_PLUGIN)libPtr->getSymbol("dllStartPlugin");

      if (!pFunc)
      {
        std::string message{ "Cannot find symbol [dllStartPlugin] in library: " };
        message.append(pluginName);
        throw guslib::SimpleException(message.c_str());
      }

      // This must call installPlugin
      pFunc();
    }
  }

 
  void PluginManagerUtil::unloadPluginByName(const std::string& pluginName)
  {
    std::vector<DynamicLib*>::iterator it;

    for (it = impl_->dynLibList_.begin(); it != impl_->dynLibList_.end(); ++it)
    {
      if ((*it)->getName() == pluginName)
      {
        // Call plugin shutdown
#ifdef __GNUC__
        __extension__
#endif
        DLL_STOP_PLUGIN pFunc = (DLL_STOP_PLUGIN)(*it)->getSymbol("dllStopPlugin");
        
        // this must call uninstallPlugin
        pFunc();
        
        // Unload library (destroyed by DynLibManager)
        DynamicLibManager::get().unload(*it);
        impl_->dynLibList_.erase(it);
        return;
      }
    }
  }

}


