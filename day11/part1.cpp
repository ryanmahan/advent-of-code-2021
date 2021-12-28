#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Grid.h"

using namespace advent;

int main() {
  Grid grid;
  int rows, cols;
  grid.readFile("data.txt");
  [rows, cols] = grid.size();
}