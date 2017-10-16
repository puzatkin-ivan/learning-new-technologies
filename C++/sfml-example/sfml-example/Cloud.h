#pragma once
#include <SFML/Graphics.hpp>

class Cloud
{
public:
	Cloud();
	void Draw(sf::RenderWindow & window);

private:
	sf::CircleShape cloud1;
	sf::CircleShape cloud2;
	sf::CircleShape cloud3;
};