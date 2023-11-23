#pragma once
#include "Person.h"

class nodeInStack
{
public:
	person human;
	std::string key;
	bool deleted, collision;

	nodeInStack(std::string surname, std::string name, 
		std::string fatherName, std::string key) :
		human(surname, name, fatherName), deleted(false), 
		collision(false), key(key) {}
};

class list
{
private:
	/*
	* Класс узел, недоступный за границами методов класса,
	* включающий в себя информацию о точке, указатель на предыдущий/следующий элемент
	* и конструктор с параметрами по умолчанию
	*/
	class nodeList
	{
	public:
		nodeInStack value;
		nodeList* prev, *next;

		nodeList(std::string surname, std::string name, 
			std::string fatherName, std::string key, nodeList* next = nullptr):
			next(next), value(surname, name, fatherName, key), prev(nullptr) {}
	};
	
	nodeList* head;
	unsigned int countElements;
public:
	list();
	~list();


	int GetCountOfElements() const { return countElements; }

	bool PushForward(std::string surname, std::string name,
		std::string fatherName, std::string key);

	bool PopForward(const unsigned int& id_Elem);
	bool PopForward();
	void Clear();

	bool IsEmpty() const { return head == nullptr; }
	void ResetList();

	nodeInStack* operator[] (const unsigned int index);

};