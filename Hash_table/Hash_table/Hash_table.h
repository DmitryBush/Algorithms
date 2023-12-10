#pragma once
#include "HashNode.h"


class hashTable
{
private:
	// �������������� ������ ��� �������
	const unsigned int defaultSize = 10;
	// ����������� ������������ ��-�����������
	const float ratioCapacity = 0.75f;

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
