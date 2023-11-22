#pragma once
#include "Person.h"
#include "List.h"
#include "HashNode.h"

//class node
//{
//public:
//	person human;
//	list stack;
//	bool deleted, collision;
//
//	node(std::string surname, std::string name, std::string fatherName): 
//		human(surname, name, fatherName), deleted(false), collision(false) {}
//};

class hashTable
{
private:
	const unsigned int defaultSize = 10;
	const float ratioCapacity = 0.75;

	node** table;
	// Количество элементов хэш таблицы
	unsigned int countElements;
	// Количество всех элементов таблицы (в том числе и удаленных)
	unsigned int countAllElements;
	// Выделенные элементы под двумерный массив table
	unsigned int tableSize;

	int ComputeAddress(const std::string str);
	unsigned int SumStr(const std::string str);
	unsigned int CalcNumDigit(const unsigned int numb);
	void ReHash();
	void CleanUpArr(node** arr);
public:
	hashTable();

	void Push(std::string surname, std::string name, std::string fatherName);

	~hashTable();
};