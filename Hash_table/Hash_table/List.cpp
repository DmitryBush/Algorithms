#include "List.h"
#include <iostream>
#include <conio.h>

/*
* ����������� ��� ����������
*/
list::list() : countElements(0) { head = nullptr; }

/*
* ����������, ��������� ������
*/
list::~list() { Clear(); }

/*
* ��������� ������ ��� ����� ������� ���������������� ������
*/
bool list::PushForward(std::string surname, std::string name,
	std::string fatherName)
{
	if (head == nullptr)
	{
		try
		{
			// ������� ��������� ������ ��� ���� � ���������� ����������
			head = new nodeList(surname, name, fatherName);
			countElements++;			
			return true;
		}
		catch (const std::bad_alloc& ex)
		{
			std::cout << "An error has occured" << "(code: " << ex.what()
				<< "Not enough free RAM. Close other programs and try again" << std::endl;
			return false;
		}
	}
	else
	{
		try
		{
			// ������� ��������� ������ ��� ���� � ���������� ����������
			nodeList* curr = new nodeList(surname, name, 
				fatherName, head);	
			head->prev = curr;					

			head = curr;
			countElements++;
			return true;
		}
		catch (const std::bad_alloc& ex)
		{
			std::cout << "An error has occured" << "(code: " << ex.what()
				<< "Not enough free RAM. Close other programs and try again" << std::endl;
			return false;
		}
	}
}

/*
* �������� �������� ���������������� ������, �� ���������� �������
*/
bool list::PopForward(const unsigned int& index)
{
	int a = 1;
	nodeList* del;

	if (head == nullptr)
	{
		std::cout << "List is empty" << std::endl;
		return false;
	}
	else if (index <= 0 && index > countElements)		// ������ ��������� � ����������� ��������
	{
		std::cout << "This element does not exist" << std::endl;
		return false;
	}
	else if (index == 1)
	{
		if (head->next == nullptr && head->prev == nullptr)		// � ������ ���� �������
		{
			delete head;
			head = nullptr;
			countElements = 0;

			return true;
		}
		else if (head->prev)			// ������ ������ �� ��������� � ������
		{
			ResetList();

			del = head;
			head = head->next;
			head->prev = nullptr;

			delete del;
			countElements--;

			return true;
		}
		else							// � ������ ����� ���������
		{
			del = head;
			head = head->next;
			head->prev = nullptr;

			delete del;
			countElements--;

			return true;
		}
	}
	else if (head->prev)		// ������ ������ �� ��������� � ������
	{
		ResetList();

		nodeList* curr = head;
		while (curr->next)		// ���� ����������� �������� �� ��������� ������� �������
		{
			if (a + 1 == index && curr->next->next != nullptr)	// ���� ��������� ������� �� �������� ���������
			{
				del = curr->next;
				curr->next = curr->next->next;		// �� ������������� ��������� � ������� �������

				nodeList* tmp = curr->next->next;
				tmp->prev = curr;

				delete del;
				countElements--;

				return true;
			}
			else if (a + 1 == index)	// ���� ��������� ������� ���������
			{
				del = curr->next;
				curr->next = nullptr;	// �� ������������� ��������� � ������� �������

				delete del;
				countElements--;

				return true;
			}
			else						// ���� ������ �� ������
			{
				curr = curr->next;
				a++;
			}
		}
		return false;
	}
	else
	{
		nodeList* curr = head;
		while (curr->next)			// ���� ����������� �������� �� ��������� ������� �������
		{
			if (a + 1 == index && curr->next->next != nullptr)	// ���� ��������� ������� �� �������� ���������
			{
				del = curr->next;
				curr->next = curr->next->next;			// �� ������������� ��������� � ������� �������

				nodeList* tmp = curr->next->next; tmp->prev = curr;

				delete del;
				countElements--;

				return true;
			}
			else if (a + 1 == index)	// ���� ��������� ������� ���������
			{
				del = curr->next;
				curr->next = nullptr;	// �� ������������� ��������� � ������� �������

				delete del;
				countElements--;

				return true;
			}
			else						// ����� ���� ������ �� ������
			{
				curr = curr->next;
				a++;
			}
		}
		return false;
	}
}

/*
* �������� �������� �������� ���������������� ������
*/
bool list::PopForward()
{
	nodeList* del;

	if (head == nullptr)
	{
		std::cout << "List is empty" << std::endl;
		return false;
	}
	else
	{
		if (head->next == nullptr && head->prev == nullptr)		// � ������ ���� �������
		{
			delete head;
			head = nullptr;
			countElements = 0;

			return true;
		}
		else if (head->prev)				// ������ ������ �� ��������� � ������
		{
			ResetList();
			del = head;
			head = head->next;
			head->prev = nullptr;

			delete del;
			countElements--;

			return true;
		}
		else
		{
			del = head;
			head = head->next;
			head->prev = nullptr;

			delete del;
			countElements--;

			return true;
		}
	}
}

/*
* ����� �������� ������
*/
void list::Clear()
{
	nodeList* del;
	if (head == nullptr) { return; }
	else
	{
		while (head->next)		// ���� ��������� �������� ������, ���� �� ���� ���� ���������
		{
			del = head;
			head = head->next;
			delete del;
		}
		delete head;			// �������� ���������� ��������
	}
	head = nullptr;
	countElements = 0;
}

/*
* ��������� ��������� ������ ������ � ����������� ���������
*/
void list::ResetList()
{
	if (head == nullptr) {}
	else
	{
		while (head->prev)
		{
			head = head->prev;
		}
	}
}

/*
* ���������� ��������� ���������� ������, ������� ���������� ��������� �� �������
*/
nodeInList* list::operator[](const unsigned int index)
{
	if (index < 0 || index > countElements)
	{
		throw("invalid index");
	}

	if (head == nullptr)
	{
		throw("empty list");
	}

	nodeList* curr = head;
	for (unsigned int i = 0; i < index; i++) 
	{
		curr = curr->next;
		if (!curr) 
			return nullptr;
	}
	return &curr->value;
}
