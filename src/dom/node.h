// Copyright: Peter Sanders. All rights reserved.
// Date: 2016-11-03
//
// Defines Document Object Model node according to
// documentation found at:
// https://www.w3.org/TR/WD-DOM/level-one-core.html
//
// NOTE: This is a willful violation of the style guide,
// deferring to the format used by the above documentation

#ifndef DOM_NODE_H_
#define DOM_NODE_H_

#include <string>
#include <list>
#include <unordered_map>

namespace dom {

class Node;
class Element;

using NodeList = std::list<Node*>;
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

  Node(NodeType type) {
    type_ = type;
  }
  virtual ~Node() {
    for (auto it = children_.begin(); it != children_.end(); ++it) {
      delete *it;
    }
  }

  // Attribute accessors and mutators
  virtual std::string* nodeName() const { return nullptr; }
  virtual std::string* nodeValue() const { return nullptr; }
  virtual NodeType nodeType() const { return kDummyType; }
  virtual void setNodeValue(const std::string& value);
  virtual NodeList* attributes() const { return nullptr; }

  // Family accessors and mutators
  Node* parentNode() const;
  Element* parentElement() const;
  Node* nextSibling() const;
  Node* previousSibling() const;

  // Some nodes cannot have children
  virtual NodeList* childNodes() const { return nullptr; }
  virtual Node* firstChild() const { return nullptr; }
  virtual Node* lastChild() const { return nullptr; }

  Node* insertBefore(Node* new_child, const Node* ref_child);
  Node* replaceChild(Node* new_child, const Node* old_child);

  virtual bool isEqualNode(const Node* other) const = 0;
  bool hasChildren() const { return (this->firstChild() != nullptr); }
  bool isSameNode(const Node* other) const { return this == other; }

 private:
  NodeType type_ = kDummyType;
  NodeList children_ = {};

};  // class Node
}  // namespace dom

#endif  // DOM_NODE_H_
