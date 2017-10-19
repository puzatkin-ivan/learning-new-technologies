#pragma once
#include "sheet.h"

class Block
{
public:
	Block(const sf::Vector2f & position, const sf::Vector2f & sizeBlock);
	
	void Draw(sf::RenderWindow & window);
private:
	sf::RectangleShape m_body;
};
