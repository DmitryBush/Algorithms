#include <iostream>
#include "sparseMatrix.h"
#include "MatrixUtils.h"

int main()
{
    bool running = true; sparseCoordMatrix matrix;
    while (running)
    {
        int elem[3]{ 0 }; int** tmpMat = nullptr;
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
            matUtils::CheckInputValidation(elem[0], "value");

            std::cout << "Enter column" << '\n';
            std::cin >> elem[1];
            matUtils::CheckInputValidation(elem[1], "value");

            std::cout << "Enter value" << '\n';
            std::cin >> elem[2];
            matUtils::CheckInputValidation(elem[2], "value");
            matrix.AddElement(elem[2], elem[0], elem[1]);

            system("cls");
            break;
        case '2':
            std::cout << "Enter element to delete" << '\n';
            std::cout << "Enter row" << '\n';
            std::cin >> elem[0];
            matUtils::CheckInputValidation(elem[0], "value");

            std::cout << "Enter column" << '\n';
            std::cin >> elem[1];
            matUtils::CheckInputValidation(elem[1], "value");
            matrix.DeleteElement(elem[0], elem[1]);

            system("cls");
            break;
        case '3':
            system("cls");
            std::cout << "Enter row" << '\n';
            std::cin >> elem[0];
            matUtils::CheckInputValidation(elem[0], "value");

            std::cout << "Enter column" << '\n';
            std::cin >> elem[1];
            matUtils::CheckInputValidation(elem[1], "value");

            std::cout << "Enter value" << '\n';
            std::cin >> elem[2];
            matUtils::CheckInputValidation(elem[2], "value");
            if (auto ptr = matrix.At(elem[0], elem[1]))
                *ptr = elem[2];
            else
                matrix.AddElement(elem[2], elem[0], elem[1]);

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
            matUtils::CheckInputValidation(elem[0], "value");

            std::cout << "Enter column" << '\n';
            std::cin >> elem[1];
            matUtils::CheckInputValidation(elem[1], "value");

            matUtils::RandomFillMatrix(matrix, elem[0], elem[1]);

            break;
        case '6':
            system("cls");
            tmpMat = matUtils::FileFillMatrix();
            matrix.ImportMatrix(tmpMat, 8, 8);

            for (int i = 0; i < 8; i++)
            {
                delete[] tmpMat[i];
            }
            delete[] tmpMat;
            tmpMat = nullptr;
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
