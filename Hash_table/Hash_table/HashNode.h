#pragma once
#include "List.h"

//  ласс узел хран€щий информацию в €чейке хэш таблицы
class node
{
public:
	person human;
	list stack;
	bool deleted, collision;

	node(std::string surname, std::string name, 
		std::string fatherName) :
		human(surname, name, fatherName), deleted(false), 
		collision(false) {}
};
