#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

long scoreFirstIllegalCharacter(std::string line) {
  std::stack<char> chunks;
  std::map<char, char> validityMap({{ ']', '[' }, {'}', '{'}, {')', '('}, {'>', '<'}});
  std::map<char, int> scoreMap({{'(', 1}, { '[', 2}, {'{', 3}, {'<', 4}});
  for (char c : line) {
    if (c == '[' || c == '{' || c == '(' || c == '<') {
      chunks.push(c);
    } else {
      char expected = chunks.top();
      chunks.pop();
      if (validityMap.at(c) != expected) {
        return -1;
      }
    }
  }
  long score = 0;
  while (chunks.size() > 0) {
    char next = chunks.top();
    std::cout << next << std::endl;
    score *= 5;
    score += scoreMap.at(next);
    std::cout << score << std::endl;
    chunks.pop();
  }
  return score;
}

int main() {
  std::ifstream file("data.txt");
  std::string line;
  std::vector<long> scores;
  while(std::getline(file, line)) {
    long score = scoreFirstIllegalCharacter(line);
    if (score > -1) {
      scores.push_back(score);
    }
  }
  std::sort(scores.begin(), scores.end());
  std::cout << "scores: " << std::endl;
  for (long score : scores) {
    std::cout << score << " ";
  }
  std::cout << std::endl;
  std::cout << scores.size() << std::endl;
  std::cout << scores.at(scores.size()/2 ) << std::endl;
}