#include "sparseMatrix.h"
#include <iostream>

unsigned int sparseMatrix::DefineNonZeroElements(int** arr, 
	const int& rows, const int& columns)
{
	unsigned int count = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (arr[i][j] != 0)
				count++;
	return count;
}

int** sparseMatrix::AllocateMem(int** arr, const unsigned int offset)
{
	arr = new int* [countElements + offset];

	for (int i = 0; i < countElements + offset; i++)
	{
		arr[i] = new int[3];
	}
	return arr;
}

int** sparseMatrix::Swap(int** prevMat, int** newMat, bool compr)
{
	unsigned int k = 0;
	if (compr)
	{
		int maxRow = 0, maxColumn = 0;
		for (int i = 0; i < countElements; i++)
		{
			if (prevMat[i][0] != -1)
			{
				newMat[i][0] = prevMat[i][0];
				newMat[i][1] = prevMat[i][1];
				newMat[i][2] = prevMat[i][2];

				if (maxRow < prevMat[i][0])
					maxRow = prevMat[i][0];
				if (maxColumn < prevMat[i][1])
					maxColumn = prevMat[i][1];
			}
		}
		if (maxRow != rows)
			rows = maxRow + 1;
		if (maxColumn != columns)
			columns = maxColumn + 1;
		return newMat;
	}
	else
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				if (prevMat[i][j])
				{
					newMat[k][0] = i;
					newMat[k][1] = j;
					newMat[k][2] = prevMat[i][j];
					k++;
				}
		return newMat;
	}
}

void sparseMatrix::CleanUpArray()
{
	if (matrix)
	{
		for (int i = 0; i < countElements; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;

		matrix = nullptr;
	}
}

bool sparseMatrix::FindElement(const unsigned int row, const unsigned int column)
{
	for (int i = 0; i < countElements; i++)
		if (row == matrix[i][0] && column == matrix[i][1])
			return true;
	return false;
}

int* sparseMatrix::GetElement(const unsigned int row, const unsigned int column,
	const bool DEV_MODE)
{
	for (int i = 0; i < countElements; i++)
		if (row == matrix[i][0] && column == matrix[i][1])
			return matrix[i];
	return nullptr;
}

sparseMatrix::sparseMatrix(): countElements(0), matrix(nullptr), columns(0), rows(0) {}

sparseMatrix::sparseMatrix(int** arr, const int& rows, const int& columns): 
	rows(rows), columns(columns)
{
	if (rows > 0 && columns > 0)
	{
		countElements = DefineNonZeroElements(arr, rows, columns);
		matrix = AllocateMem(matrix, countElements);

		matrix = Swap(arr, matrix, false);
	}
	else
	{
		countElements = 0;
		matrix = nullptr;
	}
}

void sparseMatrix::AddElement(const int val, 
	const unsigned int row, const unsigned int column)
{
	auto ptr = GetElement(row - 1, column - 1, true);
	if (row < 0 || column < 0)
		throw("Invalid index");
	else if (val == 0)
	{
		if (row > rows) { rows = row; }
		if (column > columns) { columns = column; }
		return;
	}
	else if (ptr != nullptr)
	{
		*(ptr + 2) = val;
	}
	else
	{
		int** newArr = nullptr;
		newArr = AllocateMem(newArr, countElements + 1);

		newArr = Swap(matrix, newArr, true);
		newArr[countElements][0] = row - 1;
		newArr[countElements][1] = column - 1;
		newArr[countElements][2] = val;

		CleanUpArray(); countElements++;
		matrix = newArr;
		if (row > rows) { rows = row; }
		if (column > columns) { columns = column; }
	}
}

void sparseMatrix::DeleteElement(const unsigned int row, const unsigned int column)
{
	for (int i = 0; i < countElements; i++)
	{
		if (row == matrix[i][0] && column == matrix[i][1])
		{
			matrix[i][0] = -1;
			int** newArr = nullptr;

			newArr = AllocateMem(newArr, countElements - 1);
			newArr = Swap(matrix, newArr, true);
			CleanUpArray(); countElements--;
			matrix = newArr;
			break;
		}	
	}
}

int sparseMatrix::GetElement(const unsigned int rows, const unsigned int columns)
{
	for (int i = 0; i < countElements; i++)
		if (rows == matrix[i][0] && columns == matrix[i][1])
			return matrix[i][2];
	return 0;
}

void sparseMatrix::Clear()
{
	CleanUpArray();
	countElements = 0, rows = 0, columns = 0;
}

void sparseMatrix::PrintMatrix()
{
	if(matrix == nullptr)
		std::cout << "There's no matrix to show" << '\n';
	else
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
				std::cout << GetElement(i, j) << ' ';
			std::cout << '\n';
		}
		std::cout << '\n';
		for (size_t i = 0; i < countElements; i++)
		{
			std::cout << matrix[i][0] << ' ' << matrix[i][1] << ' ' << matrix[i][2] << '\n';
		}
	}
}

void sparseMatrix::Task()
{
	for (int i = 0; i < countElements; i++)
	{
		if (matrix[i][1] + 1 > columns - 1 && matrix[i][0] + 1 > rows - 1)
		{
			matrix[i][0] = 0;
			matrix[i][1] = 0;
		}
		else if (matrix[i][1] + 1 > columns - 1)
		{
			matrix[i][0]++;
			matrix[i][1] = 0;
		}
		else
			matrix[i][1]++;
	}
}

sparseMatrix::~sparseMatrix()
{
	Clear();
}
