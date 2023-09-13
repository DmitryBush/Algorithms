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

void sparseMatrix::AllocateMem()
{
	matrix = new int*[countElements];

	for (int i = 0; i < countElements; i++)
	{
		matrix[i] = new int[3];
	}
}

int** sparseMatrix::Swap(int** prevMat, int** newMat)
{
	unsigned int k = 0;
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

sparseMatrix::sparseMatrix(): countElements(0), matrix(nullptr), columns(0), rows(0) {}

sparseMatrix::sparseMatrix(int** arr, const int& rows, const int& columns): 
	rows(rows), columns(columns)
{
	if (rows > 0 && columns > 0)
	{
		countElements = DefineNonZeroElements(arr, rows, columns);
		AllocateMem();

		matrix = Swap(arr, matrix);
	}
	else
	{
		countElements = 0;
		matrix = nullptr;
	}
}

int sparseMatrix::GetElement(const unsigned int rows, const unsigned int columns)
{
	for (int i = 0; i < countElements; i++)
		if (rows == matrix[i][0] && columns == matrix[i][1])
			return matrix[i][2];
	return 0;
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
	for (int i = 0; i < countElements; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}
