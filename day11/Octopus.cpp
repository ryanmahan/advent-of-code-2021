#include "Octopus.h"

using namespace cavern;

void Octopus::setPower(int power) {
  this->power = power;
}

void Octopus::setFlashCallback(void(*callback)()) {
  this->flashCallback = callback;
}

void Octopus::increasePower() {
  if (this->increaseLock) return;
  this->power++;
  if (this->power == 10) {
    this->increaseLock = true;
    this->power = 0;
    for (Octopus neighbor : this->neighbors) {
      neighbor.increasePower();
    }
  }
}

void Octopus::newRound() {
  this->increaseLock = false;
}