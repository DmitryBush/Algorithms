#pragma once


class sparseMatrix
{
private:
	unsigned int columns;
	unsigned int rows;
	unsigned int countElements;

	int** matrix;

	unsigned int DefineNonZeroElements(int** arr, const int& rows, const int& columns);
	int** AllocateMem(int** arr, const short int& paramOffset);
	int** Swap(int** prevMat, int** newMat, bool compr);
public:
	sparseMatrix();
	sparseMatrix(int** arr, const int& rows, const int& columns);

	void AddElement(const int val, const unsigned int row, const unsigned int column);
	int GetElement(const unsigned int rows, const unsigned int columns);

	void Clear();

	void PrintMatrix();

	void Task();

	~sparseMatrix();
};