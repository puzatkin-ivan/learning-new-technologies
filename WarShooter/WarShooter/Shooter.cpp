#include "stdafx.h"
#include "Shooter.h"

const auto NO_DIRECTION_MOVE = 0.f;
const auto SPEED = 200.f;

Shooter::Shooter(CAssets & assets, const PlayerForDraw & playerOfServer)
	:m_assets(assets)
{
	SetParameters(playerOfServer);
	SetTexture(m_assets.PLAYER_TEXTURE);
}

void Shooter::SetTexture(const sf::Texture & texture)
{
	m_body.setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body.setTexture(texture);
}

void Shooter::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}

void Shooter::Update()
{
	
}

sf::Vector2f Shooter::GetPosition() const
{
	return m_body.getPosition();
}

std::string Shooter::GetIp() const
{
	return m_ip;
}

sf::Vector2f Shooter::GetSize() const
{
	return sf::Vector2f(m_body.getTexture()->getSize());
}

void Shooter::SetParameters(const PlayerForDraw & playerOfServer)
{
	m_body.setPosition(playerOfServer.position);
	m_direction = playerOfServer.direction;
	m_health = playerOfServer.health;
	m_ip = playerOfServer.playerId;
	m_nickname = playerOfServer.nickname;
}
