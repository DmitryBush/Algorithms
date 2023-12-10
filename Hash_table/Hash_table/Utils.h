#pragma once
#include "Hash_table.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <iostream>

namespace treeUtils
{
    /*
    * Функция заполнения n-дерева из файла
    */
    void FileFillMatrix(hashTable& table)
    {
        std::ifstream file;
        std::string surname, name, fatherName;
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        try
        {
            table.Clear();
            file.open("table.txt");

            while (!file.eof())
            {
                std::getline(file, surname);
                std::getline(file, name);
                std::getline(file, fatherName);
                table.Push(surname, name, fatherName);
            }
            file.close();
        }
        catch (const std::exception& ex)
        {
            std::cout << "An error has occuried" << '\n' << ex.what() << '\n';
            table.Clear();
        }
    }

    /*
    * Функция проверки корректности ввода
    */
    void CheckInputValidation(std::string& inpValue, const char* str)
    {
        while (std::cin.fail() || inpValue.empty())
        {
            system("cls");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "An error has occuried" << '\n' << "Try entering again " << str << '\n';
            std::cin >> inpValue;
        }
    }
}