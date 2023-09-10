#pragma once

class list
{
private:
	/*
	* ����� ����, ����������� �� ��������� ������� ������,
	* ���������� � ���� ���������� � �����, ��������� �� ����������/��������� �������
	* � ����������� � ����������� �� ���������
	*/
	class node
	{
	public:
		int value;
		node* prev, *next;

		node(int val = 0, node* next = nullptr): next(next), value(val), prev(nullptr) {}
	};
	
	node* head;
	unsigned int countElements;
public:
	list();
	~list();


	int GetCountOfElements() const { return countElements; }

	bool PushForward(const int val = 0);

	bool PopForward(const unsigned int& id_Elem);
	bool PopForward();
	void Clear();

	bool IsEmpty() const { return head == nullptr; }
	void ResetList();

	int* operator[] (const unsigned int index);

	void Task();
	void Print();
};