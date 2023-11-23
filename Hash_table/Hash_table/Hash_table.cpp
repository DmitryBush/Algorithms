#include "Hash_table.h"
#include <iostream>

int hashTable::ComputeAddress(const std::string key)
{
	unsigned int sum = SumStr(key);
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
	for (auto i = 0; i < str.size(); i++)
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
		{
			if (newArr[i]->deleted)
			{
				if (newArr[i]->collision)
				{
					for (auto j = 0; j < newArr[i]->stack.GetCountOfElements(); j++)
					{
						Push(newArr[i]->stack[j]->human.surname,
							newArr[i]->stack[j]->human.name,
							newArr[i]->stack[j]->human.fatherName,
							newArr[i]->stack[j]->key);
					}
				}
			}
			else
			{
				Push(newArr[i]->human.surname, newArr[i]->human.name,
					newArr[i]->human.fatherName, newArr[i]->key);
				if (newArr[i]->collision)
				{
					for (auto j = 0; j < newArr[i]->stack.GetCountOfElements(); j++)
					{
						Push(newArr[i]->stack[j]->human.surname,
							newArr[i]->stack[j]->human.name,
							newArr[i]->stack[j]->human.fatherName,
							newArr[i]->stack[j]->key);
					}
				}
			}
		}
	}

	CleanUpArr(newArr, tableSize);
}

void hashTable::ReSize()
{
	unsigned int pastTableSize = tableSize;
	tableSize *= 2;
	countAllElements = 0, countElements = 0;
	node** newArr = new node * [tableSize] {nullptr};
	std::swap(table, newArr);
	for (auto i = 0; i < pastTableSize; i++)
	{
		if (newArr[i])
		{
			if (newArr[i]->deleted)
			{
				if (newArr[i]->collision)
				{
					for (auto j = 0; j < newArr[i]->stack.GetCountOfElements(); j++)
					{
						Push(newArr[i]->stack[j]->human.surname,
							newArr[i]->stack[j]->human.name,
							newArr[i]->stack[j]->human.fatherName,
							newArr[i]->stack[j]->key);
					}
				}
			}
			else
			{
				Push(newArr[i]->human.surname, newArr[i]->human.name,
					newArr[i]->human.fatherName, newArr[i]->key);
				if (newArr[i]->collision)
				{
					for (auto j = 0; j < newArr[i]->stack.GetCountOfElements(); j++)
					{
						Push(newArr[i]->stack[j]->human.surname,
							newArr[i]->stack[j]->human.name,
							newArr[i]->stack[j]->human.fatherName,
							newArr[i]->stack[j]->key);
					}
				}
			}
		}
	}

	CleanUpArr(newArr, pastTableSize);
}

