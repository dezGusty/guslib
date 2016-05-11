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
//   A simple port tester class.
//
 
//
// Include own header.
//
#include "guslib/util/porttester.h"
 
//
// Platform specific definitions and overall build options for the library.
//
#include <guslib/guslibbuildopts.h>

//
// C system files
//
#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#elif ACT_COMMON_PLATFORM_TYPE == ACT_COMMON_PLATFORM_TYPE_LINUX
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif
//
// C++ system files
//
 
// none
 
//
// This libraries' headers
//
#include "guslib/trace/trace.h"

namespace guslib
{
#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
 
  void InitializeSockets()
  {
    //----------------------
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
    {
      GTRACE(3, "WSAStartup function failed with error: " << iResult << ".");
    }
  }
 
  void CleanupSockets()
  {
    WSACleanup();
  }
 
  bool CanOpenTCPPortWindows(const char* address, unsigned int port_number)
  {
    InitializeSockets();
 
    struct sockaddr_in client;
    int sock;
 
    client.sin_family = AF_INET;
    client.sin_port = htons(port_number);
    client.sin_addr.S_un.S_addr = inet_addr(address);
 
    sock = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));
 
    GTRACE(3, "Checking if port can be opened for: " << port_number << " on " << address);
 
    int result = connect(sock, (struct sockaddr *) &client, sizeof(client));
    int last_error = WSAGetLastError();
    if (result == SOCKET_ERROR)
    {
      GTRACE(3, "Connect failed with error: " << last_error);
    }

    closesocket(sock);
    CleanupSockets();
 
    if (result == 0)
    {
      // No error.
      // Managed to connect to a socket.
      // That means that the port cannot be opened (it is already opened).
      return false;
    }
    else
    {
      if (last_error == WSAECONNREFUSED)
      {
        // (10061)
        // Connection refused.
        // No connection could be made because the target computer actively refused it.
        // This usually results from trying to connect to a service that is inactive on the foreign host—that is,
        // one with no server application running
        return true;
      }
 
      // port is active and used
      return false;
    }
  }
 
#elif GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_LINUX
  bool CanOpenTCPPortLinux(const char* address, unsigned int port_number)
  {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
      return false;
    }
 
    server = gethostbyname(address);
 
    if (server == NULL)
    {
      // Error, no such host.
      return false;
    }
 
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
      (char *)&serv_addr.sin_addr.s_addr,
      server->h_length);
 
    bool result = false;
    serv_addr.sin_port = htons(port_number);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
      // Port is closed.
      result = true;
    }
    else
    {
      // Port is active
      result = false;
    }
 
    close(sockfd);
    return 0;
}
#endif
 
  bool PortTester::CanOpenTCPPort(const char* address, unsigned int port_number)
  {
#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
    return CanOpenTCPPortWindows(address, port_number);
#elif GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_LINUX
    return CanOpenTCPPortLinux(address, port_number);
#endif
  }
}

