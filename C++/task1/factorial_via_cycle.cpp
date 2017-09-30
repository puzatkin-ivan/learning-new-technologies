#include <iostream>
#include <cmath>

int findFactorial(int number)
{
	int factorial = 1;
	for (int count = 1; count <= number; ++count)
	{
		factorial *= count;
	}

	return factorial;
}

int main() {
	int number;
	std::cin >> number;
	std::cout << findFactorial(number) << std::endl;
	return 0;
}