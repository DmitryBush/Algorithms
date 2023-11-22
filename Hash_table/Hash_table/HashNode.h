#pragma once
#include "Person.h"
#include "List.h"

class node
{
public:
	person human;
	list stack;
	bool deleted, collision;

	node(std::string surname, std::string name, std::string fatherName) :
		human(surname, name, fatherName), deleted(false), collision(false) {}
};