#include <vector>
#include <iostream>
#include <sstream>
#include <numeric>
#include <fstream>

#define DAYS 80
#define NEW_FISH 8
#define OLD_FISH 6

using namespace std;

vector<int> simulate_day(vector<int>& school) {
  int size = school.size();
  for(int i = 0 ; i < size ; i++) {
    int fish = school.at(i);
    // cout << "fish: " << fish << " " << i << "\n";
    if (fish == 0) {
      school.push_back(NEW_FISH);
      school.at(i) = OLD_FISH;
    } else {
      school.at(i) = fish - 1;
    }
  }
  return school;
}

int main() {
  ifstream file("data.txt");
  string line;
  getline(file, line);
  stringstream stream(line);
  vector<int> school;
  int i;
  for (int i; stream >> i;) {
    school.push_back(i);    
    if (stream.peek() == ',')
      stream.ignore();
  }
  cout << school.size() << "\n";

  for (int i = 0 ; i < DAYS ; i++) {
    cout << "DAY NUMBER " << i << "\n";
    simulate_day(school);
    cout << "SCHOOL COUNT " << school.size() << "\n";
  }
  cout << school.size();
}