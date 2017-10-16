#pragma once
#include <SFML/Graphics.hpp>

class WindowHouse
{
public:
	WindowHouse();
	void Draw(sf::RenderWindow & window);
private:
	float x;
	float y;
	float width;
	float height;
	sf::Color WHITE = sf::Color(255, 255, 255);

	sf::RectangleShape windowHouse1;
	sf::RectangleShape windowHouse2;
	sf::RectangleShape windowHouse3;
};