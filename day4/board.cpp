#include "board.h"
#include <iostream>
#include <algorithm>
using namespace std;
using namespace bingo;


Board::Board(vector<vector<int>> winners) {
  Board::winners = winners;
  this->winning_move = 0;
};

int Board::find_winning_move (vector<int> call_list) {
  int lowest_winner = 1000;
  for (vector<int> winner : winners) {
    int highest_count = 0;
    for (int board_number : winner) {
      // probably a better way to do this, but would require changing the call_list type
      // find is O(n), not great here. A combo of a call list for order keeping and map for O(1) order lookup
      // would take more memory but be less CPU intensive here
      vector<int>::iterator iter = find(call_list.begin(), call_list.end(), board_number);
      if (iter == call_list.end()) continue;
      int position = iter - call_list.begin();
      // find the highest/latest called number
      if (position > highest_count) {
        highest_count = position;
      }
    }
    // if our current latest call number is lower than others, thats our winning col or row
    if (highest_count < lowest_winner) {
      lowest_winner = highest_count;
    }
  }
  this->winning_move = lowest_winner;
  return lowest_winner;
};

int Board::score_board (vector<int> call_list) {
  set<int> board_numbers = Board::get_numbers();
  int called = -1;
  for(int i = 0 ; i <= Board::winning_move ; i++) {
    called = call_list.at(i);
    board_numbers.erase(called);
  }
  int board_sum = accumulate(board_numbers.begin(), board_numbers.end(), 0);
  return board_sum * called;
};

set<int> bingo::Board::get_numbers() {
  set<int> concatenated;
  for (vector<int> row : winners) {
    concatenated.insert(row.begin(), row.end());
  }
  return concatenated;
}
