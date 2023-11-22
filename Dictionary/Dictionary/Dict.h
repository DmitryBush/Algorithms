#pragma once
#include <string>
#include "String.h"

class dict
{
private:
	/*
	* Класс узел, недоступный за границами методов класса,
	* включающий в себя информацию о точке, указатель на предыдущий/следующий элемент
	* и конструктор с параметрами по умолчанию
	*/
	class node
	{
	public:
		str value;
		str key;
		node* prev, *next;

		node(const char* val, const char* key, node* next = nullptr):
			next(next), value(val), key(key), prev(nullptr) {}
	};
	
	node* head;
	unsigned int countElements;
public:
	dict();
	~dict();


	int GetCountOfElements() const { return countElements; }

	bool PushForward(const char* val, const char* key);

	bool PopForward(std::string key);
	bool PopForward();
	void Clear();

	bool IsEmpty() const { return head == nullptr; }
	void ResetList();

	const char* operator[](const char* str);

	void Task();
	void Print();
};