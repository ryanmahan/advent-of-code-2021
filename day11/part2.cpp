#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "grid/Grid.impl.hpp"
#include "Octopus.h"

using namespace advent;
using namespace cavern;

int count = 0;

void flashCallback() {
  count++;
}

int main() {
  Grid<Octopus> grid;
  int rows, cols;
  grid.readFile("test.txt");
  GridSize gridSize = grid.size();
  std::cout << "Grid Size " << gridSize.rows << " by " << gridSize.cols << std::endl;
  for (int i = 0 ; i < gridSize.rows ; i++) {
    for (int j = 0 ; j < gridSize.cols ; j++) {
      Octopus* octo = grid.safeGet(i, j);
      octo->setFlashCallback(flashCallback);
      octo->setNeighbors(grid.getNeighbors(i, j, true));
    }
  }
  for (int k = 0 ; k < 10000 ; k++) {
    std::cout << k << std::endl;
    for (int i = 0 ; i < gridSize.rows ; i++) {
      for (int j = 0 ; j < gridSize.cols ; j++) {
        Octopus* octo = grid.safeGet(i, j);
        octo->increasePower();
        std::cout << octo->getPower();
      }
      std::cout << std::endl;
    }
    for (int i = 0 ; i < gridSize.rows ; i++) {
      for (int j = 0 ; j < gridSize.cols ; j++) {
        Octopus* octo = grid.safeGet(i, j);
        octo->newRound();
        if (count >= 100) {
          return 0;
        }
      }
    }
    count = 0;
    
  }
  std::cout << count << std::endl;
}