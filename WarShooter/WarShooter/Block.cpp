#include "stdafx.h"
#include "Block.h"

const sf::Color BLOCK_COLOR = sf::Color::Black;

Block::Block(const sf::Vector2f & position, const sf::Vector2f & sizeBlock)
{
	m_body.setFillColor(BLOCK_COLOR);
	m_body.setSize(sizeBlock);
	m_body.setPosition(position);
}

void Block::Update(float dt)
{

}

void Block::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}
