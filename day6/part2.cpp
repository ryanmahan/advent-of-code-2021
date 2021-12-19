#include <vector>
#include <iostream>
#include <sstream>
#include <numeric>
#include <fstream>

#define DAYS 256
#define NEW_FISH 8
#define OLD_FISH 6

using namespace std;

vector<uint64_t> simulate_day(vector<uint64_t>& school) {
  uint64_t temp_fish = school.at(0);
  for (int i = 1 ; i < school.size() ; i++) {
    school.at(i-1) = school.at(i);
  }
  cout << "temp fish " << temp_fish << "\n";
  school.at(6) += temp_fish;
  school.at(8) = temp_fish;
  return school;
}

int main() {
  ifstream file("data.txt");
  string line;
  getline(file, line);
  stringstream stream(line);
  vector<uint64_t> school(9, 0);
  int i;
  for (int i; stream >> i;) {
    school.at(i)++;
    if (stream.peek() == ',')
      stream.ignore();
  }
  for (int i = 0 ; i < DAYS ; i++) {
    cout << "DAY NUMBER " << i << "\n";
    simulate_day(school);
  }
  uint64_t total_fish = 0;
  for (uint64_t count : school) {
    total_fish += count;
  }
  cout << total_fish << "\n";
}