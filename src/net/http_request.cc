// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-02

#include "net/http_request.h"

#include <unordered_map>
#include <string>
#include <cstdint>

#include "net/tcp_stream.h"
#include "url/url.h"

using std::string;

namespace net {
bool HttpRequest::Open(Method method, url::Url url) {
  method_ = method;
  url_ = url;
}

bool HttpRequest::Send() {
  string request = "";
  switch(method_) {
    case GET:
      request = "GET";
      break;
    case POST:
      request = "POST";
    case PUT:
      request = "PUT";
    case DELETE:
      request = "DELETE";
  }
  request += " " + url_.get_path() + " HTTP/1.1\r\n";
  
  for (auto it = attributes_.begin(); it != attributes_.end(); ++it) {
    request += it->first + ": " + it->second + "\r\n";
  }
  request += "\r\n";

  return (tcp_.Open(url_.get_host(), url_.get_port()) && tcp_.Send(request));
}

bool HttpRequest::Response(string* buffer) {

}
}  // namespace net
