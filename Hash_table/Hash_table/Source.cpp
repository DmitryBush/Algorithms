#include "Hash_table.h"


int main()
{
	hashTable storage;
	storage.Push("Kuzmin", "Lev", "Matveevich", "asd");
	storage.Push("Astaxova", "Elizabeth", "Yanovna", "Doubtful");
	storage.Push("Merkulova", "Maya", "Maximovna", "Almond");
	storage.Push("Fomina", "Angeline", "Andreevna", "Construction");
	storage.Push("Galkin", "Artem", "Denisovich", "Friendship");
	
	storage.Print();
}
