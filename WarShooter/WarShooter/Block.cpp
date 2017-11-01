#include "stdafx.h"
#include "sheet.h"
#include "Block.h"

Block::Block(CAssets & assets, const sf::Vector2f & position)
	:m_assets(assets)
{
	m_body.setPosition(position);
	SetTexture(m_assets.BLOCK_TEXTURE);
}

void Block::SetTexture(sf::Texture & texture)
{
	m_body.setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body.setTexture(texture);
}

void Block::Update(float dt)
{
	(void)&dt;
}

void Block::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}
