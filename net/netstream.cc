#include "netstream.h"

#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using std::string;

namespace net {
bool NetStream::Send(const string& message) {
  if (!valid_) return false;

  const char* message_buffer = message.c_str();
  int len_remaining = message.size();
  while (len_remaining > 0) {
    int status = send(
        socket_,
        &message_buffer[message.size() - len_remaining],
        len_remaining,
        0  // No flags are used
    );
    if (status == -1) {
      return false;
    } else {
      len_remaining -= status;
    }
  }
  return true;
}

bool NetStream::Receive(string* data) {
  data->clear();
  char *buffer = new char[kBufferSize];
  memset(buffer, sizeof(buffer), '\0');
  int status;
  while (status = recv(socket_, buffer, kBufferSize - 1, 0) > 0) {
    *data += buffer;
    memset(buffer, sizeof(buffer), '\0');
  }
  return (status == 0);  // |status| will have |-1| on error
                         // |0| on clean message termination
}

bool NetStream::Open(const char* address, const char* port) {
  struct addrinfo hints;
  memset(&hints, sizeof(hints), 0);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  struct addrinfo* results = new struct addrinfo;

  // The non-error condition is |0|, thus the following is only executed
  // if |getaddrinfo()| exits with an error.
  if (getaddrinfo(address, port, &hints, &results)) {
    // TODO(hxtk): Log error
    freeaddrinfo(results);
    return false;
  }
  for (auto it = results; it != NULL; it = it->ai_next) {
    socket_ = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
    if (socket_ == -1) continue;
    if (connect(socket_, it->ai_addr, it->ai_addrlen) == -1) continue;
    break;
  }
  freeaddrinfo(results);

  valid_ = (socket_ == -1);
  return valid_;
}
}  // namespace net
