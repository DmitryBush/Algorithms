#pragma once
#include <string>

class person
{
public:
	std::string surname;
	std::string name;
	std::string fatherName;

	person(std::string surname, std::string name, std::string fatherName) :
		surname(surname), name(name), fatherName(fatherName) {}
};

bool operator==(person arg_1, person arg_2)
{
	if (arg_1.name == arg_2.name
		&& arg_1.surname == arg_2.surname
		&& arg_1.fatherName == arg_2.fatherName)
		return true;
	return false;
}