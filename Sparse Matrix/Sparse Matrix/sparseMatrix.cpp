#include "sparseMatrix.h"

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

sparseMatrix::sparseMatrix(): countElements(0), matrix(nullptr) {}

sparseMatrix::sparseMatrix(int** arr, const int& rows, const int& columns)
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

sparseMatrix::~sparseMatrix()
{
	for (int i = 0; i < countElements; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}
