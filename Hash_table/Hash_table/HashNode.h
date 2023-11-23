#pragma once
#include "List.h"

class node
{
public:
	person human;
	list stack;
	std::string key;
	bool deleted, collision;

	node(std::string surname, std::string name, 
		std::string fatherName, std::string key) :
		human(surname, name, fatherName), deleted(false), 
		collision(false), key(key) {}
};
