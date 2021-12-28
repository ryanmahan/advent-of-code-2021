#include "Node.h"

using namespace caves;

std::vector<Node *> Node::getConnectedNodes() {
  return this->connectedNodes;
}

std::string Node::getName() {
  return this->name;
}

void Node::addConnection(Node *node) {
  this->connectedNodes.push_back(node);
}

bool Node::isLarge() {
  return this->large;
}

Node::Node(std::string name) {
  this->name = name;
  this->large = std::isupper(name.at(0));
  this->connectedNodes = std::vector<Node *>();
}

Node::Node() {
  this->connectedNodes = std::vector<Node *>();
}