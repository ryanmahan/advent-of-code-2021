#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <numeric>

#define OFFSETS std::vector<int>({ -1, 1 })

int safeGetValue(std::vector<std::vector<int>> points, int i, int j) {
  try { 
    return points.at(i).at(j);
  } catch (const std::out_of_range& e) {
    return std::numeric_limits<int>::max(); 
  }
}

std::vector<std::pair<int, int>> findLowestPoints(std::vector<std::vector<int>> points) {
  std::vector<std::pair<int, int>> lowestPoints;
  for (int i = 0 ; i < points.size() ; i++) {
    for (int j = 0 ; j < points[i].size() ; j++ ) {
      
      bool lowest = true;
      for (int vOffset : OFFSETS) {
        int nearby = safeGetValue(points, i + vOffset, j);
        if (nearby <= points[i][j]) {
          // std::cout << nearby << " at " << i + vOffset << " " << j + hOffset << std::endl;
          // std::cout << points[i][j] << " at " << i << " " << j << std::endl;
          // std::cout << std::endl;
          lowest = false;
        }
      }
      for (int hOffset : OFFSETS) {
        int nearby = safeGetValue(points, i, j + hOffset);
        if (nearby <= points[i][j]) {
          lowest = false;
        }
      }
      if (lowest) {
        lowestPoints.push_back({ i, j });
      }
    }
  }
  return lowestPoints;
}

int getBasinSize(std::pair<int, int> point, std::vector<std::vector<int>> points) {
  // base case, 9 or ?all surrounding numbers are smaller? return one
  // otherwise call getBasinSize on all surrounding non-nine numbers that are larger
  int i = point.first;
  int j = point.second;
  int height = safeGetValue(points, i, j);

  for (int offset : OFFSETS) {
    int nearby = safeGetValue(points, i + offset, j);
    if (nearby > height && nearby < 9) {
      return 1 + getBasinSize({ i +offset, j }, points);
    }
  }
  for (int offset : OFFSETS) {
    int nearby = safeGetValue(points, i, j + offset);
    if (nearby > height && nearby < 9) {
      return 1 + getBasinSize({ i, j + offset}, points);
    }
  }
  return 1;
}

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
  std::vector<std::pair<int, int>> lowestPoints = findLowestPoints(points);
  std::vector<int> largestBasins(3, 0);
  for (std::pair<int, int> point : lowestPoints) {
    int size = getBasinSize(point, points);
    std::cout << size << std::endl;
    std::vector<int>::iterator smallestBasin = std::min_element(largestBasins.begin(), largestBasins.end());
    if (size > *smallestBasin) {
      *smallestBasin = size;
    }
  }
  int product = std::accumulate(largestBasins.begin(), largestBasins.end(), 1, std::multiplies<int>());
  for (int size : largestBasins) {
    std::cout << "Basin size: " << size << std::endl;
  }
  std::cout << product << std::endl;
  return 0;
}