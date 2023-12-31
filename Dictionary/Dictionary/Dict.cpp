#include "Dict.h"
#include <iostream>
#include <conio.h>
#include "Algorithm.h"

/*
* ����������� ��� ����������
*/
dict::dict() : countElements(0) { head = nullptr; }

dict::dict(const dict& arg)
{
	this->PushForward(arg.head->value.GetString(), arg.head->key.GetString());
	
	node* curr = arg.head->next;
	for (auto i = 0; i < arg.countElements - 1; i++)
	{
		this->PushForward(curr->value.GetString(), curr->key.GetString());
		curr = curr->next;
	}
}

/*
* ����������, ��������� ������
*/
dict::~dict() { Clear(); }

/*
* ��������� ������ ��� ����� ������� ���������������� ������
*/
void dict::PushForward(const char* val, const char* key)
{
	if (head == nullptr)
	{
		try
		{
			head = new node(val, key);		
			countElements++;			
		}
		catch (const std::bad_alloc& ex)
		{
			std::cout << "An error has occured" << "(code: " << ex.what()
				<< "Not enough free RAM. Close other programs and try again" << std::endl;
		}
	}
	else
	{
		try
		{
			node* currKey = head;
			for (auto i = 0; i < countElements; i++)
			{
				if (!strcmp(currKey->key.GetString(), key))
					return;
				currKey = currKey->next;
			}
			node* curr = new node(val, key, head);	
			head->prev = curr;					

			head = curr;
			countElements++;
		}
		catch (const std::bad_alloc& ex)
		{
			std::cout << "An error has occured" << "(code: " << ex.what()
				<< "Not enough free RAM. Close other programs and try again" << std::endl;
		}
	}
}

/*
* �������� �������� ���������������� ������, �� ���������� �������
*/
bool dict::PopForward(std::string key)
{
	int a = 1, index = 0;
	node* del = head;
	for (auto i = 0; i < countElements; i++)
	{
		if (!strcmp(del->key.GetString(), key.c_str()))
		{
			index = i + 1;
			break;
		}
		del = del->next;
	}

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

		node* curr = head;
		while (curr->next)		// ���� ����������� �������� �� ��������� ������� �������
		{
			if (a + 1 == index && curr->next->next != nullptr)	// ���� ��������� ������� �� �������� ���������
			{
				del = curr->next;
				curr->next = curr->next->next;		// �� ������������� ��������� � ������� �������

				node* tmp = curr->next->next;
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
		node* curr = head;
		while (curr->next)			// ���� ����������� �������� �� ��������� ������� �������
		{
			if (a + 1 == index && curr->next->next != nullptr)	// ���� ��������� ������� �� �������� ���������
			{
				del = curr->next;
				curr->next = curr->next->next;			// �� ������������� ��������� � ������� �������

				node* tmp = curr->next->next; tmp->prev = curr;

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
bool dict::PopForward()
{
	node* del;

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
void dict::Clear()
{
	node* del;
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
void dict::ResetList()
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
const char* dict::operator[](const char* str)
{
	if (head == nullptr)
		throw("Dict is empty");

	node* curr = head;
	for (unsigned int i = 0; i < countElements; i++) 
	{
		if (!curr) 
			throw("Not key?");
		if (!strcmp(str, curr->key.GetString()))
		{
			return curr->value.GetString();
		}
		curr = curr->next;
	}
}

/*
* �������� �������. 
* ����� � ��� ��� ��������� (�����, ������������ �� ����� � ��� �� ����)
*/
void dict::Task()
{
	unsigned int countAnagram = 0;
	dict copy(*this);
	if (head)
	{
		node* curr = copy.head;
		while (curr->next)
		{
			node* secCur = curr->next; 
			Algorithm::QuickSort(curr->value.GetString(), 
				curr->value.size() - 1);
			while (secCur->next)
			{
				Algorithm::QuickSort(secCur->value.GetString(),
					secCur->value.size() - 1);
				if (!strcmp(curr->value.GetString(), secCur->value.GetString()))
					countAnagram++;
				secCur = secCur->next;
			}
			curr = curr->next;
		}
		node* secCur = curr;
		Algorithm::QuickSort(secCur->value.GetString(),
			secCur->value.size() - 1);
		if (!strcmp(curr->prev->value.GetString(), secCur->value.GetString()))
			countAnagram++;
		std::cout << "There is " << countAnagram << " anagram" << '\n';
	}
	else
		std::cout << "There is 0 anagram" << '\n';
}

/*
* ����� ������ � �������
*/
void dict::Print()
{
	if (head != nullptr && head->prev)		// ���� ������ ������ �� � ����������� ���������
		ResetList();

	node* curr = head;
	if (curr == nullptr)
	{
		std::cout << "There's no object in list to show" << '\n';
	}
	else
	{
		while (curr->next)
		{
			std::cout << "Value - " << curr->value.GetString() 
				<< " Key - " << curr->key.GetString() << '\n';
			curr = curr->next;
		}
		std::cout << "Value - " << curr->value.GetString()
			<< " Key - " << curr->key.GetString() << '\n';
	}
}
