#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>
#include <vector>
#include <array>

#include "Cell.h"

class Sudoku {
  public:
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


  bool rowSafe(Cell* iCell, int iValue);
  bool columnSafe(Cell* iCell, int iValue);
  bool boxSafe(Cell* iCell, int iValue);
  bool safeToPlace(Cell* iCell, int iValue);

  private:

  std::array<std::array<Cell*, 9>, 9> mCells;

  std::vector<Cell*> mChangedCells;

  int possibleValues[9];
};