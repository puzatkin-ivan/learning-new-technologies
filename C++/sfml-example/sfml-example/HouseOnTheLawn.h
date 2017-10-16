#pragma once
#include "Cloud.h"
#include "WindowHouse.h"

class HouseOnTheLawn
{
public:
	HouseOnTheLawn();

	void DrawLoop(sf::RenderWindow & window);
	
private:
	sf::RectangleShape sky;
	sf::RectangleShape lawn;
	sf::RectangleShape house;
	sf::ConvexShape roof;
	sf::RectangleShape chimney;
	WindowHouse windowsHouse;
	Cloud cloud;
};