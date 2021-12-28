#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace caves;

void increaseOrInitialize(Node* node, std::map<std::string, int> &exploredNodes, bool &exploredTwice) {
  std::string name = node->getName();
  if (exploredNodes.count(name)) {
    exploredNodes.at(name) = exploredNodes.at(name) + 1;
    if (!node->isLarge()) {
      exploredTwice = true;
    }
  } else {
    exploredNodes.insert({ name, 1 });
  }
}

bool hasBeenExplored(Node *node, std::map<std::string, int> &exploredNodes, bool exploredTwice) {
  std::string name = node->getName();
  if (name == "start" || name == "end" || exploredTwice) {
    return exploredNodes.count(name);
  }
  if (exploredNodes.count(name)) {
    return exploredNodes.at(name) > 1;
  } else {
    return false;
  }
}

int countPaths(Node *startNode, std::map<std::string, int> exploredNodes, std::string path, bool exploredTwice) {
  int childPaths = 0;
  increaseOrInitialize(startNode, exploredNodes, exploredTwice);
  path.append("," + startNode->getName());
  if (startNode->getName() == "end") {
    std::cout << path << std::endl;
    return 1;
  } else { 
    for (Node *node : startNode->getConnectedNodes()) {
      bool explored = hasBeenExplored(node, exploredNodes, exploredTwice);
      if (!explored || node->isLarge()) {
        childPaths += countPaths(node, exploredNodes, path, exploredTwice);
      }
    }
  }
  return childPaths;
}

int main () {
  std::ifstream file("test.txt");
  std::string line;
  std::map<std::string, Node *> nodeMap;
  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string nodeName;
    std::size_t dashLocation = line.find('-');
    std::string firstNodeName, secondNodeName;
    firstNodeName = line.substr(0, dashLocation);
    secondNodeName = line.substr(dashLocation + 1, line.length() - dashLocation);
    Node *firstNode;
    Node *secondNode;
    if (nodeMap.count(firstNodeName)) {
      firstNode = nodeMap.at(firstNodeName);
    } else {
      firstNode = new Node(firstNodeName);
      nodeMap.insert({ firstNodeName, firstNode });
    }
    if (nodeMap.count(secondNodeName)) {
      secondNode = nodeMap.at(secondNodeName);
    } else {
      secondNode = new Node(secondNodeName);
      nodeMap.insert({ secondNodeName, secondNode });
    }
    firstNode->addConnection(secondNode);
    secondNode->addConnection(firstNode);
    nodeMap.at(firstNodeName) = firstNode;
    nodeMap.at(secondNodeName) = secondNode;
  }
  
  Node *start = nodeMap.at("start");
  // for (Node *node : start->getConnectedNodes()) {
  //   std::cout << node->getName() << std::endl;
  //   for (Node *connected : node->getConnectedNodes()) {
  //     std::cout << node->getName() << " " << connected->getName() << std::endl;
  //   }
  // }
  std::cout << countPaths(start, std::map<std::string, int>(), "", false) << std::endl;
  for(std::map<std::string, Node *>::iterator iter = nodeMap.begin() ; iter != nodeMap.end() ; ++iter) {
    delete(iter->second);
  }
}