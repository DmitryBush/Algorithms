#pragma once
#include "HashNode.h"


class hashTable
{
private:
	const unsigned int defaultSize = 10;
	const float ratioCapacity = 0.75;

	node** table;
	// ���������� ��������� ��� �������
	unsigned int countElements;
	// ���������� ���� ��������� ������� (� ��� ����� � ���������)
	unsigned int countAllElements;
	// ���������� �������� ��� ��������� ������ table
	unsigned int tableSize;

	int ComputeAddress(const std::string surname, const std::string name,
		const std::string fatherName);
	unsigned int SumStr(const std::string surname, const std::string name,
		const std::string fatherName);
	unsigned int CalcNumDigit(const unsigned int numb);
	void ReSize();
	void CleanUpArr(node** arr, const unsigned int& arrSize);
public:
	hashTable();

	void Push(std::string surname, std::string name, 
		std::string fatherName);
	void Find(std::string surname, std::string name,
		std::string fatherName);
	void Pop(std::string surname, std::string name,
		std::string fatherName);
	void ReHash();

	void Print();

	~hashTable();
};

//bool operator==(person arg_1, person arg_2)
//{
//	if (arg_1.name == arg_2.name
//		&& arg_1.surname == arg_2.surname
//		&& arg_1.fatherName == arg_2.fatherName)
//		return true;
//	return false;
//}