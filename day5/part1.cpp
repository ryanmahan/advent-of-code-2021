#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#define MAP_SIZE 1000
using namespace std;

int index_from_coordinates(int x, int y) {
  return y * MAP_SIZE + x;
}

void mark_on_seafloor(vector<int>& seafloor, int start_x, int start_y, int end_x, int end_y) {
  int delta_x = end_x - start_x;
  int delta_y = end_y - start_y;
  int x_modifier = (delta_x > 0) ? 1 : -1;
  int y_modifier = (delta_y > 0) ? 1 : -1;
  delta_x = delta_x * x_modifier;
  delta_y = delta_y * y_modifier;

  cout << delta_x << " ";
  cout << delta_y << "\n";
  // for part 2
  if (delta_x == delta_y) {
    for (int i = 0 ; i <= delta_x && delta_x > 0; i++) {
      int x_pos = start_x + (i * x_modifier);
      int y_pos = start_y + (i * y_modifier);
      int index = index_from_coordinates(x_pos, y_pos);
      seafloor.at(index) = seafloor.at(index) + 1;
    }
  // for part 1
  } else {
    for (int i = 0 ; i <= delta_x && delta_x > 0; i++) {
      int x_pos = start_x + (i * x_modifier);
      int index = index_from_coordinates(x_pos, start_y);
      seafloor.at(index) = seafloor.at(index) + 1;
    }
    for (int i = 0 ; i <= delta_y && delta_y > 0 ; i++) {
      int y_pos = start_y + (i * y_modifier);
      int index = index_from_coordinates(start_x, y_pos);
      seafloor.at(index) = seafloor.at(index) + 1;
    }
  }
}

void print_seafloor(vector<int> seafloor) {
  for (int i = 0 ; i < MAP_SIZE ; i++) {
    for (int j = 0 ; j < MAP_SIZE ; j++) {
      cout << seafloor.at(index_from_coordinates(j, i)) << " ";
    }
    cout << "\n";
  }
}

int count_crossings(vector<int> seafloor) {
  int count = 0;
  for (int spot : seafloor) {
    if (spot > 1) count++;
  }
  return count;
}

int main() {
  vector<int> seafloor(MAP_SIZE * MAP_SIZE, 0);
  ifstream file = ifstream("data.txt");
  regex rgx("([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)");
  smatch matches;
  string line;

  while (getline(file, line)) {
    regex_search(line, matches, rgx);
    if (matches.size() != 5) exit(1);
    int start_x, start_y, end_x, end_y;
    start_x = stoi(matches[1]);
    start_y = stoi(matches[2]);
    end_x = stoi(matches[3]);
    end_y = stoi(matches[4]);
    mark_on_seafloor(seafloor, start_x, start_y, end_x, end_y);
  }
  print_seafloor(seafloor);
  cout << count_crossings(seafloor) << "\n";
}