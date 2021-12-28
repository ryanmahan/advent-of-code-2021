#include <vector>
#include <functional>


namespace cavern {
  class Octopus {
    private:
      int power;
      bool increaseLock;
      std::vector<Octopus *> neighbors;
      std::function<void(void)> flashCallback;
    public:
      void setFlashCallback(std::function<void(void)> callback);
      void addNeighbor(Octopus * neighbor);
      void setNeighbors(std::vector<Octopus *> neighbors);
      void setPower(int power);
      int getPower();
      void increasePower();
      void newRound();
      Octopus(int c);
  };
};