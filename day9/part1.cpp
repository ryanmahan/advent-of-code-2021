#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <limits>

int main() {
  std::ifstream file("data.txt");
  char point;
  int sum = 0;
  std::vector<std::vector<int>> points;
  std::string line;
  
  while (std::getline(file, line)) {
    std::vector<int> pointLine;
    std::stringstream lineStream(line);
    while(lineStream.get(point)) {
      if (std::isdigit(point))
        pointLine.push_back(point - 48);
    }
    points.push_back(pointLine);
  }

  for (int i = 0 ; i < points.size() ; i++) {
    for (int j = 0 ; j < points[i].size() ; j++ ) {
      std::vector<int> verticalOffsets({ -1, 1 });
      std::vector<int> horizontalOffsets({ -1, 1 });
      bool lowest = true;
      for (int vOffset : verticalOffsets) {
        int nearby = std::numeric_limits<int>::max();
        try { 
          nearby = points.at(i + vOffset).at(j);
        } catch (const std::out_of_range& e) { nearby = std::numeric_limits<int>::max(); }
        if (nearby <= points[i][j]) {
          // std::cout << nearby << " at " << i + vOffset << " " << j + hOffset << std::endl;
          // std::cout << points[i][j] << " at " << i << " " << j << std::endl;
          // std::cout << std::endl;
          lowest = false;
        }
      }
      for (int hOffset : horizontalOffsets) {
        int nearby = std::numeric_limits<int>::max();
        try { 
          nearby = points.at(i).at(j + hOffset);
        } catch (const std::out_of_range& e) { nearby = std::numeric_limits<int>::max(); }
        if (nearby <= points[i][j]) {
          lowest = false;
        }
      }
      if (lowest) {
        try {
          std::cout << points.at(i).at(j) << " is lowest at " << i << " " << j << std::endl;
          std::cout << points.at(i-1).at(j-1) << points.at(i-1).at(j) << points.at(i-1).at(j+1) << std::endl;
          std::cout << points.at(i).at(j-1) << points.at(i).at(j) << points.at(i).at(j+1) << std::endl;
          std::cout << points.at(i+1).at(j-1) << points.at(i+1).at(j) << points.at(i+1).at(j+1) << std::endl;
        } catch (const std::out_of_range& e) { }
        
        sum += points[i][j] + 1;
      }
    }
  }
  std::cout << sum << std::endl;
}