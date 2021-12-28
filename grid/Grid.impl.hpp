#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <limits>
#include <iostream>

namespace advent {

  class GridSize {
    public:
      int rows;
      int cols;
  };

  class GridItem {
    public:
      GridItem(char c);
  };

  template <typename T>
  class Grid {
    private:
      std::vector<std::vector<T>> grid;
    public:
      std::vector<std::vector<T>> getGrid();
      void readFile(std::string filename);
      T* safeGet(int row, int col, bool verbose = false);
      void set(int row, int col, T item);
      std::vector<T *> getNeighbors(int row, int col, bool diagonals = true);
      GridSize size();
      Grid<T>();
  };
};

using namespace advent;

template <class T>
Grid<T>::Grid() {
  this->grid = std::vector<std::vector<T>>(0);
}

template <class T>
std::vector<std::vector<T>> Grid<T>::getGrid() {
  return this->grid;
}

template <class T>
void Grid<T>::readFile(std::string filename) {
  std::ifstream file(filename);
  std::string line;
  std::cout << "Reading file...";
  while(std::getline(file, line)) {
    std::vector<T> gridRow;
    for(char c : line) {
      gridRow.push_back(T(atoi(&c)));
    }
    this->grid.push_back(gridRow);
  }
}

template <class T>
T* Grid<T>::safeGet(int row, int col, bool verbose) {
  try {
    return &this->grid.at(row).at(col);
  } catch (std::out_of_range error) {
    if (verbose) std::cout << "Out of range error Row " << row << " Col " << col;
    return nullptr;
  }
}

template <class T>
void Grid<T>::set(int row, int col, T item) {
  this->grid.at(row).at(col) = item;
}

template <class T>
std::vector<T *> Grid<T>::getNeighbors(int row, int col, bool diagonals) {
  std::vector<int> offsets = {-1, 1};
  std::vector<T *> neighbors;
  if (diagonals) {
    offsets = {-1, 0, 1};
    for (int rowOffset : offsets) {
      for (int colOffset : offsets) {
        auto value = this->safeGet(row + rowOffset, col + colOffset, false);
        if (value != nullptr) {
          neighbors.push_back(value);
        }
      }
    }
  } else {
    for (int rowOffset : offsets) {
      auto value = this->safeGet(row + rowOffset, col, false);
      if (value != nullptr) {
        neighbors.push_back(value);
      }
    }
    for (int colOffset : offsets) {
      auto value = this->safeGet(row, col + colOffset, false);
      if (value != nullptr) {
        neighbors.push_back(value);
      }
    }
  }
  return neighbors;
}

template <class T>
GridSize Grid<T>::size() {
  GridSize gridSize;
  std::cout << "Grid size";
  gridSize.rows = this->grid.size();
  std::cout << "Grid size";
  try {
    gridSize.cols = this->grid.at(0).size();
  } catch (std::out_of_range e) {
    gridSize.cols = 0;
  }

  return gridSize;
};

