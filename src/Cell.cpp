#include "Cell.h"

Cell::Cell() {mValue = 0; mRow = 0; mColumn = 0;}

Cell::Cell(int iValue, int iRow, int iColumn)
{
  mValue = iValue;
  mRow = iRow;
  mColumn = iColumn;
}

void Cell::setValue(int iValue)
{
  mValue = iValue;
}

void Cell::resetValue()
{
  mValue = 0;
}

int Cell::getValue()
{
  return mValue;
}

void Cell::coutCellValue()
{
  std::cout << " " << mValue << " ";
}

int Cell::getRow()
{
  return mRow;
}

int Cell::getColumn()
{
  return mColumn;
}

void Cell::coutCoordinates()
{
  std::cout << mRow << ":" << mColumn << "=>";
}