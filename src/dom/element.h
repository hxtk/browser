// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-03

#ifndef DOM_ELEMENT_H_
#define DOM_ELEMENT_H_

#include <string>
#include <list>
#include <unordered_map>

#include "dom/node.h"

namespace dom {
class Element : public Node {
 public:
  Element() : Node(Node::kElement) {}
  ~Element() : ~Node() {
    for (auto it = attributes_.begin(); it != attributes_.end(); ++it) {
      delete it;
    }
  }

  std::string* nodeName() override { return &tag_name_; }
  NodeList* attributes() override { return &attributes_; }
 private:
  std::string tag_name_ = "";
  NodeList attributes_ = {};
};  // class Element
}  // namespace dom

#endif  // DOM_ELEMENT_H_
