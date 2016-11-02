// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-01

#ifndef NETSTREAM_H_
#define NETSTREAM_H_

#include <string>

#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace net {
class NetStream {
 public:
  NetStream() {}
  ~NetStream() {}

  // Opens a network socket to the provided host.
  // The host is not assumed to be valid.
  // Attempting to connect to an invalid host will return |false|.
  bool Open(const char* address, const char* port);

  // Sends a message string to the network socket.
  bool Send(const std::string& message);
  bool Receive(std::string* data);
 private:
  static constexpr int kBufferSize = 1024;
  int socket_ = -1;  // Error socket value
  bool valid_ = false;
};  // class NetStream
}  // namespace net

#endif  // NETSTREAM_H_
