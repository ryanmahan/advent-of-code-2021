#include <fstream>
#include <vector>
#include <string>
#include <tuple>

namespace advent {

  class GridSize {
    public:
      int rows;
      int cols;
  };

  class Grid {
    private:
      std::vector<std::vector<int>> grid;
    public:
      std::vector<std::vector<int>> getGrid();
      void readFile(std::string filename);
      int safeGet(int row, int col, bool verbose = false);
      Grid();
      GridSize size();
  };
};
