#include "Grid.h"
#include <limits>
#include <iostream>

using namespace advent;

std::vector<std::vector<int>> Grid::getGrid() {
  return this->grid;
}

void Grid::readFile(std::string filename) {
  std::ifstream file(filename);
  std::string line;
  while(std::getline(file, line)) {
    std::vector<int> gridRow;
    for(char c : line) {
      gridRow.push_back(atoi(&c));
    }
    grid.push_back(gridRow);
  }
}

int Grid::safeGet(int row, int col, bool verbose) {
  try {
    return this->grid.at(row).at(col);
  } catch (std::out_of_range error) {
    if (verbose) std::cout << "Out of range error Row " << row << " Col " << col;
    return std::numeric_limits<int>::max();
  }
}

GridSize Grid::size() {
  GridSize gridSize;
  gridSize.rows = this->grid.size();
  gridSize.cols = this->grid.at(0).size();
  return gridSize;
}