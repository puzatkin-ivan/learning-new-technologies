#include "stdafx.h"

#include "Block.h"


sf::Vector2f Block::getPosition() const
{
	return m_position;
}

void Block::setPosition(const sf::Vector2f & position)
{
	m_position = position;
}
