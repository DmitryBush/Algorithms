#pragma once
#include <string>

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
		std::string value;
		std::string key;
		node* prev, *next;

		node(std::string val, std::string key, node* next = nullptr):
			next(next), value(val), key(key), prev(nullptr) {}
	};
	
	node* head;
	unsigned int countElements;
public:
	dict();
	~dict();


	int GetCountOfElements() const { return countElements; }

	bool PushForward(std::string val, std::string key);

	bool PopForward(const unsigned int& id_Elem);
	bool PopForward();
	void Clear();

	bool IsEmpty() const { return head == nullptr; }
	void ResetList();

	std::string operator[](const std::string str);

	void Task();
	void Print();
};