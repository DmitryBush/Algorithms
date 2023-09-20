#pragma once
#include "sparseMatrix.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <iostream>

namespace matUtils
{
    /*
    * Функция заполнения списка случайными числами
    */
    sparseCoordMatrix& RandomFillMatrix(sparseCoordMatrix& matrix, const unsigned int row,
        const unsigned int column)
    {
        srand(time(NULL));
        for (int i = 0; i < (row + column); i++)
        {
            matrix.AddElement((rand() % 10) + 1,
                static_cast<unsigned int>((rand() % row) + 1),
                static_cast<unsigned int>((rand() % column) + 1));
        }
        return matrix;
    }

    /*
    * Функция заполнения списка из файла
    */
    int** FileFillMatrix()
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
                tmpMatrix[i] = new int[columns] {0};
            }


            while (!file.eof())
            {
                register int i = 0, j = 0;
                std::getline(file, tmp);
                i = std::stoi(tmp);
                std::getline(file, tmp);
                j = std::stoi(tmp);

                std::getline(file, tmp);
                tmpMatrix[i][j] = std::stoi(tmp);
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
            tmpMatrix = nullptr;
        }
        return tmpMatrix;
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
}