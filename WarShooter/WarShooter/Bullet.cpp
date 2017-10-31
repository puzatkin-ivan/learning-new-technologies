#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(CAssets & assets)
	:m_assets(assets)
{
	m_body.setPosition(BLOCK_POSITION);
	SetTexture(m_assets.BLOCK_TEXTURE);
}

void Bullet::Update(float dt)
{
	(void)&dt;
}

void Bullet::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}

void Bullet::SetTexture(sf::Texture & texture)
{
	m_body.setTextureRect(sf::IntRect(BULLET_POSITION.x, BULLET_POSITION.y, int(texture.getSize().x), int(texture.getSize().y)));
	m_body.setTexture(texture);
}
