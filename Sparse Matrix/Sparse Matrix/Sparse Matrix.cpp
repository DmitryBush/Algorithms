#include <iostream>
#include "sparseMatrix.h"
#include <fstream>
#include <string>
#include <conio.h>

sparseMatrix& FileFillMatrix();
void CheckInputValidation(int& inpValue, const char* str);
sparseMatrix& RandomFillMatrix(sparseMatrix& matrix, const unsigned int row,
    const unsigned int column);

int main()
{
    bool running = true; sparseMatrix matrix;
    while (running)
    {
        int elem[3]{0};
        matrix.PrintMatrix();
        std::cout << "Operations:" << '\n'
            << "1) Add Element" << '\n'
            << "2) Delete Element" << '\n'
            << "3) Edit Element" << '\n'
            << "4) Clear matrix" << '\n'
            << "5) Fill matrix random numbers" << '\n'
            << "6) Fill matrix from file" << '\n'
            << "7) Run Task" << '\n'
            << "0) Close" << '\n';
        switch (_getch())
        {
        case '1':
            std::cout << "Enter row" << '\n';
            std::cin >> elem[0];
            CheckInputValidation(elem[0], "value");

            std::cout << "Enter column" << '\n';
            std::cin >> elem[1];
            CheckInputValidation(elem[1], "value");

            std::cout << "Enter value" << '\n';
            std::cin >> elem[2];
            CheckInputValidation(elem[2], "value");
            matrix.AddElement(elem[2], elem[0], elem[1]);

            system("cls");
            break;
        case '2':
            std::cout << "Enter element to delete" << '\n';
            std::cout << "Enter row" << '\n';
            std::cin >> elem[0];
            CheckInputValidation(elem[0], "value");

            std::cout << "Enter column" << '\n';
            std::cin >> elem[1];
            CheckInputValidation(elem[1], "value");
            matrix.DeleteElement(elem[0], elem[1]);

            system("cls");
            break;
        case '3':
            system("cls");
            
            break;
        case '4':
            system("cls");
            matrix.Clear();

            break;
        case '5':
            system("cls");
            std::cout << "Enter row" << '\n';
            std::cin >> elem[0];
            CheckInputValidation(elem[0], "value");

            std::cout << "Enter column" << '\n';
            std::cin >> elem[1];
            CheckInputValidation(elem[1], "value");

            RandomFillMatrix(matrix, elem[0], elem[1]);

            break;
        case '6':
            system("cls");
            FileFillMatrix();

            break;
        case '7':
            system("cls");
            matrix.Task();

            break;
        case '0':
            running = false;
            break;
        default:
            system("cls");
            std::cout << "An error has occuried" << '\n';
            break;
        }
    }
    return 0;
}

/*
* Функция заполнения списка случайными числами
*/
sparseMatrix& RandomFillMatrix(sparseMatrix& matrix,const unsigned int row, 
    const unsigned int column)
{
    srand(time(NULL));
    for (int i = 0; i < (row + column) ; i++)
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
sparseMatrix& FileFillMatrix()
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