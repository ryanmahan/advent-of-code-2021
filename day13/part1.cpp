#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>

// combine two not-equally sized vectors, both ordered correctly
std::vector<bool> combine(std::vector<bool> v1, std::vector<bool> v2) {
  std::vector<bool> smaller = v1.size() > v2.size() ? v2 : v1;
  std::vector<bool> larger = v1.size() > v2.size() ? v1 : v2;
  std::vector<bool> result(larger);
  for (int i = 0 ; i < smaller.size() ; i++) {
    result.at(i) = v1.at(i) || v2.at(i);
  }
  if (smaller.size() != larger.size()) {
    for (int i = smaller.size() ; i < larger.size() ; i++) {
      result.at(i) = larger.at(i);
    }
  }
  return result;
}

void print(std::vector<std::vector<bool>> dots) {
  for (std::vector<bool> row : dots) {
    for (bool dot : row) {
      if (dot) {
        std::cout << "# ";
      } else {
        std::cout << ". ";
      }
    }
    std::cout << std::endl;
  }
}

std::vector<std::vector<bool>> foldVertically(std::vector<std::vector<bool>> dots, int row) {
  int top = 0;
  int bottom = dots.size() - 1;
  
  std::vector<std::vector<bool>> result;
  while (top != row && bottom != row) {
    result.push_back(combine(dots.at(top), dots.at(bottom)));
    top++;
    bottom--;
  }
  return result;
}

std::vector<std::vector<bool>> foldHorizontally(std::vector<std::vector<bool>> dots, int col) {
  int left = 0;
  int right = dots.at(0).size() - 1;

  std::vector<std::vector<bool>> result;
  for (int i = 0 ; i < dots.size(); i++) {
    std::vector<bool> leftSubvector(dots.at(i).begin(), dots.at(i).begin() + col);
    std::vector<bool> rightSubvector(dots.at(i).begin() + col + 1, dots.at(i).end());
    std::reverse(rightSubvector.begin(), rightSubvector.end());
    result.push_back(combine(leftSubvector, rightSubvector));
  }
  return result; 
}

int countDots(std::vector<std::vector<bool>> dots) {
  return std::accumulate(dots.begin(), dots.end(), 0, [](int sum, std::vector<bool> row) {
    return sum + std::accumulate(row.begin(), row.end(), 0);
  });
}

int main() {
  std::ifstream file("test.txt");
  std::string line;
  std::vector<std::vector<bool>> dots = { { false } };
  while(std::getline(file, line) && line.find(',') != std::string::npos) {
    int separator = line.find(',');
    int col = atoi(line.substr(0, separator).c_str());
    int row = atoi(line.substr(separator+1, line.length() - separator).c_str());
    int colsize = col > dots.at(0).size()-1 ? col + 1 : dots.at(0).size();
    int rowsize = row > dots.size()-1 ? row + 1 : dots.size();
    if (rowsize > dots.size()) {
      dots.resize(rowsize, std::vector<bool>(colsize));
    }
    if (colsize > dots.at(0).size()) {
      for (std::vector<bool> &row : dots) {
        row.resize(colsize);
      }
    }
    std::cout << "dot  " << row << ", " << col << std::endl;
    std::cout << "size " << dots.size() << ", " << dots.at(0).size() << std::endl;
    
    dots.at(row).at(col) = true;
  }
  print(dots);
  std::cout << countDots(dots) << std::endl;
  while(std::getline(file, line)) {
    char axis;
    int foldLine;
    std::cout << line << std::endl;
    sscanf(line.c_str(), "fold along %c=%d", &axis, &foldLine);
    std::cout << axis << " " << foldLine << std::endl;
    if (axis == 'x') {
      dots = foldHorizontally(dots, foldLine);
    } else {
      dots = foldVertically(dots, foldLine);
    }
    print(dots);
    std::cout << countDots(dots) << std::endl;
  }
}