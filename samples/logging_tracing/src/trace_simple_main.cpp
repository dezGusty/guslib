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

// The tracing header.
#include "guslib/trace/trace.h"

void main()
{
  // Defines the output file to use
  std::string my_file_name("tracing_sample_1.log");

  // Defines the trace level to use. All commands with a trace level higher than this shall be ignored.
  int trace_level = 4; // Level of tracing
	
  // Starts writing to the file.
  GSTARTTRACING(my_file_name.c_str(), trace_level);

  // Adding some entries.
  GTRACE(1, "The trace started successfully");
  GTRACE(5, "This message is not written, because it's sent with level 5, but the trace level is 4");
  GDISABLETRACE(); // the trace was disabled.
  GTRACE(1, "This will also not be written, because the tracing is disabled");
  GENABLETRACE(); // trace was re-enabled.
  GTRACE(4, "This message is written.");
  GSETTRACELEVEL(3); // the trace level was changed.
  GTRACE(4, "This message is not written, because it's sent with level 4, but the trace level is 3");
  GTRACE(3, "This works with streams, so it is possible to " << "group" << " more texts using the << operator.");
  GTRACE(-1, "It's possible to use negative levels also for even higher priority.");

  GSTOPTRACING(); // Destroys the trace object static instance; file handle closed.
}