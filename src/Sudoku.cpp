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
      mCells[row][column] = new Cell{0, row, column};
    }
  }
  randomizeValues();
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
      mCells[row][column] = new Cell{iCells[row][column], row, column};
    }
  }
  randomizeValues();
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
      std::cout << mCells[row][column]->value << " ";
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
  std::shuffle(std::begin(possibleValues), std::end(possibleValues), g);
}

Sudoku::Cell* Sudoku::getCell(int iRow, int iColumn)
{
  return mCells[iRow][iColumn];
}

std::optional<Sudoku::Cell*> Sudoku::getFistEmptyCell()
{
  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      if (mCells[row][column]->value == 0)
      {
        return mCells[row][column];
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
    if (std::find(rowValues.begin(), rowValues.end(), mCells[iRow][column]->value) != rowValues.end())
    {
      return false;
    }
    if (mCells[iRow][column]->value != 0)
    {
      rowValues.emplace_back(mCells[iRow][column]->value);
    }
  }
  return true;
}

bool Sudoku::rowSafe(Cell* iCell, int iValue)
{
  for (int column = 0; column < 9; column++)
  {
    if (iValue == mCells[iCell->row][column]->value &&
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
    if (std::find(columnValues.begin(), columnValues.end(), mCells[row][iColumn]->value) != columnValues.end())
    {
      return false;
    }
    if (mCells[row][iColumn]->value != 0)
    {
      columnValues.emplace_back(mCells[row][iColumn]->value);
    }
  }
  return true;
}

bool Sudoku::columnSafe(Cell* iCell, int iValue)
{
  for (int row = 0; row < 9; row++)
  {
    if (iValue == mCells[row][iCell->column]->value &&
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
      if (std::find(boxValues.begin(), boxValues.end(), mCells[BoxStartRow + row][BoxStartColumn + column]->value) != boxValues.end())
      {
        return false;
      }
      if (mCells[BoxStartRow + row][BoxStartColumn + column]->value != 0)
      {
        boxValues.emplace_back(mCells[BoxStartRow + row][BoxStartColumn + column]->value);
      }
    }
  }
  return true;
}

bool Sudoku::boxSafe(Cell* iCell, int iValue)
{
  int BoxStartRow = iCell->row - iCell->row % 3;
  int BoxStartColumn = iCell->column - iCell->column % 3;
  for (int row = 0; row < 3; row++)
  {
    for (int column = 0; column < 3; column++)
    {
      if (iValue == mCells[BoxStartRow + row][BoxStartColumn + column]->value &&
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
  return (boxSafe(iCell, iValue) && rowSafe(iCell, iValue) && columnSafe(iCell, iValue));
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
  return mCells[outputCellRow][outputCellColumn];
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
  return mCells[outputCellRow][outputCellColumn];
}

void Sudoku::solveBoard(int iValuePosition, int iCurrentLoop)
{
  std::cout << "solving...\n";
}

//void Sudoku::solveBoard(int iValuePosition, int iCurrentLoop)
//{
//  Cell* currentCell = getFistEmptyCell();
//  int testingValuePosition = iValuePosition;
//  int CurrentLoop = iCurrentLoop + 1;
//  // std::cout <<mChangedCells.size();
//  // std::cout << testingValuePosition << "=" <<*possibleValues[testingValuePosition]
//  // <<  " safe:"
//  // << safeToPlace(currentCell, possibleValues[testingValuePosition])
//  // << boxSafe(currentCell, possibleValues[testingValuePosition])
//  // << columnSafe(currentCell, possibleValues[testingValuePosition])
//  // << rowSafe(currentCell, possibleValues[testingValuePosition])
//  // << " | " ;
//  if (CurrentLoop <= 100)
//  // if (CurrentLoop <= 25893)
//  // if (CurrentLoop < 100)
//  {
//    if (CurrentLoop > 25880)
//    {
//      // coutBoard();
//      // currentCell->coutCoordinates();
//      // std::cout << " value : " << *currentCell->value << " tested value : " << *possibleValues[testingValuePosition] << " vector size : " << mChangedCells.size();
//    }
//    if (CurrentLoop > 25880)
//    {
//      std::cout << "hi";
//    }
//    mChangedCells.emplace_back(currentCell);
//    if (safeToPlace(mChangedCells.back(), possibleValues[testingValuePosition]))
//    {
//      currentCell->value = possibleValues[testingValuePosition];
//      // currentCell->coutCoordinates();
//      // std::cout << *currentCell->value << "works" << ";" << std::endl;
//      solveBoard(0, CurrentLoop);
//    }
//    else if (possibleValues[testingValuePosition] < 9)
//    {
//      // currentCell->coutCoordinates();
//      // std::cout << *possibleValues[testingValuePosition] << "retry" << ";" << std::endl;
//      delete mChangedCells.back();
//      mChangedCells.pop_back();
//      testingValuePosition++;
//      solveBoard(testingValuePosition, CurrentLoop);
//    }
//    else
//    {
//      delete mChangedCells.back();
//      mChangedCells.pop_back();
//      testingValuePosition = mChangedCells.back()->value;
//      mChangedCells.back()->value = 0;
//      // currentCell->coutCoordinates();
//      // std::cout << "error" << *mChangedCells.back()->value << ";" << std::endl;
//      // coutBoard();
//      // std::cout << "redo";
//      while (testingValuePosition == 9)
//      {
//        // coutBoard();
//        delete mChangedCells.back();
//        mChangedCells.pop_back();
//        testingValuePosition = mChangedCells.back()->value;
//        // std::cout << mChangedCells.size() << testingValuePosition + 1;
//        mChangedCells.back()->value = 0;
//      }
//      mChangedCells.pop_back();
//      // std::cout << mChangedCells.size() << testingValuePosition + 1;
//      solveBoard(testingValuePosition, CurrentLoop);
//    }
//  }
//  else
//  {
//    // currentCell->coutCoordinates();
//    std::cout << mChangedCells.size() << mChangedCells.back()->value << "end of loop";
//  }
//}

//void Sudoku::generateBoard(Cell * iCell, int iValuePosition,int iCurrentLoop)
//{
//  int CurrentLoop = iCurrentLoop + 1;
//  if (CurrentLoop < 1000)
//  {
//    // Cell * currentCell = iCell;
//    // iCell->coutCoordinates();
//    int testingValuePosition = iValuePosition;
//    // std::cout << testingValuePosition << "=" <<*possibleValues[testingValuePosition]
//    // <<  " safe:"
//    // << safeToPlace(iCell, possibleValues[testingValuePosition])
//    // << boxSafe(currentCell, possibleValues[testingValuePosition])
//    // << columnSafe(currentCell, possibleValues[testingValuePosition])
//    // << rowSafe(currentCell, possibleValues[testingValuePosition])
//    // << " | " << std::endl;
//    if (safeToPlace(iCell, possibleValues[testingValuePosition]))
//    {
//      iCell->value = possibleValues[testingValuePosition];
//      // std::cout << "works" << *currentCell->value << ";";
//      randomizeValues();
//      generateBoard(incrementCell(iCell), 0, CurrentLoop);
//    }
//    else if (testingValuePosition < 8)
//    {
//      // std::cout << "retry" << *possibleValues[testingValuePosition] << ";";
//      testingValuePosition++;
//      generateBoard(incrementCell(iCell), testingValuePosition, CurrentLoop);
//    }
//    else
//    {
//      // std::cout << "error";
//      decrementCell(iCell)->value = 0;
//      testingValuePosition++;
//      generateBoard(decrementCell(iCell), 0, CurrentLoop);
//    }
//  }
//}
