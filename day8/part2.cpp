#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
#include <set>

#define LENGTHS std::vector<int>({6, 2, 5, 6, 4, 5, 6, 3, 7, 6})

std::set<char> stringToCharSet(std::string str) {
  std::set<char> charSet;
  for (char c : str) {
    charSet.emplace(c);
  }
  return charSet;
}

int intersectingElements(std::set<char> set1, std::set<char> set2) {
  std::set<char> intersection;
  std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(intersection, intersection.begin()));
  return intersection.size();
}

std::vector<std::set<char>> getEncoding(std::vector<std::string> combos) {
  std::vector<std::set<char>> confirmed(10);
  
  for (int i = 0 ; i < combos.size() ; i++) {
    if (combos[i].length() == LENGTHS[1]) {
      confirmed[1] = stringToCharSet(combos[i]);
    } else if (combos[i].length() == LENGTHS[4]) {
      confirmed[4] = stringToCharSet(combos[i]);
    } else if (combos[i].length() == LENGTHS[7]) {
      confirmed[7] = stringToCharSet(combos[i]);
    } else if (combos[i].length() == LENGTHS[8]) {
      confirmed[8] = stringToCharSet(combos[i]);
    }
  }

  int hasSeven = -1, hasOne = -1, hasFour = -1;
  for (int i = 0 ; i < combos.size() ; i++) {
    std::set<char> unknownNumberSet = stringToCharSet(combos[i]);
    int intersectionsWithFour = intersectingElements(unknownNumberSet, confirmed[4]);
    // is a 2, 3, or 5, determinable by intersections with 4
    if (combos[i].length() == 5) {
      int intersectionsWithOne = intersectingElements(unknownNumberSet, confirmed[1]);
      if (intersectionsWithOne == 2) {
        confirmed[3] = unknownNumberSet;
      // a 2 or 5
      } else {
        if (intersectionsWithFour == 3) {
          confirmed[5] = unknownNumberSet;
        } else {
          confirmed[2] = unknownNumberSet;
        }
      }
    // a 0, 6, or 9
    } else if (combos[i].length() == 6) {
      if (intersectionsWithFour == 4) {
        confirmed[9] = unknownNumberSet;
      // a 0, or 6
      } else {
        int intersectionsWithOne = intersectingElements(unknownNumberSet, confirmed[1]);
        if (intersectionsWithOne == 1) {
          confirmed[6] = unknownNumberSet;
          // a 0
        } else {  
          confirmed[0] = unknownNumberSet;
        }
      }
    }
  }
  return confirmed;
}

int decodeString(std::string number, std::vector<std::set<char>> confirmedSet) {
  std::cout << "decoding... " << number << std::endl; 
  std::set<char> unknownCharSet = stringToCharSet(number);
  std::vector<std::set<char>>::iterator iter = std::find(confirmedSet.begin(), confirmedSet.end(), unknownCharSet);
  if (iter == confirmedSet.end()) {
    std::cout << "ERROR: " << number << std::endl;
    return -1;
  }
  return iter - confirmedSet.begin();
}

int decodeScreen(std::vector<std::string> numbers, std::vector<std::set<char>> confirmedSet) {
  std::ostringstream decoded;
  for (std::string number : numbers) {
    int decodedNumber = decodeString(number, confirmedSet);
    decoded << decodedNumber;
  }
  return atoi(decoded.str().c_str());
}

int main() {
  std::ifstream file("data.txt");
  std::string line;
  int total = 0;
  while(std::getline(file, line)) {
    std::stringstream stream(line);
    std::vector<std::string> combos(10);
    std::vector<std::string> numbers;
    for(int i = 0 ; i < combos.size() ; i++) {
      stream >> combos[i];
      std::cout << "COMBO: " << combos[i] << std::endl;
    }
    std::vector<std::set<char>> confirmedSet = getEncoding(combos);
    std::string number;
    // ignore space
    stream.ignore();
    // ignore pipe
    if (stream.peek() == '|')
        stream.ignore();
    while(stream >> number) {
      std::cout << "NUMBER: " << number << "\n";
      if (number.length() > 1)
        numbers.push_back(number);
    }
    for (int i = 0 ; i < confirmedSet.size() ; i++) {
      std::cout << i << " ";
      for (char c : confirmedSet[i]) {
        std::cout << c;
      }
      std::cout << std::endl;
    }
    total += decodeScreen(numbers, confirmedSet);
  }
  std::cout << total;
}