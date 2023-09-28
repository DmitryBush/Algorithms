#pragma once
#include "BinaryTree.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <iostream>

namespace treeUtils
{
    /*
    * Ôóíêöèÿ çàïîëíåíèÿ ìàòðèöû ñëó÷àéíûìè ÷èñëàìè
    */
    BinaryTree& RandomFillMatrix(BinaryTree& tree)
    {
        tree.Clear();
        srand(time(NULL));
        for (unsigned int i = 0; i < 15; i++)
        {
            tree.Insert((rand() % 100) + 1);
        }
        return tree;
    }

    /*
    * Ôóíêöèÿ çàïîëíåíèÿ ìàòðèöû èç ôàéëà
    */
    void FileFillMatrix(BinaryTree& tree)
    {
        std::ifstream file;
        std::string tmp;
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        try
        {
            tree.Clear();
            file.open("list.txt");

            while (!file.eof())
            {
                std::getline(file, tmp);
                tree.Insert(std::stoi(tmp));
            }
            file.close();
        }
        catch (const std::exception& ex)
        {
            std::cout << "An error has occuried" << '\n' << ex.what() << '\n';
            tree.Clear();
        }
    }

    /*
    * Ôóíêöèÿ ïðîâåðêè êîððåêòíîñòè ââîäà
    */
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