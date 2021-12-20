#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#define LENGTHS std::vector<int>({ 6, 2, 5, 6, 4, 5, 6, 3, 7, 6 })
#define DELIMITER '|'

int main() {
  std::ifstream file("data.txt");
  std::string line;
  int count = 0;
  while(std::getline(file, line)) {
    int pos = line.find(DELIMITER);
    std::string segments = line.substr(pos, std::string::npos);
    std::stringstream stream(segments);
    std::string segment;
    std::cout << "NEWLINE" << std::endl;
    while (std::getline(stream, segment, ' ')) {
      int length = segment.length();
      std::cout << segment << "|" << length << std::endl;
      if (length == LENGTHS[1] || length == LENGTHS[4] || length == LENGTHS[7] || length == LENGTHS[8]) {
        std::cout << "COUNTED" << std::endl;
        count++;
      } 
    }
  }
  std::cout << count << std::endl;
  std::cout << LENGTHS[1] << LENGTHS[4] << LENGTHS[7] << LENGTHS[8];
}