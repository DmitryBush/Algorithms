#include <iostream>
#include "List.h"
#include <fstream>
#include <string>
#include <conio.h>

void FileFillList(list& list);
void RandomFillList(list& list);
void CheckInputValidation(int& inpValue, const char* str);

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
            CheckInputValidation(elem, "value");
            storage.PushForward(elem);

            system("cls");
            break;
        case '2':
            std::cout << "Enter element to delete" << '\n';
            std::cin >> elem;
            CheckInputValidation(elem, "element");
            storage.PopForward(elem);

            system("cls");
            break;
        case '3':
            system("cls");
            std::cout << "Enter element to edit" << '\n';
            std::cin >> elem;
            CheckInputValidation(elem, "element");
            std::cout << "Enter value" << '\n';
            std::cin >> value;
            CheckInputValidation(value, "value");

            *storage[elem - 1] = value;
            break;
        case '4':
            system("cls");
            storage.Clear();

            break;
        case '5':
            system("cls");
            RandomFillList(storage);

            break;
        case '6':
            system("cls");
            FileFillList(storage);

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
}

/*
* Функция заполнения списка случайными числами
*/
void RandomFillList(list& list)
{
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
    file.exceptions(std::ifstream::badbit|std::ifstream::failbit);

    try
    {
        file.open("list1.txt");

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