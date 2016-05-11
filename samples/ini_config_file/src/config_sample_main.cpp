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

//
// Includes
//

//
// C++ system headers, in alphabetical order.
//
#include <iostream>

//
// 3rd party libs, in alphabetical order
//
#include "guslib/trace/trace.h"
#include "guslib/util/config.h"
#include "guslib/util/config/configuration.h"
#include "guslib/util/config/loader.h"

class SampleXmlLoader
  : public guslib::config::Loader
{
public:
  static guslib::config::Loader* createLoader()
  {
    return new SampleXmlLoader();
  }

  SampleXmlLoader()
    : guslib::config::Loader()
  {
    std::cout << "SampleXmlLoader CTOR" << std::endl;
  }

  virtual bool load(guslib::config::Configuration & configToLoad, const std::string& fileName)
  {
    std::cout << "Loading [" << fileName << "]" << std::endl;
    return true;
  }

  virtual void save(guslib::config::Configuration & configToSave, const std::string& fileName)
  {
    std::cout << "Saving [" << fileName << "]" << std::endl;
    // nothing.
  }

};

int main()
{
  GSTARTTRACING("config_sample_1.log", 10);
  GTRACE(3, "Started tracing");

  try
  {
    guslib::config::Configuration sample_config;
    guslib::config::LoaderFactory::getPtr()->Register("xml", SampleXmlLoader::createLoader);

    sample_config.load("data/sample.ini");

    GTRACE(3, "Creating property group using local context");
#if 0
    guslib::config::PropertyGroup sample_group("x1");

    guslib::config::PropertyGroup second_group("x2"); //xxx

    sample_group = second_group;
#endif
    guslib::config::PropertyGroup sample_group;
    GTRACE(3, "Copying object with assignment");
    sample_group = sample_config.getGroup("general");
    std::cout << "A group was found using the name: " << sample_group.getName() << std::endl;

    // Display all the properties in the group.
    std::vector<guslib::config::Property> props;
    props = sample_group.getProperties();

    for (auto prop : props)
    {
      std::cout << prop.getAsString() << std::endl;
    }
    
    // Display a multi-value property, using a single value.
    std::cout << "Multi-value property, as single value: " << sample_config["general"]["multioption1"].getAsStringOrDefaultVal("no value found") << std::endl;

    std::vector <std::string> sample_multi_values = sample_config["general"]["multioption1"].getAsStringList();
    std::cout << "Multi-value property as vector:" << std::endl;
    for (auto single_value : sample_multi_values)
    {
      std::cout << single_value << std::endl;
    }
  }
  catch (const std::exception& ex)
  {
    std::cout << "An exception was caught: " << ex.what() << std::endl;
  }


  GTRACE(3, "done!");
  GSTOPTRACING();
  
  return 0;
}