#include <iostream>
#include <string>

unsigned int SumStr(const std::string str)
{
	int sum = 0;
	for (auto i = 0; i < str.size(); i++)
		sum += str[i];
	return sum;
}

unsigned int CalcNumDigit(unsigned int numb)
{
	int digits = 0;
	while (numb > 0)
	{
		digits++;
		numb /= 10;
	}
	return digits;
}

int main()
{
	std::string str = "a";
	unsigned int sum = SumStr(str);
	unsigned int digit = CalcNumDigit(sum);
	if (digit)
	{
		int* sumParts = new int[digit] {0};
		register int i = 0;
		do
		{
			*(sumParts + i) = sum % 100;
			i++;
		} while (sum /= 100);

		for (auto i = 0; i < digit; i++)
			sum += sumParts[i];
		delete[] sumParts;
		std::cout << sum % 10;
		return 0;
	}
	else
	{
		return -1;
	}
}
