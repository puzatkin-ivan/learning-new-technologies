#include "stdafx.h"
#include "ShooterView.h"

const auto NO_DIRECTION_MOVE = 0.f;
const auto SPEED = 200.f;

ShooterView::ShooterView(CAssets & assets, const Shooter & playerOfServer)
	:m_assets(assets)
{
	SetParameters(playerOfServer);
	SetTexture(m_assets.PLAYER_TEXTURE);
}

void ShooterView::SetTexture(const sf::Texture & texture)
{
	m_body.setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body.setTexture(texture);
}

void ShooterView::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}

void ShooterView::Update()
{
	
}

sf::Vector2f ShooterView::GetPosition() const
{
	return m_body.getPosition();
}

std::string ShooterView::GetIp() const
{
	return m_ip;
}

sf::Vector2f ShooterView::GetSize() const
{
	return sf::Vector2f(m_body.getTexture()->getSize());
}

void ShooterView::SetParameters(const Shooter & playerOfServer)
{
	m_body.setPosition(playerOfServer.position);
	m_direction = playerOfServer.direction;
	m_health = playerOfServer.health;
	m_ip = playerOfServer.playerId;
	m_nickname = playerOfServer.nickname;
}
