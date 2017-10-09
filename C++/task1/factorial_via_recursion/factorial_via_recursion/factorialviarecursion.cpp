#include "stdafx.h"
#include <iostream>

unsigned FindFactorial(unsigned number)
{
	return (number != 0) ? (FindFactorial(number - 1) * number) : 1;
}

int main()
{
	int number;
	std::cin >> number;

	if (number >= 0)
	{
		std::cout << FindFactorial(number) << std::endl;
	}
	else
	{
		std::cout << "This number is negative" << std::endl;
	}

	return 0;
}
