#include <iostream>
#include "sparseMatrix.h"

int main()
{
    int** mat = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		mat[i] = new int[5];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
			mat[i][j] = 0;
	}
	mat[3][3] = 5;

    sparseMatrix matrix(mat, 4, 5);
	std::cout << matrix.GetElement(3,3) << '\n';
}
