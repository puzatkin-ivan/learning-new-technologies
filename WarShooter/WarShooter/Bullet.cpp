#include "stdafx.h"
#include "Bullet.h"

const sf::Color BULLET_COLOR = sf::Color::Magenta;

Bullet::Bullet(const sf::Vector2f & position, const sf::Vector2f & sizeBullet)
{
	m_body.setFillColor(BULLET_COLOR);
	m_body.setSize(sizeBullet);
	m_body.setPosition(position);
}

void Bullet::Update(float dt)
{
	(void)&dt;
}

void Bullet::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}
