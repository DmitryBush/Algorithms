#pragma once
#include "HashNode.h"


class hashTable
{
private:
	// Первоначальный размер хэш таблицы
	const unsigned int defaultSize = 10;
	// Коэффициент заполнености ре-хэширования
	const float ratioCapacity = 0.75f;

	node** table;
	// Количество элементов хэш таблицы
	unsigned int countElements;
	// Количество всех элементов таблицы (в том числе и удаленных)
	unsigned int countAllElements;
	// Выделенные элементы под двумерный массив table
	unsigned int tableSize;

	int ComputeAddress(const std::string surname, const std::string name,
		const std::string fatherName);
	unsigned int SumStr(const std::string surname, const std::string name,
		const std::string fatherName);
	unsigned int CalcNumDigit(const unsigned int numb);
	void ReSize();
	void CleanUpArr(node** arr, const unsigned int& arrSize);
	void InitializeTable();
public:
	hashTable();

	void Push(std::string surname, std::string name, 
		std::string fatherName);
	void Find(std::string surname, std::string name,
		std::string fatherName);
	void Pop(std::string surname, std::string name,
		std::string fatherName);
	void ReHash();

	void Clear();
	void Print();

	~hashTable();
};
