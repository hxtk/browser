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

  std::string* nodeName() const override {
    return const_cast<std::string*>(&kNodeName);
  }
 private:
  const std::string kNodeName = "#document";
};  // class Element
}  // namespace dom

#endif  // DOM_DOCUMENT_H_
