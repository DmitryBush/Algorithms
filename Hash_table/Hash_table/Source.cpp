#include "Utils.h"

// Основное тело программы 
int main()
{
    bool running = true; hashTable hashTable;
    while (running)
    {
        std::string name, surname, fatherName; hashTable.Print();
        std::cout << "Operations:" << '\n'
            << "1) Add Element" << '\n'
            << "2) Delete Element" << '\n'
            << "3) Find Element" << '\n'
            << "4) Rehash table" << '\n'
            << "5) Clear hashTable" << '\n'
            << "6) Fill hashTable from file" << '\n'
            << "0) Close" << '\n';
        switch (_getch())
        {
        case '1':
            std::cout << "Enter name" << '\n';
            std::cin >> name;
            treeUtils::CheckInputValidation(name, "name");

            std::cout << "Enter surname" << '\n';
            std::cin >> surname;
            treeUtils::CheckInputValidation(surname, "surname");

            std::cout << "Enter fatherName" << '\n';
            std::cin >> fatherName;
            treeUtils::CheckInputValidation(fatherName, "fatherName");
            hashTable.Push(surname, name, fatherName);

            surname.clear();
            name.clear();
            fatherName.clear();
            system("cls");
            break;
        case '2':
            std::cout << "Enter name" << '\n';
            std::cin >> name;
            treeUtils::CheckInputValidation(name, "name");

            std::cout << "Enter surname" << '\n';
            std::cin >> surname;
            treeUtils::CheckInputValidation(surname, "surname");

            std::cout << "Enter fatherName" << '\n';
            std::cin >> fatherName;
            treeUtils::CheckInputValidation(fatherName, "fatherName");
            system("cls");
            hashTable.Pop(surname, name, fatherName);

            surname.clear();
            name.clear();
            fatherName.clear();
            break;
        case '3':
            std::cout << "Enter name" << '\n';
            std::cin >> name;
            treeUtils::CheckInputValidation(name, "name");

            std::cout << "Enter surname" << '\n';
            std::cin >> surname;
            treeUtils::CheckInputValidation(surname, "surname");

            std::cout << "Enter fatherName" << '\n';
            std::cin >> fatherName;
            treeUtils::CheckInputValidation(fatherName, "fatherName");
            system("cls");
            hashTable.Find(surname, name, fatherName);

            surname.clear();
            name.clear();
            fatherName.clear();
            break;
        case '4':
            system("cls");
            hashTable.ReHash();

            break;
        case '5':
            system("cls");
            hashTable.Clear();

            break;
        case '6':
            system("cls");
            treeUtils::FileFillMatrix(hashTable);

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
