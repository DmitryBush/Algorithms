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

int** sparseMatrix::AllocateMem(int** arr, const short int& paramOffset)
{
	switch (paramOffset)
	{
	case 0:
		arr = new int* [countElements];

		for (int i = 0; i < countElements; i++)
		{
			arr[i] = new int[3];
		}
		return arr;
		break;
	case 1:
		arr = new int* [countElements + 1];

		for (int i = 0; i < countElements + 1; i++)
		{
			arr[i] = new int[3];
		}
		return arr;
		break;
	case -1:
		arr = new int* [countElements - 1];

		for (int i = 0; i < countElements - 1; i++)
		{
			arr[i] = new int[3];
		}
		return arr;
		break;
	default:
		break;
	}
}

int** sparseMatrix::Swap(int** prevMat, int** newMat, bool compr)
{
	unsigned int k = 0;
	if (compr)
	{
		for (int i = 0; i < countElements; i++)
		{
			newMat[i][0] = prevMat[i][0];
			newMat[i][1] = prevMat[i][1];
			newMat[i][2] = prevMat[i][2];
		}
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

sparseMatrix::sparseMatrix(): countElements(0), matrix(nullptr), columns(0), rows(0) {}

sparseMatrix::sparseMatrix(int** arr, const int& rows, const int& columns): 
	rows(rows), columns(columns)
{
	if (rows > 0 && columns > 0)
	{
		countElements = DefineNonZeroElements(arr, rows, columns);
		matrix = AllocateMem(matrix, 0);

		matrix = Swap(arr, matrix, false);
	}
	else
	{
		countElements = 0;
		matrix = nullptr;
	}
}

void sparseMatrix::AddElement(const int val, const unsigned int row, const unsigned int column)
{
	int** newArr = nullptr;
	newArr = AllocateMem(newArr, 1);
	
	newArr = Swap(matrix, newArr, true);
	newArr[countElements + 1][0] = row;
	newArr[countElements + 1][1] = column;
	newArr[countElements + 1][2] = val;

	Clear(); countElements++;
	if (row > rows) { rows = row; }
	if (column > columns) { columns = column; }
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
	if (matrix)
	{
		for (int i = 0; i < countElements; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;

		matrix = nullptr;
		countElements = 0, rows = 0, columns = 0;
	}
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
