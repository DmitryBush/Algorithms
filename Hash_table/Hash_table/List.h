#pragma once
#include "HashNode.h"

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
		node value;
		nodeList* prev, *next;

		nodeList(std::string surname, std::string name, 
			std::string fatherName, nodeList* next = nullptr):
			next(next), value(surname, name, fatherName), prev(nullptr) {}
	};
	
	nodeList* head;
	unsigned int countElements;
public:
	list();
	~list();


	int GetCountOfElements() const { return countElements; }

	bool PushForward(std::string surname, std::string name,
		std::string fatherName);

	bool PopForward(const unsigned int& id_Elem);
	bool PopForward();
	void Clear();

	bool IsEmpty() const { return head == nullptr; }
	void ResetList();

	node* operator[] (const unsigned int index);

};