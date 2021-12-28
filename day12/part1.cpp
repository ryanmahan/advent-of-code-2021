#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace caves;

int countPaths(Node *startNode, std::vector<std::string> exploredNodes) {
  int childPaths = 0;
  exploredNodes.push_back(startNode->getName());
  if (startNode->getName() == "end") {
    return 1;
  } else { 
    for (Node *node : startNode->getConnectedNodes()) {
      bool explored = std::find(exploredNodes.begin(), exploredNodes.end(), node->getName()) != exploredNodes.end();
      if (!explored || node->isLarge()) {
        childPaths += countPaths(node, exploredNodes);
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
  std::cout << countPaths(start, std::vector<std::string>()) << std::endl;
  for(std::map<std::string, Node *>::iterator iter = nodeMap.begin() ; iter != nodeMap.end() ; ++iter) {
    delete(iter->second);
  }
}