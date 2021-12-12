#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <bitset>
using namespace std;

int main() {
  std::ifstream file = std::ifstream("data.txt");
  std::string line;
  int linecount = 0;
  std::getline(file, line);
  int sums[line.length()] = { 0 };
  
  do {
    for (int i = 0 ; i < line.length() ; i++) {
      if (line.at(i) == '1') {
        sums[i]++;
      }
    }
    linecount++;
  } while (std::getline(file, line));

  uint32_t gamma = 0;
  uint32_t epsilon = 0;

  for (int i = 0 ; i < line.length() ; i++) {
    int result = (sums[i] > (linecount / 2));
    cout << result;
    cout << "\n";
    gamma = (gamma << 1) | result;
    epsilon = (epsilon << 1) | !result;
    cout << sums[i] << " ";
  }
  std::string gammabits = std::bitset<16>(gamma).to_string();
  std::string epsilonbits = std::bitset<16>(epsilon).to_string();
  printf("\n%s %s\n %d %d %d\n", gammabits.c_str(), epsilonbits.c_str(), gamma, epsilon, gamma * epsilon);
};
