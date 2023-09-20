#include "sparseMatrix.h"
#include <iostream>

/*
* Метод определяющий количество элементов для массива
*/
unsigned int sparseCoordMatrix::DefineNonZeroElements(int** arr, 
	const int& rows, const int& columns)
{
	unsigned int count = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (arr[i][j] != 0)
				count++;
	return count;
}

/*
* Метод для выделения памяти массивов
*/
int** sparseCoordMatrix::AllocateMem(int** arr, const unsigned int offset)
{
	arr = new int* [countElements + offset];

	for (int i = 0; i < countElements + offset; i++)
	{
		arr[i] = new int[3];
	}
	return arr;
}

/*
* Метод копирования двух массивов
* bool compr - Используется ли координатный тип хранения
*/
int** sparseCoordMatrix::Swap(int** prevMat, int** newMat, bool compr)
{
	unsigned int k = 0;
	if (compr)
	{
		int maxRow = 0, maxColumn = 0;
		for (int i = 0; i < countElements; i++)
		{
			if (prevMat[i][0] != -1) // значение -1 появляется при удалении элемента
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

/*
* Метод для очищения памяти в массиве
*/
void sparseCoordMatrix::CleanUpArray()
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

/*
* Метод для получения указателя на элемент
*/
int* sparseCoordMatrix::GetElement(const unsigned int& row, const unsigned int& column,
	const bool& DEV_MODE)
{
	for (int i = 0; i < countElements; i++)
		if (row == matrix[i][0] && column == matrix[i][1])
			return matrix[i];
	return nullptr;
}

/*
* Конструктор без параметров
*/
sparseCoordMatrix::sparseCoordMatrix(): countElements(0), matrix(nullptr), columns(0), rows(0) {}

/*
* Конструктор с параметрами
*/
sparseCoordMatrix::sparseCoordMatrix(int** arr, const int& rows, const int& columns): 
	rows(rows), columns(columns)
{
	if (rows > 0 && columns > 0 && arr != nullptr)
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

/*
* Метод для добавления элементов в матрицу
*/
void sparseCoordMatrix::AddElement(const int& val, 
	const unsigned int& row, const unsigned int& column)
{
	auto ptr = GetElement(row - 1, column - 1, true);
	if (row < 0 || column < 0)
		throw("Invalid index");
	else if (val == 0) // При нулевом значении нет необходимости добавлять элемент
	{
		if (row > rows) { rows = row; }
		if (column > columns) { columns = column; }
		return;
	}
	else if (ptr != nullptr) // Если элемент существует, то перезаписать
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

/*
* Метод для удаления элемента
*/
void sparseCoordMatrix::DeleteElement(const unsigned int& row, const unsigned int& column)
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

/*
* Метод для удаления элемента
*/
int sparseCoordMatrix::GetElement(const unsigned int& rows, const unsigned int& columns)
{
	for (int i = 0; i < countElements; i++)
		if (rows == matrix[i][0] && columns == matrix[i][1])
			return matrix[i][2];
	return 0;
}

/*
* Метод для импорта матрицы 
*/
void sparseCoordMatrix::ImportMatrix(int** arr, const int& rows, const int& columns)
{
	if (matrix != nullptr)
		Clear();
	if (rows > 0 && columns > 0 && arr != nullptr)
	{
		this->rows = rows; this->columns = columns;
		countElements = DefineNonZeroElements(arr, rows, columns);
		matrix = AllocateMem(matrix, countElements);

		matrix = Swap(arr, matrix, false);
	}
	else
	{
		throw("Matrix are empty");
	}
}

/*
* Метод для очищения матрицы
*/
void sparseCoordMatrix::Clear()
{
	CleanUpArray();
	countElements = 0, rows = 0, columns = 0;
}

/*
* Метод доступа к элементу
*/
int* sparseCoordMatrix::At(const unsigned int& row, const unsigned int& column)
{
	if (row <= 0 || column <= 0 
		|| row > rows || column > columns)
		throw("Invalid index");
	else if (matrix == nullptr)
		throw("Matrix is empty");

	if (int* elem = GetElement(row - 1, column - 1, true))
		return elem + 2;
	else
		return nullptr;
}

/*
* Метод для отображения матрицы
*/
void sparseCoordMatrix::PrintMatrix()
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
	}
}

/*
* Задача 4. Дана разреженная матрица (CS). Осуществить циклический сдвиг в матрице. 
* Сдвинуть всю матрицу. В первой строке первый элемент переносится на второе место, 
* второй элемент на третье и т.д. 
* Последний элемент в первой строке становиться первым элементом во второй строке. 
* Последний элемент в последней строке переноситься на первую строку на первое место.
*/
void sparseCoordMatrix::Task()
{
	PrintMatrix(); std::cout << '\n' <<  '\n';
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

/*
* Деструктор
*/
sparseCoordMatrix::~sparseCoordMatrix()
{
	Clear();
}
