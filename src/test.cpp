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
  //for (int i = 0; i < 9; i++)
  //{
  //  for (int j = 0; j < 9; j++)
  //  {
  //  }
  //}
  return 0;
}