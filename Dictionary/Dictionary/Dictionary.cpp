#include <iostream>
#include "String.h"
#include "Algorithm.h"

int main()
{
	str a;
	//std::cout << sizeof(nullptr);
	a.Push("cba");
	Algorithm::QuickSort(a.GetString(), a.size());
	a.Print();
}