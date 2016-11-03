// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-02

#include "net/tcp_stream.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <initializer_list>
#include <string>
#include <cstdint>
#include <cstring>

using std::string;
using addrinfo = struct addrinfo;

namespace net {
bool TcpStream::Send(const string& message) {
  if (!valid_) return false;

  const char* buffer = message.c_str();
  int len_remaining = message.size();
  while (len_remaining > 0) {
    int tmp = send(
        socket_,
        reinterpret_cast<const void*>(buffer + message.size() - len_remaining),
        len_remaining,
        0);
    if (tmp == -1) {
      return false;
    } else {
      len_remaining -= tmp;
    }
  }
  return true;
}

bool TcpStream::Read(string* data, int num_bytes) {
  if (!valid_) return false;

  char* buffer = new char[num_bytes + 1];
  memset(buffer, '\0', num_bytes + 1);

  // NOTE: may receive no more than num_bytes - 1
  int status = recv(socket_, buffer, num_bytes, 0);
  *data += buffer;

  delete[] buffer;
  if (status == -1) valid_ = false;
  return (status > 0);
}

bool TcpStream::ReadTo(string* data, const string& delim) {
  if (!valid_) return false;

  int offset = data->size();
  char buffer;

  // read a single character at a time onto the string until a match is found
  while (data->find(delim, offset) == string::npos) {
    int status = recv(socket_, &buffer, 1, 0);
    if (status < 1) {
      if (status  == -1) valid_ = false;
      return false;
    }
    *data += buffer;
  }
  return true;
}

bool TcpStream::ReadTo(string* data, std::initializer_list<string> delims) {
  if (!valid_) return false;

  int offset = data->size();
  char buffer;

  // read a single character at a time onto the string until a match is found
  while (!DelimFound(*data, delims, offset)) {
    int status = recv(socket_, &buffer, 1, 0);
    if (status < 1) {
      if (status  == -1) valid_ = false;
      return false;
    }
    *data += buffer;
  }
  return true;
}

bool TcpStream::Open(const string& peer, int port) {
  port_ = port;

  // Require a connection over IPv4 using a TCP socket.
  addrinfo hints {
      0,            // flags
      AF_INET,      // address family
      SOCK_STREAM,  // Require TCP socket
      0,            // protocol
      0,            // address length (must be |0|)
      nullptr,      // struct sockaddr (must be |null|)
      nullptr,      // canonical name (must be |null|)
      nullptr       // link to next element (must be |null|)
  };
  addrinfo* results = new addrinfo;
  int status = 0;

  status = getaddrinfo(
      peer.c_str(),
      std::to_string(port).c_str(),
      &hints,
      &results);

  if (status != 0) {
    // TODO(hxtk): log error
    return false;
  }

  // Iterate over results until a usable connection is found.
  for (auto it = results; it != nullptr; it = it->ai_next) {
    socket_ = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
    if (socket_ == -1 || connect(socket_, it->ai_addr, it->ai_addrlen) == -1) {
      socket_ = -1;
      continue;
    }
    peer_ip_ = ntohl(
        reinterpret_cast<sockaddr_in*>(it->ai_addr)->sin_addr.s_addr);
    freeaddrinfo(results);
    valid_ = true;
    return true;
  }
  freeaddrinfo(results);
  valid_ = false;
  return false;
}

bool TcpStream::DelimFound(
    const string& haystack,
    std::initializer_list<string> needles,
    int offset) const {
  for (auto it = needles.begin(); it != needles.end(); ++it) {
    if (haystack.find(*it, offset) != string::npos) return true;
  }
  return false;
}

}  // namespace net
