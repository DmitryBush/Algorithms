#pragma once
#include "TreeNode.h"

class list
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
		TreeNode* value;
		node* prev, *next;

		node(TreeNode* val = nullptr, node* next = nullptr): 
			next(next), prev(nullptr) {
			value = val;
		}
	};
	
	node* head;
	unsigned int countElements;
public:
	list();
	~list();


	int GetCountOfElements() const { return countElements; }

	bool PushForward(TreeNode* val = nullptr);

	bool PopForward(const unsigned int& id_Elem);
	bool PopForward();
	void Clear();

	bool IsEmpty() const { return head == nullptr; }
	void ResetList();

	TreeNode* operator[] (const unsigned int index);

	void Task();
	void Print();
};