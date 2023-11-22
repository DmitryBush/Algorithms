﻿#include <iostream>
#include "Dict.h"
#include "Utils.h"

int main()
{
    system("chcp 1251"); system("cls");
    dict storage; bool running = true;
    while (running)
    {
        std::string str, key;
        int elem = 0, value = 0;
        storage.Print();
        std::cout << "Operations:" << '\n'
            << "1) Add Element" << '\n'
            << "2) Delete Element" << '\n'
            << "3) Clear list" << '\n'
            << "4) Fill list from file" << '\n'
            << "5) Run Task" << '\n'
            << "0) Close" << '\n';
        switch (_getch())
        {
        case '1':
            std::cout << "Enter string" << '\n';
            std::cin >> str;
            //dictUtils::CheckInputValidation(elem, "value");
            std::cin >> key;
            //dictUtils::CheckInputValidation(elem, "value");
            storage.PushForward(str.c_str(), key.c_str());

            system("cls");
            break;
        case '2':
            std::cout << "Enter element to delete" << '\n';
            std::cin >> key;
            //dictUtils::CheckInputValidation(elem, "element");
            storage.PopForward(key);

            system("cls");
            break;
        case '3':
            system("cls");
            storage.Clear();

            break;
        case '4':
            system("cls");
            dictUtils::FileFillList(storage);

            break;
        case '5':
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