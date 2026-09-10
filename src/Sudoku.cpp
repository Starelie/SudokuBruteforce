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
  // randomizeValues();
  // generateBoard(mCells[0][0], 0, 0);
  coutBoard();
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
  for (int i = 1; i <= 9; i++)
  {
    possibleValues[i - 1] = i;
  }
  solveBoard(0, 0);
  coutBoard();
}

Sudoku::~Sudoku() {}

void Sudoku::coutBoard()
{
  for (int row = 0; row < 9; row++)
  {
    if (row % 3 == 0)
    {
      std::cout << std::endl;
      for (int i = 0; i < 31; i++)
      {
        std::cout << "-";
      }
    }
    std::cout << std::endl;
    for (int column = 0; column < 9; column++)
    {
      if (column % 3 == 0)
      {
        std::cout << "|";
      }
      std::cout << mCells[row][column]->value;
    } 
    std::cout << "|";
  }
  std::cout << std::endl;
  for (int i = 0; i < 31; i++)
  {
    std::cout << "-";
  }
}

void Sudoku::randomizeValues()
{
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(std::begin(possibleValues), std::end(possibleValues), g);
}

Sudoku::Cell* Sudoku::getFistEmptyCell()
{
  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      if (mCells[row][column]->value == 0)
      {
        // mCells[row][column]->coutCoordinates();
        return mCells[row][column];
      }
    }
  }
  Cell* emptyCell = new Cell{0, 0, 0};
  return emptyCell;
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

bool Sudoku::boxSafe(Cell* iCell, int iValue)
{
  int BoxStartX = iCell->row - iCell->row % 3;
  int BoxStartY = iCell->column - iCell->column % 3;
  for (int row = 0; row < 3; row++)
  {
    for (int column = 0; column < 3; column++)
    {
      if (iValue == mCells[BoxStartX + row][BoxStartY + column]->value &&
          iValue != 0)
      {
        return false;
      }
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

void Sudoku::solveBoard(int iValuePosition,int iCurrentLoop)
{
  Cell* currentCell = getFistEmptyCell();
  int testingValuePosition = iValuePosition;
  int CurrentLoop = iCurrentLoop + 1;
  // std::cout <<mChangedCells.size();
  // std::cout << testingValuePosition << "=" <<*possibleValues[testingValuePosition]
  // <<  " safe:"
  // << safeToPlace(currentCell, possibleValues[testingValuePosition])
  // << boxSafe(currentCell, possibleValues[testingValuePosition])
  // << columnSafe(currentCell, possibleValues[testingValuePosition])
  // << rowSafe(currentCell, possibleValues[testingValuePosition])
  // << " | " ;
  if (CurrentLoop <= 100)
  // if (CurrentLoop <= 25893)
  // if (CurrentLoop < 100)
  {
    if (CurrentLoop > 25880)
    {
      // coutBoard();
      // currentCell->coutCoordinates();
      // std::cout << " value : " << *currentCell->value << " tested value : " << *possibleValues[testingValuePosition] << " vector size : " << mChangedCells.size();
    }
    if (CurrentLoop > 25880)
    {
      std::cout << "hi";
    }
    mChangedCells.emplace_back(currentCell);
    if (safeToPlace(mChangedCells.back(), possibleValues[testingValuePosition]))
    {
      currentCell->value = possibleValues[testingValuePosition];
      // currentCell->coutCoordinates();
      // std::cout << *currentCell->value << "works" << ";" << std::endl;
      solveBoard(0, CurrentLoop);
    }
    else if (possibleValues[testingValuePosition] < 9)
    {
      // currentCell->coutCoordinates();
      // std::cout << *possibleValues[testingValuePosition] << "retry" << ";" << std::endl;
      delete mChangedCells.back();
      mChangedCells.pop_back();
      testingValuePosition++;
      solveBoard(testingValuePosition, CurrentLoop);
    }
    else
    {
      delete mChangedCells.back();
      mChangedCells.pop_back();
      testingValuePosition = mChangedCells.back()->value;
      mChangedCells.back()->value = 0;
      // currentCell->coutCoordinates();
      // std::cout << "error" << *mChangedCells.back()->value << ";" << std::endl;
      // coutBoard();
      // std::cout << "redo";
      while (testingValuePosition == 9)
      {
        // coutBoard();
        delete mChangedCells.back();
        mChangedCells.pop_back();
        testingValuePosition = mChangedCells.back()->value;
        // std::cout << mChangedCells.size() << testingValuePosition + 1;
        mChangedCells.back()->value = 0;
      }
      mChangedCells.pop_back();
      // std::cout << mChangedCells.size() << testingValuePosition + 1;
      solveBoard(testingValuePosition, CurrentLoop);
    }
  }
  else
  {
    // currentCell->coutCoordinates();
    std::cout << mChangedCells.size() << mChangedCells.back()->value << "end of loop";
  }
}

void Sudoku::generateBoard(Cell * iCell, int iValuePosition,int iCurrentLoop)
{
  int CurrentLoop = iCurrentLoop + 1;
  if (CurrentLoop < 1000)
  {
    // Cell * currentCell = iCell;
    // iCell->coutCoordinates();
    int testingValuePosition = iValuePosition;
    // std::cout << testingValuePosition << "=" <<*possibleValues[testingValuePosition]
    // <<  " safe:"
    // << safeToPlace(iCell, possibleValues[testingValuePosition])
    // << boxSafe(currentCell, possibleValues[testingValuePosition])
    // << columnSafe(currentCell, possibleValues[testingValuePosition])
    // << rowSafe(currentCell, possibleValues[testingValuePosition])
    // << " | " << std::endl;
    if (safeToPlace(iCell, possibleValues[testingValuePosition]))
    {
      iCell->value = possibleValues[testingValuePosition];
      // std::cout << "works" << *currentCell->value << ";";
      randomizeValues();
      generateBoard(incrementCell(iCell), 0, CurrentLoop);
    }
    else if (testingValuePosition < 8)
    {
      // std::cout << "retry" << *possibleValues[testingValuePosition] << ";";
      testingValuePosition++;
      generateBoard(incrementCell(iCell), testingValuePosition, CurrentLoop);
    }
    else
    {
      // std::cout << "error";
      decrementCell(iCell)->value = 0;
      testingValuePosition++;
      generateBoard(decrementCell(iCell), 0, CurrentLoop);
    }
  }
}