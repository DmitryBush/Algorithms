#include "List.h"
#include <iostream>
#include <conio.h>

/*
* Конструктор без параметров
*/
list::list() : countElements(0) { head = nullptr; }

/*
* Деструктор, очищающий список
*/
list::~list() { Clear(); }

/*
* Выделение памяти под новый элемент двунаправленного списка
*/
bool list::PushForward(std::string surname, std::string name,
	std::string fatherName)
{
	if (head == nullptr)
	{
		try
		{
			// Попытка выделения памяти под узел с переданным параметром
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
			// Попытка выделения памяти под узел с переданным параметром
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
* Удаление элемента двунаправленного списка, по указанному индексу
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
	else if (index <= 0 && index > countElements)		// Индекс находится в невозможных границах
	{
		std::cout << "This element does not exist" << std::endl;
		return false;
	}
	else if (index == 1)
	{
		if (head->next == nullptr && head->prev == nullptr)		// В списке один элемент
		{
			delete head;
			head = nullptr;
			countElements = 0;

			return true;
		}
		else if (head->prev)			// Голова списка не находится в начале
		{
			ResetList();

			del = head;
			head = head->next;
			head->prev = nullptr;

			delete del;
			countElements--;

			return true;
		}
		else							// В списке много элементов
		{
			del = head;
			head = head->next;
			head->prev = nullptr;

			delete del;
			countElements--;

			return true;
		}
	}
	else if (head->prev)		// Голова списка не находится в начале
	{
		ResetList();

		nodeList* curr = head;
		while (curr->next)		// Цикл проверяющий является ли следующий элемент искомым
		{
			if (a + 1 == index && curr->next->next != nullptr)	// Если следующий элемент не является последним
			{
				del = curr->next;
				curr->next = curr->next->next;		// То переприсвоить указатели и удалить элемент

				nodeList* tmp = curr->next->next;
				tmp->prev = curr;

				delete del;
				countElements--;

				return true;
			}
			else if (a + 1 == index)	// Если следующий элемент последний
			{
				del = curr->next;
				curr->next = nullptr;	// То переприсвоить указатель и удалить элемент

				delete del;
				countElements--;

				return true;
			}
			else						// Идти дальше по списку
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
		while (curr->next)			// Цикл проверяющий является ли следующий элемент искомым
		{
			if (a + 1 == index && curr->next->next != nullptr)	// Если следующий элемент не является последним
			{
				del = curr->next;
				curr->next = curr->next->next;			// То переприсвоить указатели и удалить элемент

				nodeList* tmp = curr->next->next; tmp->prev = curr;

				delete del;
				countElements--;

				return true;
			}
			else if (a + 1 == index)	// Если следующий элемент последний
			{
				del = curr->next;
				curr->next = nullptr;	// То переприсвоить указатель и удалить элемент

				delete del;
				countElements--;

				return true;
			}
			else						// Иначе идти дальше по списку
			{
				curr = curr->next;
				a++;
			}
		}
		return false;
	}
}

/*
* Удаление текущего элемента двунаправленного списка
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
		if (head->next == nullptr && head->prev == nullptr)		// В списке один элемент
		{
			delete head;
			head = nullptr;
			countElements = 0;

			return true;
		}
		else if (head->prev)				// Голова списка не находится в начале
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
* Метод очищения списка
*/
void list::Clear()
{
	nodeList* del;
	if (head == nullptr) { return; }
	else
	{
		while (head->next)		// Цикл удаляющий элементы списка, пока за ними есть следующий
		{
			del = head;
			head = head->next;
			delete del;
		}
		delete head;			// Удаление последнего элемента
	}
	head = nullptr;
	countElements = 0;
}

/*
* Переводит указатель головы списка в изначальное состояние
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
* Перегрузка оператора квадратных скобок, который возвращяет указатель на элемент
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
