// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-01

#include <iostream>
#include <string>

#include  "./netstream.h"

using std::cout;
using std::endl;
using std::string;

int main() {
  string buffer;
  bool status;
  net::NetStream ns;
  cout << "Attempting to open socket." << endl;
  cout << ns.Open("localhost", "8000") << endl;
  cout << ns.Send("GET / HTTP/1.1\nHost: localhost\n\n") << endl;

  return 0;
}
