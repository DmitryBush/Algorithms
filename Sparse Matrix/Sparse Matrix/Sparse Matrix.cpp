﻿#include <iostream>
#include "sparseMatrix.h"

int main()
{
    int** mat = new int*[3];
	for (int i = 0; i < 3; i++)
	{
		mat[i] = new int[3];
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			mat[i][j] = 0;
	}
	mat[2][2] = 5;

    sparseMatrix matrix(mat, 3, 3);
	std::cout << matrix.GetElement(3,3) << '\n';
	matrix.PrintMatrix();
}