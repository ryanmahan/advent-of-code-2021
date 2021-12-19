#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <limits>

int get_fuel_cost(std::vector<int> positions, int end_point) {
  std::vector<int> fuel_cost(positions.size(), 0);
  std::transform(positions.begin(), positions.end(), fuel_cost.begin(), [end_point](int pos){ return std::abs(end_point - pos); });
  return std::accumulate(fuel_cost.begin(), fuel_cost.end(), 0);
}

int get_fuel_cost_part2(std::vector<int> positions, int end_point) {
  std::vector<int> fuel_cost(positions.size(), 0);
  std::transform(positions.begin(), positions.end(), fuel_cost.begin(), [end_point](int pos){ 
    int dist = std::abs(end_point - pos); 
    return dist * (dist+1) / 2;
  });
  return std::accumulate(fuel_cost.begin(), fuel_cost.end(), 0);
}

int main() {
  std::ifstream file("data.txt");
  std::string line;
  std::getline(file, line);
  std::stringstream stream(line);
  std::vector<int> positions;
  int h_pos;
  while(stream >> h_pos) {
    // std::cout << h_pos << " ";
    positions.push_back(h_pos);
    if (stream.peek() == ',')
      stream.ignore();
  }
  std::cout << positions.size();
  int max = *std::max_element(std::begin(positions), std::end(positions));
  int min = *std::min_element(std::begin(positions), std::end(positions));
  int current = 0, lowest = std::numeric_limits<int>::max(), ideal = -1;
  int lower = std::numeric_limits<int>::max(), higher = std::numeric_limits<int>::max();
  std::cout << "min " << min << " max " << max << "\n";
  // sad brute force method
  
  // for (int i = max ; i > min ; i--) {
  //   current = get_fuel_cost_part2(positions, i);
  //   if (current <= lowest) {
  //     lowest = current;
  //     ideal = i;
  //     // std::cout << lowest << " " << current << " " << i << "\n";
  //   }
  //   std::cout << lowest << " " << current << " " << i << "\n";
  // }

  // happier binary search method
  int step = positions.size() / 2;
  int alpha = step;
  current = get_fuel_cost_part2(positions, step);
  while (alpha != 1) {
    alpha = alpha / 2;
    lower = get_fuel_cost_part2(positions, step - alpha);
    higher = get_fuel_cost_part2(positions, step + alpha);
    if (lower < current) {
      current = lower;
      step = step - alpha;
    } else if (higher < current) {
      current = higher;
      step = step + alpha;
    }
  }
  std::cout << current;
  
}