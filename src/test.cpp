#include <iostream>
#include <array>

#include "Sudoku.hpp"

void TestConformityFunctions(Sudoku iSudokuBoard)
{
  // Check if the test board conforms to the rules of sudoku
  for (int i = 0; i < 9; i++)
  {
    std::cout << "Row no" << i + 1 << " : " << iSudokuBoard.rowConforms(i) 
              << " | Column no" << i + 1 << " : " << iSudokuBoard.columnConforms(i) 
              << " | Box no" << i + 1 << " : " << iSudokuBoard.boxConforms(i) << "\n";
  }
  std::cout << "The whole board : " << iSudokuBoard.boardConforms() << "\n";
}

void TestGetFirstEmptyCellFunction(Sudoku iSudokuBoard, int iTestedRow = 0, int iTestedColumn = 0)
{
  int wCellValue = iSudokuBoard.getCell(iTestedRow, iTestedColumn)->value;
  iSudokuBoard.getCell(iTestedRow, iTestedColumn)->value = 0;
  std::cout << "Finding the first empty cell, if it exists : ";
  if (iSudokuBoard.getFistEmptyCell())
  {
    iSudokuBoard.getFistEmptyCell().value()->coutCell();
  }
  else {std::cout << "X\n";}
  iSudokuBoard.getCell(iTestedRow, iTestedColumn)->value = wCellValue;
}

void TestCoutBoard(Sudoku iSudokuBoard)
{
  iSudokuBoard.coutBoard();
}

void TestSolveBoard(Sudoku iSudokuBoard)
{
  iSudokuBoard.solveBoard();
  iSudokuBoard.coutBoard();
}

int main()
{
  std::array<std::array<int, 9>, 9> SudokuValues =
  {{
    {{1,2,3,4,5,6,7,8,9}},
    {{4,5,6,7,8,9,1,2,3}},
    {{7,8,9,1,2,3,4,5,6}},
    {{9,1,2,3,4,5,6,7,8}},
    {{3,4,5,6,7,8,9,1,2}},
    {{6,7,8,9,1,2,3,4,5}},
    {{8,9,1,2,3,4,5,6,7}},
    {{2,3,4,5,6,7,8,9,1}},
    {{5,6,7,8,9,1,2,3,4}}
  }};

  std::cout << "Cell values declared\n";
  Sudoku sudokuBoard{SudokuValues};
  std::cout << "Sudoku object created\n";
  return 0;
}