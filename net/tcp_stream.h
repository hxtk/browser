// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-01

#ifndef TCP_STREAM_H_
#define TCP_STREAM_H_

#include <initializer_list>
#include <string>
#include <cstdint>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace net {
class TcpStream {
 public:
  TcpStream() {}
  ~TcpStream() {
    if (socket_ != -1)
      close(socket_);
  }

  // Opens a network socket to the provided host.
  // The host is not assumed to be valid.
  // Attempting to connect to an invalid host will return |false|.
  bool Open(const std::string& address, int port);

  // Accepts a message to be sent and sends it.
  // As long as there are bytes remaining and there has not been an error,
  // it will continue attempting to send the remaining information.
  // Returns |true| if and only if all information is successfully sent.
  bool Send(const std::string& message);

  // The |Read*(*)| family of functions all read from the socket into
  // a string buffer passed as the first argument. The results are
  // appended to this buffer, leaving the original contents intact.

  // Second argument specifies number of bytes to be read from |socket_|.
  // NOTE: the buffer will be one byte larger than |num_bytes| to accomodate
  // C-style null termination of the string.
  // Returns true if and only if one or more character was read.
  // Invalidates the stream if an error occurs.
  bool Read(std::string* data, int num_bytes);

  // Reads a single byte at a time onto the output buffer
  // until the specified delimiter has been read.
  // NOTE: any occurrences of the delimeter already in the
  // buffer are ignored.
  bool ReadTo(std::string* data, const std::string& delim);

  // Reads a single byte at a time onto the output buffer
  // until one of arbitrarily many delimiters have been read.
  // NOTE: any occurrences of the delimeter already in the
  // buffer are ignored.
  bool ReadTo(std::string* data,
              const std::initializer_list<std::string> delims);

  // Returns the IP address to which you are connected
  // in numeric form (big endian).
  bool is_valid() const { return valid_; }
  uint32_t get_peer_ip() const { return peer_ip_; }
  int get_port() const { return port_; }
  void set_timeout(int timeout) { timeout_ = timeout; }
 private:
  bool DelimFound(
      const std::string& haystack,
      std::initializer_list<std::string> needles,
      int offset) const;
  
  // 192.0.2.* is reserved for dummy addresses under IPv4
  // and is thus used for the initial value.
  uint32_t peer_ip_ = (192 << 24) | (2 << 8);
  
  int port_ = -1;    // Initialized to invalid port
  int socket_ = -1;  // Initialized to error socket value
  bool valid_ = false;
  int timeout_= 1000;  // timeout length in ms (default 1 second)

};  // class TcpStream
}  // namespace net

#endif  // TCP_STREAM_H_
