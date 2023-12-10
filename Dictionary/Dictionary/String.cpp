#include "String.h"
#include <string.h>
#include <iostream>

// Метод выделения памяти
char* str::AllocateMem(char* arr)
{
	arr = new char[countElements];
	return arr;
}

/*
* Метод определения количества элементов
* для обновленного массива
*/
unsigned int str::DefineCountElem(const char* arr)
{
	if (arr || data)
		return countElements = SizeOfArr(arr) + SizeOfArr(data);
	return countElements = 0;
}

// Метод возращающий размер массива
unsigned int str::SizeOfArr(const char* arr)
{
	if (arr)
	{
		int size = 0;
		while (arr[size] != '\0')
		{
			++size;
		}
		return size + 1;
	}
	return 0;
}

void str::CleanUpArray()
{
	if (data)
	{
		delete[] data;
		data = nullptr;
		countElements = 0;
	}
}

str::str()
{
	data = nullptr;
	countElements = 0;
}

str::str(const char* string)
{
	Push(string);
}

str::str(const str& arg): countElements(arg.countElements)
{
	data = AllocateMem(data);
	strcpy_s(data, sizeof(arg.data), arg.data);
}

unsigned int str::size()
{
	return countElements;
}

void str::Clear()
{
	CleanUpArray();
}

// Вывод строки
void str::Print()
{
	for (auto i = 0; i < countElements; i++)
	{
		std::cout << data[i];
	}
	std::cout << '\n';
}

str::~str()
{
	CleanUpArray();
}

// Метод добавления элемента
void str::Push(const char* string)
{
	DefineCountElem(string);
	char* newArr = nullptr;
	newArr = AllocateMem(newArr);

	if (data)
	{
		strcpy_s(newArr, SizeOfArr(data), data);
		strcpy_s(newArr, SizeOfArr(string), string);
	}
	else
		strcpy_s(newArr, SizeOfArr(string), string);

	data = newArr;
}
