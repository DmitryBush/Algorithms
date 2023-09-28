#include "BinaryTree.h"
#include "TreeUtils.h"
#include <iostream>

int main()
{
    bool running = true; BinaryTree tree;
    while (running)
    {
        int elem = 0; tree.Print();
        std::cout << "Operations:" << '\n'
            << "1) Add Element" << '\n'
            << "2) Delete Element" << '\n'
            << "3) Clear tree" << '\n'
            << "4) Fill tree random numbers" << '\n'
            << "5) Fill tree from file" << '\n'
            << "6) Run Task" << '\n'
            << "0) Close" << '\n';
        switch (_getch())
        {
        case '1':
            std::cout << "Enter value" << '\n';
            std::cin >> elem;
            treeUtils::CheckInputValidation(elem, "value");
            tree.Insert(elem);

            system("cls");
            break;
        case '2':
            std::cout << "Enter element to delete" << '\n';
            std::cin >> elem;
            treeUtils::CheckInputValidation(elem, "value");

            tree.DeleteNode(elem);

            //system("cls");
            break;
        case '3':
            system("cls");
            tree.Clear();

            break;
        case '4':
            system("cls");
            treeUtils::RandomFillMatrix(tree);

            break;
        case '5':
            system("cls");
            treeUtils::FileFillMatrix(tree);

            break;
        case '6':
            system("cls");
            tree.Task();

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