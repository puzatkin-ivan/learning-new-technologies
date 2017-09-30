#include <iostream>
#include <cmath>

struct rootEquation
{
public:
	float first = 0;
	float second = 0;
	int amount = 0;
};

rootEquation solve2(int a,  int b, int c) 
{
	float discriminant = pow(b, 2) - 4 * a * c;
	rootEquation root;

	if (discriminant > 0)
	{
		root.amount = 2;
	} else if (discriminant == 0) 
	{
		root.amount = 1;
	}

	switch (root.amount)
	{
	case 2:
		root.first = (-b + std::sqrt(discriminant)) / (2 * a);
		root.second = (-b - std::sqrt(discriminant)) / (2 * a);
			break;
	case 1:
		root.first = (-b) / (2 * a);
		root.second = root.first;
		break;
	}
	
	return root;
}

int main()
{
	int a, b, c;

	std::cin >> a >> b >> c;
	switch (solve2(a, b, c).amount)
	{
	case 2:
		std::cout << "First root: " << solve2(a, b, c).first << std::endl; 
		std::cout << "Second root: " << solve2(a, b, c).second << std::endl;
		break;
	case 1:
		std::cout << "Only root: " << solve2(a, b, c).first << std::endl;
		break;
	case 0:
		std::cout << "No real roots"<< std::endl;
		break;
	}
	return 0;
}