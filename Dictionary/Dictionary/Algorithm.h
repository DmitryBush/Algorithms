#pragma once
#include <iostream>
#include <string>

namespace Algorithm
{
	template <typename I, typename O>
	bool BinarySearch(const I& list, const O& item)
	{
		int low = 0;
		int high = static_cast<int>(list.size()) - 1;

		while (low <= high)
		{
			if (item == list.at((high + low) / 2))
				return true;
			else if (item < list.at((high + low) / 2))
				high--;
			else
				low++;
		}
		return false;
	}

	unsigned long long RecursiveFactorial(const short int& numb)
	{
		if (numb == 1 || numb == 0)
			return 1;
		else if (numb < 0)
			throw("Trying to find the factorial from negative number");
		else
			return numb * RecursiveFactorial(numb - 1);
	}

	unsigned long long Factorial(const short int& numb)
	{
		if (numb == 1 || numb == 0)
			return 1;
		else if (numb < 0)
			throw("Trying to find the factorial from negative number");

		unsigned long long factorial = 1;
		for (short int i = 2; i <= numb; i++)
			factorial *= i;
		return factorial;
	}


	template <typename IT, typename I>
	void QuickSort(I* list, IT left_limit, IT right_limit)
	{
		IT low = left_limit; IT high = right_limit;
		IT pivot = left_limit; std::advance(pivot, (std::distance(low, high)) / 2 + 1);
		do
		{
			while (*low < *pivot)
				std::advance(low, 1);
			while (*high > *pivot)
				std::advance(high, -1);
			if (low <= high)
			{
				std::swap(*low, *high);
				std::advance(low, 1); std::advance(high, -1);
			}
		} while (low < high);

		if (left_limit < high) QuickSort(list, left_limit, high);
		if (low < right_limit) QuickSort(list, low, right_limit);
	}

	void QuickSort(char* arr, int size)
	{
		int left_limit = 0, right_limit = size - 1;
		char pivot = arr[size / 2];
		do
		{
			while (arr[left_limit] < pivot)
				left_limit++;
			while (arr[right_limit] > pivot)
				right_limit--;
			if (left_limit <= right_limit)
			{
				char tmp = arr[left_limit];
				arr[left_limit] = arr[right_limit];
				arr[right_limit] = tmp;
				left_limit++; right_limit--;
			}
		} while (left_limit <= right_limit);

		if (right_limit > 0) QuickSort(arr, right_limit + 1);
		if (left_limit < size) QuickSort(&arr[left_limit], size - left_limit);
	}
}