#pragma once


class sparseCoordMatrix
{
private:
	unsigned int columns;
	unsigned int rows;
	unsigned int countElements;

	int** matrix;

	unsigned int DefineNonZeroElements(int** arr, const int& rows, const int& columns);
	int** AllocateMem(int** arr, const unsigned int offset);
	int** Swap(int** prevMat, int** newMat, bool compr);
	void CleanUpArray();
	int* GetElement(const unsigned int& rows, const unsigned int& columns,
		const bool& DEV_MODE);
public:
	sparseCoordMatrix();
	sparseCoordMatrix(int** arr, const int& rows, const int& columns);

	void AddElement(const int& val, const unsigned int& row, const unsigned int& column);
	void DeleteElement(const unsigned int& row, const unsigned int& column);
	int GetElement(const unsigned int& rows, const unsigned int& columns);

	void ImportMatrix(int** arr, const int& rows, const int& columns);
	void Clear();

	int* At(const unsigned int& row, const unsigned int& column);
	void PrintMatrix();
	void Task();

	~sparseCoordMatrix();
};