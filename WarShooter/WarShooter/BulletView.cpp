#include "stdafx.h"
#include "BulletView.h"

BulletView::BulletView(CAssets & assets)
	:m_assets(assets)
{
	m_body.setPosition(BULLET_POSITION);
	SetTexture(m_assets.BLOCK_TEXTURE);
}

void BulletView::Update(float dt)
{
	(void)&dt;
}

void BulletView::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}

void BulletView::SetTexture(sf::Texture & texture)
{
	m_body.setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body.setTexture(texture);
}
