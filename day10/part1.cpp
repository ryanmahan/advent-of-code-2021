#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

int scoreFirstIllegalCharacter(std::string line) {
  std::stack<char> chunks;
  std::map<char, char> validityMap({{ ']', '[' }, {'}', '{'}, {')', '('}, {'>', '<'}});
  std::map<char, int> scoreMap({{')', 3}, { ']', 57}, {'}', 1197}, {'>', 25137}});
  for (char c : line) {
    if (c == '[' || c == '{' || c == '(' || c == '<') {
      chunks.push(c);
    } else {
      char expected = chunks.top();
      chunks.pop();
      if (validityMap.at(c) != expected) {
        return scoreMap.at(c);
      }
    }
  }
  return 0;
}

int main() {
  std::ifstream file("data.txt");
  std::string line;
  int sum = 0;
  while(std::getline(file, line)) {
    sum += scoreFirstIllegalCharacter(line);
  }
  std::cout << sum << std::endl;
}