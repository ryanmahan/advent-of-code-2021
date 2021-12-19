#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

int sum(std::vector<int> values) {
  return std::accumulate(values.begin(), values.end(), 0);
}

int main() {
  std::string line;
  std::ifstream file = std::ifstream("data.txt");
  std::vector<int> values = {0, 0, 0};
  int count = 0;
  int line_number = 3;

  for (int i = 0 ; i < 3 ; i++) {
    std::getline(file, line);
    values[i] += atoi(line.c_str());
  }

  int prevSum = sum(values);
  int newSum = 0;
  while(std::getline(file, line)) {
    int new_value = atoi(line.c_str());
    int bounded_line = line_number % 3;
    values[bounded_line] = new_value;
    newSum = sum(values);
    std::cout << prevSum << " " << newSum << "\n";
    if (newSum > prevSum) {
      count++;
    }
    prevSum = newSum;
    line_number++;
  }    
  std::cout << count;
}