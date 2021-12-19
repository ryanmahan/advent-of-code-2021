#include <fstream>
#include <string>
#include <iostream>

int main() {
  std::ifstream file = std::ifstream("data.txt");
  std::string line, prevLine;
  std::getline(file, prevLine);
  int count = 0;
  while(std::getline(file, line)) {
    if (atoi(line.data()) > atoi(prevLine.data())) {
      count++;
    }
    prevLine = line;
    std::cout << line << "\n";
  }
  std::cout << count;
}