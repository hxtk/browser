// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-03

#ifndef DOM_TEXT_H_
#define DOM_TEXT_H_

#include <string>
#include <list>
#include <unordered_map>

#include "dom/node.h"

namespace dom {
class Document : public Node {
 public:
  Document() : Node(Node::kDocument) {}

  std::string* nodeName() override { return &kNodeName; }
 private:
  static constexpr std::string kNodeName = "#text";
 
};  // class Element
}  // namespace dom

#endif  // DOM_TEXT_H_
