#include <vector>
#include <array>
#include <optional>

class Sudoku {
  public:

  struct Cell
  {
    int value = 0;
    int row = 0;
    int column = 0;

    void coutCell();
  };

  Sudoku();
  Sudoku(std::array<std::array<int, 9>, 9> iCells);
  Sudoku(std::array<std::array<Cell, 9>, 9> iCells);
  ~Sudoku();

  void solveBoard();
  void generateBoard();
  void coutBoard();

  void randomizeValues();

  std::optional<Cell*> getFistEmptyCell();
  Cell* getCell(int iRow, int iColumn);

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