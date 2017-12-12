#include "stdafx.h"

#include "ShooterView.h"

namespace
{

static const auto NO_DIRECTION_MOVE = 0.f;

static const auto SPEED = 200.f;

static const auto Up = "direction_up";

static const auto Down = "direction_down";

static const auto Left = "direction_left";

static const auto Right = "direction_right";

}

ShooterView::ShooterView(SAssets & assets, const Shooter & playerOfServer)
	:m_assets(assets)
{
	SetParameters(playerOfServer);
	SetTexture(m_assets.PLAYER_TEXTURE);
	m_isDraw = true;
}

void ShooterView::SetTexture(const sf::Texture & texture)
{
	m_body.setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body.setTexture(texture);
}

void ShooterView::Draw(sf::RenderWindow & window) const
{
	if (m_isDraw)
	{
		window.draw(m_body);
	}
}

void ShooterView::Update()
{
	if (m_direction == Right)
	{
		m_body.setRotation(90.f);
		const auto offset = sf::Vector2f(float(m_body.getTexture()->getSize().x), 0.f);
		m_body.setPosition(m_body.getPosition() + offset);
	}
	else if (m_direction == Left)
	{
		m_body.setRotation(-90.f);
		const auto offset = sf::Vector2f(0.f, float(m_body.getTexture()->getSize().y));
		m_body.setPosition(m_body.getPosition() + offset);
	}
	else if (m_direction == Up)
	{
		m_body.setRotation(0.f);
	}
	else if (m_direction == Down)
	{
		m_body.setRotation(180.f);
		const auto offset = sf::Vector2f(m_body.getTexture()->getSize());
		m_body.setPosition(m_body.getPosition() + offset);
	}
}

bool ShooterView::GetInformationAboutHealth() const
{
	return m_health == 0;
}

void ShooterView::SetOpportunityDrawing(bool isDraw)
{
	m_isDraw = isDraw;
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
	m_body.setPosition(playerOfServer.position - 0.5f * sf::Vector2f(m_assets.PLAYER_TEXTURE.getSize()));
	m_direction = playerOfServer.direction;
	m_health = playerOfServer.health;
	m_ip = playerOfServer.playerId;
	m_nickname = playerOfServer.nickname;
}
