#include <vector>
#include <array>

class Sudoku {
  public:

  struct Cell
  {
    int value = 0;
    int row = 0;
    int column = 0;
  };

  Sudoku();
  Sudoku(std::array<std::array<int, 9>, 9> iCells);
  ~Sudoku();

  void solveBoard(int iValuePosition,int iCurrentLoop = 0);
  void generateBoard(Cell* iCell, int iValuePosition, int iCurrentLoop = 0);
  void coutBoard();

  void randomizeValues();
  Cell* getFistEmptyCell();

  Cell* incrementCell(Cell* iCell);
  Cell* decrementCell(Cell* iCell);

  bool rowConforms(int iRow);
  bool rowSafe(Cell* iCell, int iValue);
  bool columnConforms(int iColumn);
  bool columnSafe(Cell* iCell, int iValue);
  bool boxConforms(int iBox); // From left to right, top to bottom
  bool boxSafe(Cell* iCell, int iValue);
  bool boardConforms();
  bool safeToPlace(Cell* iCell, int iValue);

  private:

  std::array<std::array<Cell*, 9>, 9> mCells;

  std::vector<Cell*> mChangedCells;

  std::array<int, 9> possibleValues = {1, 2, 3, 4, 5, 6, 7, 8, 9};
};