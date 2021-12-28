#include "Octopus.h"
#include <iostream>

using namespace cavern;

void Octopus::setPower(int power) {
  this->power = power;
}

void Octopus::setNeighbors(std::vector<Octopus *> neighbors) {
  this->neighbors = neighbors;
}

int Octopus::getPower() {
  return this->power;
}

void Octopus::setFlashCallback(std::function<void(void)> callback) {
  this->flashCallback = callback;
}

void Octopus::increasePower() {
  if (this->increaseLock) return;
  this->power = this->power + 1;
  if (this->power > 9) {
    this->increaseLock = true;
    this->power = 0;
    for (Octopus *neighbor : this->neighbors) {
      neighbor->increasePower();
    }
    this->flashCallback();
  }
}

void Octopus::newRound() {
  this->increaseLock = false;
}

Octopus::Octopus(int c) {
  this->power = c;
}