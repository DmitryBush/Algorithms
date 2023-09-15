#pragma once
#include <iostream>
#include "List.h"
#include <fstream>
#include <string>
#include <conio.h>

namespace listUtils
{
    /*
    * Функция заполнения списка случайными числами
    */
    void RandomFillList(list& list)
    {
        list.Clear();
        srand(time(NULL));
        for (int i = 0; i < 15; i++)
        {
            list.PushForward(rand() % 20);
        }
    }

    /*
    * Функция заполнения списка из файла
    */
    void FileFillList(list& list)
    {
        std::ifstream file;
        std::string tmp;
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        try
        {
            list.Clear();
            file.open("list.txt");

            while (!file.eof())
            {
                std::getline(file, tmp);
                list.PushForward(std::stoi(tmp));
            }
            file.close();
        }
        catch (const std::exception& ex)
        {
            std::cout << "An error has occuried" << '\n' << ex.what() << '\n';
            list.Clear();
        }
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