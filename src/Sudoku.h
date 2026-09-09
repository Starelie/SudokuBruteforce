#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>
#include <vector>

#include "Cell.h"

class Sudoku {
  public:
  Sudoku();
  Sudoku(int * iCells[9][9]);
  ~Sudoku();

  void solveBoard(int iValuePosition,int iCurrentLoop);
  void generateBoard(Cell * iCell, int iValuePosition, int iCurrentLoop);
  void coutBoard();

  void randomizeValues();
  Cell * getFistEmptyCell();

  Cell * incrementCell(Cell * iCell);
  Cell * decrementCell(Cell * iCell);


  bool rowSafe(Cell * iCell, int * iValue);
  bool columnSafe(Cell * iCell, int * iValue);
  bool boxSafe(Cell * iCell, int * iValue);
  bool safeToPlace(Cell * iCell, int * iValue);

  private:

  Cell * mCells[9][9];

  std::vector<Cell *> mChangedCells;

  int * possibleValues[9];
};