#pragma once
#include <fstream>
#include <string>
#include <conio.h>
#include <iostream>

namespace treeUtils
{
    
    nTree& RandomFillMatrix(nTree& tree)
    {
        tree.Clear();
        srand(time(NULL));

        tree.Push((rand() % 100) + 1);
        for (unsigned int i = 0; i < 5; i++)
        {
            for (unsigned int i = 0; i < 5; i++)
            {
                tree.Push((rand() % 100) + 1);
            }
            tree.MoveNode(rand() % 4);
        }
        tree.ResetToRoot();
        return tree;
    }

    
    void FileFillMatrix(nTree& tree)
    {
        std::ifstream file;
        std::string tmp;
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        try
        {
            tree.Clear();
            file.open("NTree.txt");

            while (!file.eof())
            {
                for (auto i = 0; i < 4; i++)
                {
                    std::getline(file, tmp);
                    tree.Push(std::stoi(tmp));
                }
                tree.MoveNode(1);

                for (auto i = 0; i < 4; i++)
                {
                    std::getline(file, tmp);
                    tree.Push(std::stoi(tmp));
                }
            }
            file.close();
        }
        catch (const std::exception& ex)
        {
            std::cout << "An error has occuried" << '\n' << ex.what() << '\n';
            tree.Clear();
        }
        tree.ResetToRoot();
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
        system("cls");
    }

    void EditTree(nTree& tree)
    {
        bool editing = true;
        while (editing)
        {
            int elem = 0; tree.PrintCurr();

            std::cout << "Operations:" << '\n'
                << "1) Move to node" << '\n'
                << "2) Add element" << '\n'
                << "3) Clear current height" << '\n'
                << "4) Reset to root" << '\n'
                << "0) Back" << '\n';
            switch (_getch())
            {
            case '1':
                std::cout << "Enter node" << '\n';
                std::cin >> elem;
                treeUtils::CheckInputValidation(elem, "node");
                tree.MoveNode(elem - 1);

                break;
            case '2':
                std::cout << "Enter value" << '\n';
                std::cin >> elem;
                treeUtils::CheckInputValidation(elem, "value");
                tree.Push(elem);

                break;
            case '3':
                system("cls");
                tree.DeleteCurrHeight();

                break;
            case '4':
                system("cls");
                tree.ResetToRoot();

                break;
            case '0':
                system("cls");
                editing = false;
                break;
            default:
                system("cls");
                std::cout << "An error has occuried" << '\n';
                break;
            }
        }
    }
}