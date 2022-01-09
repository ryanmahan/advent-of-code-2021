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

std::map<char, long> pair_insertion(std::string base, std::map<std::string, char> productMap) {
  std::map<std::string, long> pairs = { { base, 1 } };
  std::map<char, long> counts;
  for (int i = 0 ; i < STEPS ; i++) {
    std::map<std::string, long> new_pairs;
    for (std::pair<std::string, long> pair_count : pairs) {
      std::string pair = pair_count.first;
      long count = pair_count.second;
      if (count <= 0) continue;
      char resultant = productMap.at(pair);
      if (counts.find(resultant) == counts.end()) {
        counts.emplace(resultant, 1);
      } else {
        counts.at(resultant) += count;
      }
      std::string product1{pair.at(0), resultant};
      std::string product2{resultant, pair.at(1)};
      std::vector<std::string> products({ product1, product2 });

      // std::cout << "pair " << pair << std::endl;
      // std::cout << "count " << count << std::endl;
      // std::cout << "result " << productMap.at(pair) << std::endl;
      // std::cout << "p1 " << product1 << std::endl;
      // std::cout << "p2 " << product2 << std::endl;

      for (std::string product : products) { 
        if (new_pairs.find(product) != new_pairs.end()) {
          new_pairs.at(product) += count;
        } else {
          new_pairs.emplace(product, count);
        }
      }
    }
    pairs = new_pairs;
  }
  return counts;
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

  std::cout << "start threads" << std::endl;
  std::vector<std::future<std::map<char, long>>> futures;
  for (int i = 0 ; i < polymer.length() - 1 ; i++) {
    std::string chem = polymer.substr(i, 2);
    futures.push_back(std::async(pair_insertion, chem, productMap));
  }

  std::map<char, long> totals;
  std::cout << "init totals" << std::endl;
  for (char chem : chemicals) {
    std::cout << chem << " " << std::count(polymer.begin(), polymer.end(), chem);
    totals.emplace(chem, std::count(polymer.begin(), polymer.end(), chem));
  }

  std::cout << "sum totals" << std::endl;
  for (std::future<std::map<char, long>> &future_counts : futures) {
    std::map<char, long> counts = future_counts.get();
    for (std::pair<char, long> count : counts) {
      totals.at(count.first) += count.second;
    }
  }

  std::cout << "find min/max" << std::endl;
  long most_common = 0;
  long least_common = std::numeric_limits<long>::max();
  for(char chem : chemicals) {
    long occurence = totals.at(chem);
    std::cout << chem << " " << occurence << std::endl;
    if (occurence < least_common) least_common = occurence;
    if (occurence > most_common) most_common = occurence;
  }
  std::cout << most_common << std::endl;
  std::cout << least_common << std::endl;
  return 0;
}