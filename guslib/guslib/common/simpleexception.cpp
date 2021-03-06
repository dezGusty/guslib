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
// Includes
//

//
// Own header
//
#include "guslib/common/simpleexception.h"

//
// C++ system includes
//
#include <string>

namespace guslib
{
  /**
    Pimpl Idiom for the exception.
  */
  class SimpleException::Impl
  {
  public:
    std::string exceptionMessage_;

    explicit Impl(const char* text)
    {
      this->exceptionMessage_ = text;
    }
  };


  SimpleException::SimpleException(const char* text)
    : std::exception(),
      impl_(new SimpleException::Impl(text))
  {
  }

  SimpleException::SimpleException(const SimpleException& rhs)
    : impl_(new SimpleException::Impl(rhs.impl_->exceptionMessage_.c_str()))
  {
  }

  SimpleException::~SimpleException() throw()
  {
    delete impl_;
  }

  const char* SimpleException::what() const throw()
  {
    return this->impl_->exceptionMessage_.c_str();
  }
}
