#include <iostream>
#include <cmath>

struct RootEquation
{
public:
	float first = 0;
	float second = 0;
	int amount = 0;
};

RootEquation Solve2(int a,  int b, int c) 
{
	const float discriminant = pow(b, 2) - 4 * a * c;
	RootEquation root;

	if (discriminant > 0)
	{
		root.amount = 2;
		root.first = (-b + std::sqrt(discriminant)) / (2 * a);
		root.second = (-b - std::sqrt(discriminant)) / (2 * a);
	} 
	else if (discriminant == 0) 
	{
		root.amount = 1;
		root.first = -b / (2 * a);
	}
	
	return root;
}

int main()
{
	int a, b, c;
	std::cout << "Coefficient A: ";
	std::cin >> a;
	std::cout << "Coefficient B: ";
	std::cin >> b;
	std::cout << "Coefficient C: ";
	std::cin >> c;
	std::cout << std::endl;

	if (a != 0)
	{
		const RootEquation decision = Solve2(a, b, c);

		switch (decision.amount)
		{
		case 2:
			std::cout << "First root: " << decision.first << std::endl;
			std::cout << "Second root: " << decision.second << std::endl;
			break;
		case 1:
			std::cout << "Only root: " << decision.first << std::endl;
			break;
		case 0:
			std::cout << "No real roots" << std::endl;
			break;
		}
	}
	else
	{
		std::cout << "The equation is not square" << std::endl;
	}
	return 0;
}
