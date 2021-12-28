#include <vector>

namespace cavern {
  class Octopus {
    private:
      int power;
      bool increaseLock;
      std::vector<Octopus> neighbors;
      void(*flashCallback)();
    public:
      void setFlashCallback(void(*callback)());
      void setPower(int power);
      void increasePower();
      void newRound();
  }
}