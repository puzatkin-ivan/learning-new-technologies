#pragma once
#include "sheet.h"

class Bullet
{
public:
	Bullet(const sf::Vector2f & position, const sf::Vector2f & sizeBullet);

	void Update(float dt);
	void Draw(sf::RenderWindow & window);

private:
	sf::RectangleShape m_body;
};
