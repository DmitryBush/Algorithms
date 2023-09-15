#include <iostream>
#include "List.h"
#include "Utilities.h"


int main()
{
    list storage; bool running = true;
    while (running)
    {
        int elem = 0, value = 0;
        storage.Print();
        std::cout << "Operations:" << '\n'
            << "1) Add Element" << '\n'
            << "2) Delete Element" << '\n'
            << "3) Edit Element" << '\n'
            << "4) Clear list" << '\n'
            << "5) Fill list random numbers" << '\n'
            << "6) Fill list from file" << '\n'
            << "7) Run Task" << '\n'
            << "0) Close" << '\n';
        switch (_getch())
        {
        case '1':
            std::cout << "Enter value" << '\n';
            std::cin >> elem;
            listUtils::CheckInputValidation(elem, "value");
            storage.PushForward(elem);

            system("cls");
            break;
        case '2':
            std::cout << "Enter element to delete" << '\n';
            std::cin >> elem;
            listUtils::CheckInputValidation(elem, "element");
            storage.PopForward(elem);

            system("cls");
            break;
        case '3':
            system("cls");
            std::cout << "Enter element to edit" << '\n';
            std::cin >> elem;
            listUtils::CheckInputValidation(elem, "element");
            std::cout << "Enter value" << '\n';
            std::cin >> value;
            listUtils::CheckInputValidation(value, "value");

            *storage[elem - 1] = value;
            break;
        case '4':
            system("cls");
            storage.Clear();

            break;
        case '5':
            system("cls");
            listUtils::RandomFillList(storage);

            break;
        case '6':
            system("cls");
            listUtils::FileFillList(storage);

            break;
        case '7':
            system("cls");
            storage.Task();

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
