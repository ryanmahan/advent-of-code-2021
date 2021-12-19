#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "board.h"
using namespace std;
using namespace bingo;

int main() {
  ifstream file = ifstream("data.txt");
  string call_list_str;
  getline(file, call_list_str);
  std::stringstream call_list_stream = stringstream(call_list_str);
  string call;
  int call_position = 0;
  vector<int> call_list;
  while (getline(call_list_stream, call, ',')) {
    call_list.push_back(stoi(call));
  }
  string line;
  vector<Board> boards;
  vector<vector<int>> winners = { vector<int>(), vector<int>(), vector<int>(), vector<int>(), vector<int>() };
  int column = 0;
  while (getline(file, line)) {
    // cout << "line " << line << " " << line.size() << "\n";
    // when there is an empty line, save into a board and reset winners
    if (line.size() == 0) {
      if (winners.size() > 5) {
        boards.push_back(Board(winners));
      }
      winners = { vector<int>(), vector<int>(), vector<int>(), vector<int>(), vector<int>() };
      continue;
    }
    stringstream board_stream = stringstream(line);
    vector<int> winner = vector<int>();
    // iterate over each number, add to row and corresponding column 
    while (!board_stream.eof()) {
      string word;
      board_stream >> word;
      int value;
      if (stringstream(word) >> value) {
        // cout << "value " << value << "\n";
        // cout << "column " << column << "\n";
        winner.push_back(value);
        winners.at(column%5).push_back(value);
        column++;
      }
    }
    winners.push_back(winner);
  }
  // push back final board
  boards.push_back(Board(winners));

  // part 1, find winning board
  int winning_board = -1;
  int winning_call_number = 100000;
  for (int i = 0 ; i < boards.size() ; i++) {
    Board& board = boards.at(i);
    int call_number = board.find_winning_move(call_list);
    if (call_number < winning_call_number) {
      winning_board = i;
      winning_call_number = call_number;
    }
  }

  // part 2, find losing board
  int losing_board = -1;
  int losing_call_number = 0;
  for (int i = 0 ; i < boards.size() ; i++) {
    Board& board = boards.at(i);
    int call_number = board.find_winning_move(call_list);
    if (call_number > losing_call_number) {
      losing_board = i;
      losing_call_number = call_number;
    }
  }

  cout << "boards " << boards.size() << "\n";
  cout << "winning board number " << winning_board << "\n";
  cout << "winning board score " << boards.at(winning_board).score_board(call_list) << "\n";
  cout << "losing board number " << losing_board << "\n";
  cout << "losing board score " << boards.at(losing_board).score_board(call_list) << "\n";
  return 0;
}