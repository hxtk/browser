// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-03

#ifndef DOM_DOCUMENT_H_
#define DOM_DOCUMENT_H_

#include <string>
#include <list>
#include <unordered_map>

#include "dom/node.h"

namespace dom {
class Document : public Node {
 public:
  Document() : Node(Node::kDocument) {}

  std::string* nodeName() override { return &kNodeName; }
  std::string* nodeValue() override { return &node_value_; }
  void setNodeValue(const std::string& value) override {
    node_value_ = value;
  }
 private:
  static constexpr std::string kNodeName = "#text";

  std::string node_value_ = "";
};  // class Element
}  // namespace dom

#endif  // DOM_DOCUMENT_H_
