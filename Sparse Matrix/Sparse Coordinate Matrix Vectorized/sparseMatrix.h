#pragma once


class sparse_coordinate_matrix_vectorized
{
private:
	unsigned int columns;
	unsigned int rows;
	unsigned int countElements;

	int** matrix;
	unsigned int capacity;

	unsigned int DefineNonZeroElements(int** arr, const int& rows, const int& columns);
	int** AllocateMem(int** arr, const unsigned int offset);
	int** Swap(int** prevMat, int** newMat, bool compr);
	void CleanUpArray();
	void GarbageCollector();
public:
	sparse_coordinate_matrix_vectorized();
	sparse_coordinate_matrix_vectorized(int** arr, const int& rows, const int& columns);

	void AddElement(const int val, const unsigned int row, const unsigned int column);
	void DeleteElement(const unsigned int row, const unsigned int column);
	int GetElement(const unsigned int rows, const unsigned int columns);

	void Clear();

	void PrintMatrix();

	void Task();

	~sparse_coordinate_matrix_vectorized();
};