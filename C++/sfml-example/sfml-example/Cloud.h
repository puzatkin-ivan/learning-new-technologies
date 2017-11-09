#pragma once
#include <SFML/Graphics.hpp>

class Cloud
{
public:
	Cloud();
	void Draw(sf::RenderWindow & window);

private:
	std::vector<sf::CircleShape> m_body;
};