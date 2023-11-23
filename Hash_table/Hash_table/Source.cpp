#include "Hash_table.h"


int main()
{
	hashTable storage;
	storage.Push("Kuzmin", "Lev", "Matveevich");
	storage.Push("Astaxova", "Elizabeth", "Yanovna");
	storage.Push("Merkulova", "Maya", "Maximovna");
	storage.Push("Fomina", "Angeline", "Andreevna");
	storage.Push("Galkin", "Artem", "Denisovich");
	//storage.ReHash();
	storage.Print();
}
