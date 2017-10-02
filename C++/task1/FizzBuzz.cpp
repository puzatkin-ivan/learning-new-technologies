#include <iostream>

int main()
{
	for (int count = 0; count <= 100; ++count)
	{
		const int modOnThree = count % 3;
		const int modOnFive = count % 5;

		if (modOnThree == 0 && modOnFive == 0)
		{
			std::cout << "FizzBuzz" << std::endl;
		}
		else if (modOnThree == 0)
		{
			std::cout << "Fizz" << std::endl;
		}
		else if (modOnFive == 0)
		{
			std::cout << "Buzz" << std::endl;
		}
		else
		{
			std::cout << count << std::endl;
		}
	} 
	return 0;
}