void hashTable::CleanUpArr(node** arr, const unsigned int& arrSize)
{
	if (arr)
	{
		for (auto i = 0; i < arrSize; i++)
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

void hashTable::Push(std::string surname, 
	std::string name, std::string fatherName, std::string key)
{
	if (countElements + 1 > static_cast<int>(tableSize * ratioCapacity))
		ReSize();
	else if (countAllElements > countElements * 2)
		ReHash();

	int index = ComputeAddress(key);
	if (index == -1)
		return;
	else if (!table[index])
	{
		table[index] = new node(surname, name, fatherName, key);
		countAllElements++;
	}
	else
	{
		person tmpPers(surname, name, fatherName);

		if (table[index]->key == key || table[index]->human == tmpPers)
			return;
		else if (table[index]->deleted)
		{
			table[index]->human = tmpPers;
			table[index]->key = key;
			countAllElements--;
		}
		else if (table[index]->collision)
		{
			for (auto i = 0; i < table[index]->stack.GetCountOfElements(); i++)
				if (table[index]->stack[i]->human == tmpPers
					|| table[index]->key == key)
					return;

			bool delUsed = false;
			for (auto i = 0; i < table[index]->stack.GetCountOfElements(); i++)
			{
				if (table[index]->stack[i]->deleted)
				{
					table[index]->stack[i]->human = tmpPers;
					table[index]->key = key;
					countAllElements--;
					delUsed = true;
					break;
				}
			}

			if (!delUsed)
			{
				table[index]->stack.PushForward(surname, name, fatherName, key);
				countAllElements++;
			}
		}
		else
		{
			table[index]->collision = true;
			table[index]->stack.PushForward(surname, name, fatherName, key);
			countAllElements++;
		}
	}
	countElements++;
}

void hashTable::Find(std::string key)
{
	int index = ComputeAddress(key);
	if (index == -1)
		std::cout << "There empty str" << '\n';
	else if (!table[index])
	{
		std::cout << "The specified element does not exist" << '\n';
	}
	else
	{
		if (table[index]->key == key)
		{
			std::cout << table[index]->human.surname << " "
				<< table[index]->human.name << " "
				<< table[index]->human.fatherName << " "
				<< " key - " << table[index]->key << '\n';
		}
		else if (table[index]->deleted && !table[index]->collision)
		{
			std::cout << "The specified element does not exist" << '\n';
		}
		else if (table[index]->collision)
		{
			for (auto i = 0; i < table[index]->stack.GetCountOfElements(); i++)
			{
				if (table[index]->stack[i]->key == key 
					&& !table[index]->stack[i]->deleted)
				{
					std::cout << table[index]->stack[i]->human.surname << " "
						<< table[index]->stack[i]->human.name << " "
						<< table[index]->stack[i]->human.fatherName << " "
						<< " key - " << table[index]->stack[i]->key << '\n';
					break;
				}
				else if (table[index]->stack[i]->key == key
					&& table[index]->stack[i]->deleted)
				{
					std::cout << "The specified element does not exist" << '\n';
					break;
				}
			}
		}
	}
}

void hashTable::Pop(std::string key)
{
	int index = ComputeAddress(key);
	if (index == -1)
		std::cout << "There empty str" << '\n';
	else if (!table[index])
	{
		std::cout << "The specified element does not exist" << '\n';
	}
	else
	{
		if (table[index]->key == key)
		{
			table[index]->deleted = true;
		}
		else if (table[index]->deleted && !table[index]->collision)
		{
			std::cout << "The specified element is already deleted" << '\n';
		}
		else if (table[index]->collision)
		{
			for (auto i = 0; i < table[index]->stack.GetCountOfElements(); i++)
			{
				if (table[index]->stack[i]->key == key
					&& !table[index]->stack[i]->deleted)
				{
					table[index]->stack[i]->deleted = true;
					break;
				}
				else if (table[index]->stack[i]->key == key
					&& table[index]->stack[i]->deleted)
				{
					std::cout << "The specified element is already deleted" << '\n';
					break;
				}
			}
		}
	}
}

void hashTable::Print()
{
	if (table)
	{
		std::cout << "Table size - " << tableSize
			<< " Count of all elements - " << countAllElements
			<< " Count elements - " << countElements << '\n';
		for (auto i = 0; i < tableSize; i++)
		{
			if (table[i])
			{
				if (table[i]->deleted)
				{
					if (table[i]->collision)
					{
						for (auto j = 0; 
							j < table[i]->stack.GetCountOfElements(); j++)
						{
							std::cout << table[i]->stack[j]->human.surname << " "
								<< table[i]->stack[j]->human.name << " "
								<< table[i]->stack[j]->human.fatherName << " "
								<< " key - " << table[i]->stack[j]->key << '\n';
						}
					}
				}
				else
				{
					std::cout << table[i]->human.surname << " "
						<< table[i]->human.name << " "
						<< table[i]->human.fatherName << " "
						<< " key - " << table[i]->key << '\n';
					if (table[i]->collision)
					{
						for (auto j = 0; 
							j < table[i]->stack.GetCountOfElements(); j++)
						{
							std::cout << table[i]->stack[j]->human.surname << " "
								<< table[i]->stack[j]->human.name << " "
								<< table[i]->stack[j]->human.fatherName << " "
								<< " key - " << table[i]->stack[j]->key << '\n';
						}
					}
				}
			}
		}
	}
	else
	{
		std::cout << "Hash table is not initialized" << '\n';
	}
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
