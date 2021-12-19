#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <set>
#include <numeric>
using namespace std;

namespace bingo {
  class Board {
    private:
      vector<vector<int>> winners;
      
      int score;
    public:
      Board(vector<vector<int>> winners);
      int find_winning_move (vector<int> list);
      int score_board (vector<int> call_list);
      set<int> get_numbers();
      int winning_move = -1;
    };
};

#endif //_BOARD_H_