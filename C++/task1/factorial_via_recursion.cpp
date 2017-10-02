#include <iostream>

unsigned FindFactorial(int number)
{
	return number == 1 ? 1 : FindFactorial(number - 1) * number;
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
