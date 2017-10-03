#include "stdafx.h"
#include <iostream>

unsigned FindFactorial(unsigned number)
{
	unsigned factorial = 1;
	for (unsigned count = 1; count <= number; ++count)
	{
		factorial *= count;
	}

	return factorial;
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
