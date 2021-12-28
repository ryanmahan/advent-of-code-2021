#include <vector>
#include <string>

namespace caves {
  class Node {
    private:
      std::vector<Node *> connectedNodes;
      bool large;
      std::string name;
    public:
      std::vector<Node *> getConnectedNodes();
      std::string getName();
      bool isLarge();
      void addConnection(Node *node);
      Node(std::string name);
      Node();
  };
}