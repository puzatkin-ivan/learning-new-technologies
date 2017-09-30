#include <iostream>
#include <cmath>

int findFactorial(int number)
{
	if (number == 1)
	{
		return 1;
	}
	else
	{
		return findFactorial(number - 1) * number;
	}
}

int main() {
	int number;
	std::cin >> number;
	std::cout << findFactorial(number) << std::endl;
	return 0;
}