#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>

#include "Sudoku.hpp"

Sudoku::Sudoku() 
{
  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      mBoard[row][column] = new Cell{0, row, column};
      mOriginalBoard[row][column] = new Cell{0, row, column};
    }
  }
}

void Sudoku::Cell::coutCell()
{
  std::cout << "(" << this->row << ";" << this->column << ") -> " << this->value << "\n";
}

Sudoku::Sudoku(std::array<std::array<int, 9>, 9> iCells) 
{
  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      mBoard[row][column] = new Cell{iCells[row][column], row, column};
      mOriginalBoard[row][column] = new Cell{iCells[row][column], row, column};
    }
  }
}

Sudoku::Sudoku(std::array<std::array<Cell, 9>, 9> iCells) 
{
  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      mBoard[row][column] = new Cell{iCells[row][column]};
    }
  }
}

Sudoku::~Sudoku() {}

void Sudoku::coutBoard()
{
  for (int row = 0; row < 9; row++)
  {
    if (row % 3 == 0)
    {
      for (int i = 0; i < 25; i++)
      {
        std::cout << "-";
      }
      std::cout << "\n";
    }
    for (int column = 0; column < 9; column++)
    {
      if (column % 3 == 0)
      {
        std::cout << "| ";
      }
      std::cout << mBoard[row][column]->value << " ";
    } 
    std::cout << "|\n";
  }
  for (int i = 0; i < 25; i++)
  {
    std::cout << "-";
  }
  std::cout << "\n";
}

static void coutBoard(std::array<std::array<Sudoku::Cell*, 9>, 9> iBoard)
{
  for (int row = 0; row < 9; row++)
  {
    if (row % 3 == 0)
    {
      for (int i = 0; i < 25; i++)
      {
        std::cout << "-";
      }
      std::cout << "\n";
    }
    for (int column = 0; column < 9; column++)
    {
      if (column % 3 == 0)
      {
        std::cout << "| ";
      }
      std::cout << iBoard[row][column]->value << " ";
    } 
    std::cout << "|\n";
  }
  for (int i = 0; i < 25; i++)
  {
    std::cout << "-";
  }
  std::cout << "\n";
}

void Sudoku::randomizeValues()
{
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(possibleValues.begin(), possibleValues.end(), g);
}

Sudoku::Cell* Sudoku::getCell(int iRow, int iColumn)
{
  return mBoard[iRow][iColumn];
}

std::optional<Sudoku::Cell*> Sudoku::getFistEmptyCell()
{
  for (std::array<Cell*, 9> mRow : mBoard)
  {
    for (Cell* mCell : mRow)
    {
      if (mCell->value == 0)
      {
        return mCell;
      }
    }
  }
  return {};
}

bool Sudoku::rowConforms(int iRow)
{
  std::vector<int> rowValues;
  for (int column = 0; column < 9; column++)
  {
    if (std::find(rowValues.begin(), rowValues.end(), mBoard[iRow][column]->value) != rowValues.end())
    {
      return false;
    }
    if (mBoard[iRow][column]->value != 0)
    {
      rowValues.emplace_back(mBoard[iRow][column]->value);
    }
  }
  return true;
}

bool Sudoku::rowWillConform(Cell* iChangedCell, int iValue)
{
  for (int column = 0; column < 9; column++)
  {
    if (iValue == mBoard[iChangedCell->row][column]->value &&
        iValue != 0)
    {
      return false;
    }
  }
  return true;
}

bool Sudoku::columnConforms(int iColumn)
{
  std::vector<int> columnValues;
  for (int row = 0; row < 9; row++)
  {
    if (std::find(columnValues.begin(), columnValues.end(), mBoard[row][iColumn]->value) != columnValues.end())
    {
      return false;
    }
    if (mBoard[row][iColumn]->value != 0)
    {
      columnValues.emplace_back(mBoard[row][iColumn]->value);
    }
  }
  return true;
}

bool Sudoku::columnWillConform(Cell* iChangedCell, int iValue)
{
  for (int row = 0; row < 9; row++)
  {
    if (iValue == mBoard[row][iChangedCell->column]->value &&
        iValue != 0)
    {
      return false;
    }
  }
  return true;
}

bool Sudoku::boxConforms(int iBox)
{
  std::vector<int> boxValues;
  int BoxStartRow = 3 * (iBox % 3);
  int BoxStartColumn = 3 * int(iBox / 3);
  for (int row = 0; row < 3; row++)
  {
    for (int column = 0; column < 3; column++)
    {
      if (std::find(boxValues.begin(), boxValues.end(), mBoard[BoxStartRow + row][BoxStartColumn + column]->value) != boxValues.end())
      {
        return false;
      }
      if (mBoard[BoxStartRow + row][BoxStartColumn + column]->value != 0)
      {
        boxValues.emplace_back(mBoard[BoxStartRow + row][BoxStartColumn + column]->value);
      }
    }
  }
  return true;
}

bool Sudoku::boxWillConform(Cell* iChangedCell, int iValue)
{
  int BoxStartRow = iChangedCell->row - iChangedCell->row % 3;
  int BoxStartColumn = iChangedCell->column - iChangedCell->column % 3;
  for (int row = 0; row < 3; row++)
  {
    for (int column = 0; column < 3; column++)
    {
      if (iValue == mBoard[BoxStartRow + row][BoxStartColumn + column]->value &&
          iValue != 0)
      {
        return false;
      }
    }
  }
  return true;
}

bool Sudoku::boardConforms()
{
  for (int i = 0; i < 9; i++)
  {
    if (!(rowConforms(i) && columnConforms(i) && boxConforms(i)))
    {
      return false;
    }
  }
  return true;
}

bool Sudoku::safeToPlace(Cell* iCell, int iValue)
{
  return (boxWillConform(iCell, iValue) && rowWillConform(iCell, iValue) && columnWillConform(iCell, iValue));
}

Sudoku::Cell* Sudoku::incrementCell(Cell* iCell)
{
  int outputCellRow = iCell->row;
  int outputCellColumn = iCell->column;
  if (outputCellColumn == 8)
  {
    outputCellColumn = -1;
    outputCellRow++;
  }
  outputCellColumn++;
  return mBoard[outputCellRow][outputCellColumn];
}

Sudoku::Cell* Sudoku::decrementCell(Cell* iCell)
{
  int outputCellRow = iCell->row;
  int outputCellColumn = iCell->column;
  if (outputCellColumn == 0)
  {
    outputCellColumn = 9;
    outputCellRow--;
  }
  outputCellColumn--;
  return mBoard[outputCellRow][outputCellColumn];
}

void Sudoku::solveBoard()
{
  std::cout << "solving...\n";
}
