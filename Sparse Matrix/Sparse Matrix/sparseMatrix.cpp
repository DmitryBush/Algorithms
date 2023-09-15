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
		arr[i] = new int[3]{-1};
	}
	return arr;
}

int** sparseMatrix::Swap(int** prevMat, int** newMat, bool compr)
{
	unsigned int k = 0;
	if (compr)
	{
		for (int i = 0; i < countElements; i++)
		{
			if (prevMat[i][0] != -1)
			{
				newMat[i][0] = prevMat[i][0];
				newMat[i][1] = prevMat[i][1];
				newMat[i][2] = prevMat[i][2];
			}
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

void sparseMatrix::CleanUpArray()
{
	if (matrix)
	{
		for (int i = 0; i < capacity; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;

		matrix = nullptr;
	}
}

void sparseMatrix::GarbageCollector()
{
	int** newArr = nullptr;
	capacity = static_cast<unsigned int>(capacity / 1.25);
	newArr = AllocateMem(newArr, countElements);

	newArr = Swap(matrix, newArr, true);

	CleanUpArray();

	matrix = newArr;
}

sparseMatrix::sparseMatrix(): countElements(0), matrix(nullptr), capacity(0),
	columns(0), rows(0) {}

sparseMatrix::sparseMatrix(int** arr, const int& rows, const int& columns): 
	rows(rows), columns(columns)
{
	if (rows > 0 && columns > 0)
	{
		countElements = DefineNonZeroElements(arr, rows, columns);
		capacity = countElements * 2;
		matrix = AllocateMem(matrix, countElements);

		matrix = Swap(arr, matrix, false);
	}
	else
	{
		countElements = 0;
		capacity = 0;
		matrix = nullptr;
	}
}

void sparseMatrix::AddElement(const int val, const unsigned int row, const unsigned int column)
{
	if (capacity > countElements)
	{
		for (int i = 0; i < capacity; i++)
		{
			if (matrix[i][0] == -1)
			{
				matrix[countElements][0] = row - 1;
				matrix[countElements][1] = column - 1;
				matrix[countElements][2] = val;

				countElements++;
				if (row > rows) { rows = row; }
				if (column > columns) { columns = column; }
				return;
			}
		}
		throw("Memory leaking");
	}
	else
	{
		int** newArr = nullptr;
		capacity = (countElements + 1) * 2;
		newArr = AllocateMem(newArr, countElements + 1);

		newArr = Swap(matrix, newArr, true);
		newArr[countElements][0] = row - 1;
		newArr[countElements][1] = column - 1;
		newArr[countElements][2] = val;

		CleanUpArray(); countElements++;
		if (row > rows) { rows = row; }
		if (column > columns) { columns = column; }
		matrix = newArr;
	}
}

void sparseMatrix::DeleteElement(const unsigned int row, const unsigned int column)
{
	if (countElements * 2.5 < capacity)
		GarbageCollector();

	for (int i = 0; i < capacity; i++)
	{
		if (row == matrix[i][0] && column == matrix[i][1])
		{
			matrix[i][0] = -1;
			countElements--;
			break;
		}	
	}
}

int sparseMatrix::GetElement(const unsigned int rows, const unsigned int columns)
{
	for (int i = 0; i < capacity; i++)
		if(matrix[i][0] != -1)
			if (rows == matrix[i][0] && columns == matrix[i][1])
				return matrix[i][2];
	return 0;
}

void sparseMatrix::Clear()
{
	CleanUpArray();
	countElements = 0, rows = 0, columns = 0, capacity = 0;
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
	for (int i = 0; i < capacity; i++)
	{
		if (matrix[i][0] != -1)
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
}

sparseMatrix::~sparseMatrix()
{
	Clear();
}
