#pragma once


class sparseMatrix
{
private:
	unsigned int countElements;

	int** matrix;

	unsigned int DefineNonZeroElements(int** arr, const int& rows, const int& columns);
	void AllocateMem();
	int** Swap(int** prevMat, int** newMat, const int rows = 0, const int columns = 0);
public:
	sparseMatrix();
	sparseMatrix(int** arr, const int& rows, const int& columns);

	int GetElement(const unsigned int rows, const unsigned int columns);

	~sparseMatrix();
};