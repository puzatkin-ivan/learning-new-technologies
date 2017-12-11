#include "stdafx.h"

#include "sheet.h"
#include "BlockView.h"

BlockView::BlockView(SAssets & assets, const sf::Vector2f & position)
	:m_assets(assets)
{
	m_body.setPosition(position);
	SetTexture(m_assets.BLOCK_TEXTURE);
}

void BlockView::SetTexture(sf::Texture & texture)
{
	m_body.setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body.setTexture(texture);
}

void BlockView::Update(float dt)
{
	(void)&dt;
}

void BlockView::Draw(sf::RenderWindow & window) const
{
	window.draw(m_body);
}
