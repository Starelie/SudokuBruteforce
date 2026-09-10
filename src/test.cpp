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

  for (unsigned int i = 0; i < SudokuValues.size(); i++)
  {
    for (unsigned int j = 0; j < SudokuValues[0].size(); j++)
      {
        std::cout << SudokuValues[i][j] << " ";
      }
    std::cout << "\n";
  }

  //Sudoku sudokuBoard{SudokuValues};
  return 0;
}