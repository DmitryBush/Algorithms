#pragma once


class sparseMatrix
{
private:
	unsigned int columns;
	unsigned int rows;
	unsigned int countElements;

	int** matrix;

	unsigned int DefineNonZeroElements(int** arr, const int& rows, const int& columns);
	void AllocateMem();
	int** Swap(int** prevMat, int** newMat, const int rows = 0, const int columns = 0);
	int* GetElement(const unsigned int rows, const unsigned int columns, const unsigned int id);
public:
	sparseMatrix();
	sparseMatrix(int** arr, const int& rows, const int& columns);

	int GetElement(const unsigned int rows, const unsigned int columns);
	void PrintMatrix();

	void Task();

	~sparseMatrix();
};