#include <iostream>
#include <array>

#include "Sudoku.hpp"

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
  sudokuBoard.coutBoard();
  // Check if the test board conforms to the rules of sudoku
  for (int i = 0; i < 9; i++)
  {
    std::cout << "Row no" << i << " : " << sudokuBoard.rowConforms(i) 
              << "| Column no" << i << " : " << sudokuBoard.columnConforms(i) 
              << "| Box no" << i << " : " << sudokuBoard.boxConforms(i) << "\n";
  }
  std::cout << "The whole board : " << sudokuBoard.boardConforms() << "\n";
  sudokuBoard.getCell(0,0)->value = 0;
  std::cout << "Finding the first empty cell, if it exists : ";
  if (sudokuBoard.getFistEmptyCell())
  {
    sudokuBoard.getFistEmptyCell().value()->coutCell();
  }
  else {std::cout << "X\n";}
  sudokuBoard.getCell(0,0)->value = 1;
  //sudokuBoard.solveBoard();
  //sudokuBoard.coutBoard();
  return 0;
}