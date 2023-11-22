#pragma once

class str 
{
private:
	char* data;
	unsigned int countElements;

	unsigned int DefineCountElem(const char* arr = nullptr);
	unsigned int SizeOfArr(const char* arr);
	char* AllocateMem(char* arr);
	void CleanUpArray();
public:
	str();
	str(const char* string);
	str(const str& arg);

	unsigned int size();
	void Clear();

	char* GetString() { return data; }

	void Push(const char* string);

	void Print();
	~str();
};
