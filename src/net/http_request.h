// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-02

#ifndef NET_HTTP_REQUEST_H_
#define NET_HTTP_REQUEST_H_

#include <unordered_map>
#include <string>
#include <cstdint>

#include "net/tcp_stream.h"

namespace net {

// Convenience alias for string-based key/value pairs
using AttributeMap = std::unordered_map<std::string, std::string>;

class HttpRequest {
 public:
  enum Method { GET, POST, PUT, DELETE };
  
  HttpRequest() {}
  ~HttpRequest() {}

  bool Open(Method method, url::Url url);
  bool Send();

  void set_attribute(std::string key, std::string value) {
    attributes_[key] = value;
  }
  void get_attribute(std::string key) {
    return attributes_[key];
  }
 private:
  url::Url url_;
  TcpStream tcp_;
  Method method_ = GET;
  AttributeMap attributes_;
};  // class HttpRequest
}  // namespace net

#endif  // NET_HTTP_REQUEST_H_
