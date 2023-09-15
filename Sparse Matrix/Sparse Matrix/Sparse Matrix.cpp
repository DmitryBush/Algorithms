#include <iostream>
#include "sparseMatrix.h"
#include <fstream>
#include <string>

sparseMatrix& FileFillList();
void CheckInputValidation(int& inpValue, const char* str);
sparseMatrix& RandomFillList(const unsigned int rows, const unsigned int columns);

int main()
{
    unsigned int count = 18;
    std::cout << count * 2.5 << ' ';
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
	mat[0][0] = 44;
	mat[1][2] = 77;

    sparseMatrix matrix(mat, 3, 3);
	std::cout << matrix.GetElement(0,0) << '\n';
	matrix.Task();
    matrix.AddElement(54, 4, 4);
	matrix.PrintMatrix();
}

/*
* Функция заполнения списка случайными числами
*/
sparseMatrix& RandomFillList(const unsigned int rows, const unsigned int columns)
{
    sparseMatrix matrix;
    srand(time(NULL));
    for (int i = 0; i < 15; i++)
    {
        
    }
    return matrix;
}

/*
* Функция заполнения списка из файла
*/
sparseMatrix& FileFillList()
{
    std::ifstream file;
    std::string tmp;
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    int** tmpMatrix = nullptr; int rows = 0, columns = 0;

    try
    {
        file.open("matrix.txt");

        std::getline(file, tmp);
        rows = std::stoi(tmp);

        tmpMatrix = new int* [rows];
        std::getline(file, tmp);
        columns = std::stoi(tmp);
        for (int i = 0; i < rows; i++)
        {
            tmpMatrix[i] = new int[columns];
        }

        register int i = 0, j = 0;
        while (!file.eof())
        {
            if (j >= columns) { j = 0; i++; }
            else if (i >= rows) { break; }
            std::getline(file, tmp);

            tmpMatrix[i][j] = std::stoi(tmp);
            j++;
        }
        file.close();
    }
    catch (const std::exception& ex)
    {
        std::cout << "An error has occuried" << '\n' << ex.what() << '\n';
        if (tmpMatrix)
        {
            for (int i = 0; i < rows; i++)
            {
                delete[] tmpMatrix[i];
            }
            delete[] tmpMatrix;
        }
    }
    sparseMatrix matrix(tmpMatrix, rows, columns);
    return matrix;
}

void CheckInputValidation(int& inpValue, const char* str)
{
    while (std::cin.fail())
    {
        system("cls");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "An error has occuried" << '\n' << "Try entering again " << str << '\n';
        std::cin >> inpValue;
    }
}