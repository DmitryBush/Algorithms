#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

namespace dictUtils
{
    /*
    * 
    */
    void FileFillList(dict& dictionary)
    {
        std::ifstream file;
        std::string tmp, key;
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        try
        {
            dictionary.Clear();
            file.open("list.txt");

            while (!file.eof())
            {
                std::getline(file, tmp);
                std::getline(file, key);
                dictionary.PushForward(tmp.c_str(), key.c_str());
            }
            file.close();
        }
        catch (const std::exception& ex)
        {
            std::cout << "An error has occuried" << '\n' << ex.what() << '\n';
            dictionary.Clear();
        }
    }

    void CheckInputValidation(std::string& inpValue, const char* str)
    {
        while (std::cin.fail() || inpValue.empty())
        {
            system("cls");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "An error has occuried" << '\n' 
                << "Try entering again " << str << '\n';
            std::cin >> inpValue;
        }
    }
}