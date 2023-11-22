#include "Hash_table.h"

int hashTable::ComputeAddress(const std::string str)
{
	unsigned int sum = SumStr(str);
	unsigned int digit = CalcNumDigit(sum);
	if (digit)
	{
		int* sumParts = new int[digit] {0};
		register int i = 0;
		do
		{
			*(sumParts + i) = sum % 100;
			i++;
		} while (sum /= 100);

		for (auto i = 0; i < digit; i++)
			sum += sumParts[i];
		delete[] sumParts;
		return static_cast<int>(sum % tableSize);
	}
	else
	{
		return -1;
	}
}

unsigned int hashTable::SumStr(const std::string str)
{
	int sum = 0;
	for (auto i = 0; str[i] != str.size(); i++)
		sum += str[i];
	return sum;
}

unsigned int hashTable::CalcNumDigit(unsigned int numb)
{
	int digits = 0;
	do { digits++; } while (numb /= 10);
	return digits;
}

void hashTable::ReHash()
{
	countElements = 0, countAllElements = 0;
	node** newArr = new node * [tableSize] {nullptr};
	std::swap(table, newArr);
	for (auto i = 0; i < tableSize; i++)
	{
		if (newArr[i])
			if (!newArr[i]->deleted)
				Push(newArr[i]->human);
	}

	CleanUpArr(newArr);
}

void hashTable::CleanUpArr(node** arr)
{
	if (arr)
	{
		for (auto i = 0; i < tableSize; i++)
		{
			if (arr[i])
				delete arr[i];
		}
		delete[] arr;
	}
}

hashTable::hashTable(): countElements(0), countAllElements(0)
{
	tableSize = defaultSize;
	table = new node * [tableSize] {nullptr};
}

void hashTable::Push(std::string surname, std::string name, std::string fatherName)
{
	/*if (countElements + 1 > static_cast<int>(tableSize * ratioCapacity))
		Resize();
	else if (countAllElements > countElements * 2)
		ReHash();*/

	int index = ComputeAddress(surname);
	if (index == -1)
		return;
	else if (!table[index])
	{
		table[index] = new node(surname, name, fatherName);
		countAllElements++;
	}
	else
	{
		person tmpPers(surname, name, fatherName);

		if (table[index]->human == tmpPers)
			return;
		else if (table[index]->deleted)
		{
			table[index]->human = tmpPers;
			countAllElements--;
		}
		else if (table[index]->collision)
		{
			for (auto i = 0; i < table[index]->stack.GetCountOfElements(); i++)
				if (table[index]->stack[i]->human == tmpPers)
					return;

			bool delUsed = false;
			for (auto i = 0; i < table[index]->stack.GetCountOfElements(); i++)
			{
				if (table[index]->stack[i]->deleted)
				{
					table[index]->stack[i]->human = tmpPers;
					countAllElements--;
					delUsed = true;
					break;
				}
			}

			if (delUsed)
			{
				table[index]->stack.PushForward(surname, name, fatherName);
				countAllElements++;
			}
		}
		else
		{
			table[index]->collision = true;
			table[index]->stack.PushForward(surname, name, fatherName);
			countAllElements++;
		}
	}
	countElements++;
}

hashTable::~hashTable()
{
	if (table)
	{
		for (auto i = 0; i < tableSize; i++)
		{
			if (table[i])
				delete table[i];
		}
		delete[] table;
	}
}
