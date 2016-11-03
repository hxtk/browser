// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-03
//
// Defines Document Object Model node according to
// documentation found at:
// https://www.w3.org/TR/WD-DOM/level-one-core.html
// NOTE: Style is also based on this specification;
//  deviations from the styleguide are intentional.

#ifndef DOM_NODE_H_
#define DOM_NODE_H_

#include <string>
#include <list>
#include <unordered_map>

namespace dom {

using NodeList = std::list<Node>;
using AttributeMap = std::unordered_map<std::string, std::string>;

class Node {
 public:
  enum NodeType {
    kDummyType = 0,
    kDocument = 1,
    kElement = 2,
    kAttribute = 3,
    kProcessingInstruction = 4,
    kComment = 5,
    kText = 6,
    kCDataSection = 7,
    kDocumentFragment = 8,
    kEntity = 9,
    kEntityReference = 10,
    kDocumentType = 11
  };

  // Attribute accessors and mutators
  virtual std::string nodeName() const = 0;
  virtual std::string nodeValue() const = 0;
  virtual std::string nodeType() const = kDummyType;
  virtual void setNodeValue(const std::string&);
  virtual AttributeMap* attributes() const = nullptr;
  
  // Family accessors and mutators
  Node* parentNode() const;
  Element* parentElement() const;
  Node* nextSibling() const;
  Node* previousSibling() const;

  // Some nodes cannot have children
  virtual NodeList* childNodes() const = nullptr;
  virtual Node* firstChild() const = nullptr;
  virtual Node* lastChild() const = nullptr;

  
  Node* insertBefore(Node* new_child, const Node* ref_child);
  Node* replaceChild(Node* new_child, const Node* old_child);
  
  bool hasChildren() const { return firstChild() != nullptr; }
  bool isEqualNode(const Node* other) const;
  bool isSameNode(const Node* other) const { return this == other; }
  
 private:
  
};
}

#endif  // DOM_NODE_H_
