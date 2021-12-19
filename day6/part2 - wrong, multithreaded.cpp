#include <vector>
#include <iostream>
#include <sstream>
#include <numeric>
#include <fstream>
#include <thread>
#include <future>

#define DAYS 80
#define NEW_FISH 8
#define OLD_FISH 6
#define THREADS 12

using namespace std;


int fish_count(int fish_days, int days_left) {
  if (days_left <= fish_days) {
    return 1;
  } else {
    return fish_count(7, days_left - fish_days) +
    fish_count(9, days_left - fish_days);
  }
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
  
  int fish_total = 0;
  vector<future<int>> futures;
  vector<int> return_vals;
  for (int fish : school) {
    int return_val = 0;
    futures.push_back(async(fish_count, fish, DAYS));
  }
  for (future<int> &future : futures) {
    int one_fish_total = future.get();
    cout << one_fish_total << "\n";
    fish_total += one_fish_total;
  }

  cout << fish_total;
}