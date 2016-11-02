// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-02

#include <iostream>
#include <cstdint>

#include "tcp_stream.h"

int main() {
  net::TcpStream ts;
  ts.Open("localhost", 8000);
  ts.set_timeout(10000);
  uint32_t ip = ts.get_peer_ip();
  std::cout << "Connected to peer: "
            << (ip >> 24) << "."
            << ((ip >> 16) & 0xff) << "."
            << ((ip >> 8) & 0xff) << "."
            << (ip & 0xff) << std::endl;
  std::cout << ts.Send("GET / HTTP/1.1\nHost: xkcd.com\n\n");
  std::cout << std::endl;
  std::string buffer;
  ts.ReadTo(&buffer, {"\r\n\r\n", "\n\n"});
  std::cout << buffer << std::endl;
  
  return 0;
}
