#include "Cell.h"

Cell::Cell() {mValue = 0; mRow = 0; mColumn = 0;}

Cell::Cell(int * iValue, int iRow, int iColumn)
{
  if (iValue != nullptr)
  {
    mValue = iValue;
  }
  else
  {
    mValue = new int{0};
  }
  mRow = iRow;
  mColumn = iColumn;
}

Cell::~Cell()
{
  delete mValue;
}

void Cell::setValue(int * iValue)
{
  mValue = iValue;
}

void Cell::resetValue()
{
  mValue = new int{0};
}

int* Cell::getValue()
{
  return mValue;
}

void Cell::coutCellValue()
{
  std::cout << " " << *mValue << " ";
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