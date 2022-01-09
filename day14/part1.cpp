#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <future>
#include <vector>
#include <string>
#include <set>
#include <limits>

#define STEPS 40

std::string pair_insertion(std::string base, std::map<std::string, char> productMap) {
  for (int i = 0 ; i < STEPS ; i++) {
    std::cout << i << std::endl;
    std::string new_base = "";
    int len = base.length();
    for (int j = 0 ; j < len - 1 ; j++) {
      char new_product = productMap.at(base.substr(j, 2));
      new_base += base.at(j);
      new_base += new_product;
    }
    new_base += base.at(base.length() - 1);
    base = new_base;
  }
  return base;
}

int main() {
  std::ifstream file("data.txt");
  std::string line, polymer;
  std::getline(file, polymer);
  std::set<char> chemicals;
  const int steps = 10;
  std::map<std::string, char> productMap;

  while(std::getline(file, line)) {
    std::cout << line << std::endl;
    if (!line.length() > 0) continue;
    std::string precursor = line.substr(0, 2);
    char product = line.substr(6, 1)[0];
    productMap.insert({ precursor, product });
    chemicals.insert(product);
  }

  std::vector<std::future<std::string>> futures;
  for (int i = 0 ; i < polymer.length() - 1 ; i++) {
    std::string chem = polymer.substr(i, 2);
    futures.push_back(std::async(pair_insertion, chem, productMap));
  }

  std::string end_polymer = "";
  for (std::future<std::string> &future_string : futures) {
    std::string result = future_string.get();
    end_polymer = end_polymer.substr(0, end_polymer.length() - 1);
    end_polymer += result;
  }

  // std::cout << std::endl;
  // std::cout << end_polymer << std::endl;

  long most_common = 0;
  long least_common = std::numeric_limits<long>::max();
  for(char chem : chemicals) {
    long occurence = std::count(end_polymer.begin(), end_polymer.end(), chem);
    if (occurence < least_common) least_common = occurence;
    if (occurence > most_common) most_common = occurence;
  }
  std::cout << most_common << std::endl;
  std::cout << least_common << std::endl;
  return 0;
}