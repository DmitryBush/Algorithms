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

int** sparseMatrix::Swap(int** prevMat, int** newMat, const int rows, const int columns)
{
	unsigned int k = 0;
	if (rows == 0 || columns == 0)
	{
		for (int i = 0; i < countElements; i++)
			for (int j = 0; j < 3; j++)
				if (prevMat[i][j] != 0)
				{
					newMat[k][0] = i;
					newMat[k][1] = j;
					newMat[k][2] = prevMat[i][j];
				}
	}
	else
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				if (prevMat[i][j] != 0)
				{
					newMat[k][0] = i;
					newMat[k][1] = j;
					newMat[k][2] = prevMat[i][j];
				}
	}
	return newMat;
}

int* sparseMatrix::GetElement(const unsigned int rows, const unsigned int columns, 
	const unsigned int id)
{
	for (int i = 0; i < countElements; i++)
		if (rows == matrix[i][0] && columns == matrix[i][1])
			switch (id)
			{
			case 0:
				return &matrix[i][0];
				break;
			case 1:
				return &matrix[i][1];
				break;
			case 2:
				return &matrix[i][2];
				break;
			default:
				return nullptr;
				break;
			}
	return nullptr;
}

sparseMatrix::sparseMatrix(): countElements(0), matrix(nullptr), columns(0), rows(0) {}

sparseMatrix::sparseMatrix(int** arr, const int& rows, const int& columns): 
	rows(rows), columns(columns)
{
	if (rows > 0 && columns > 0)
	{
		countElements = DefineNonZeroElements(arr, rows, columns);
		AllocateMem();

		matrix = Swap(arr, matrix, rows, columns);
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
	bool rowTransfer = false;
	int* tmpBuffer = new int[columns];

	for (size_t i = 0; i < columns; i++)
		tmpBuffer[i] = 0;

	for (int i = 0; i < rows; i++)
	{
		for (size_t i = 0; i < columns - 1; i++)
			tmpBuffer[i] = 0;

		if (!tmpBuffer[columns - 1])
			rowTransfer = true;

		for (int j = 1; j < columns; j++)
		{
			if (rowTransfer)
			{
				tmpBuffer[j] = GetElement(i, j);

				*GetElement(i - 1, columns - 1, 0) += 1;
				*GetElement(i - 1, columns - 1, 1) = 0;

				*GetElement(i, j - 1, 1) += 1;

				rowTransfer = false;
				tmpBuffer[columns - 1] = 0;
			}
			else if (GetElement(i, j - 1) != tmpBuffer[j - 1])
			{
				tmpBuffer[j] = GetElement(i, j);

				*GetElement(i, j - 1, 1) += 1;
			}
		}
	}
}

sparseMatrix::~sparseMatrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}
