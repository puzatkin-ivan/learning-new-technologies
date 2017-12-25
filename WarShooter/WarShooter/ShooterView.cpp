#include "stdafx.h"

#include <cmath>

#include "sheet.h"
#include "ShooterView.h"

namespace
{

static const auto NO_DIRECTION_MOVE = 0.f;

static const auto SPEED = 200.f;

static const auto Up = "direction_up";

static const auto Down = "direction_down";

static const auto Left = "direction_left";

static const auto Right = "direction_right";

static const auto COLOR_NICKNAME = sf::Color({ 15, 21, 36 });

static const unsigned CHARACTER_SIZE = 30;

static const auto STYLE_TEXT_NICKNAME = sf::Text::Bold;

}

ShooterView::ShooterView(SAssets & assets, const Shooter & playerOfServer)
	:m_assets(assets)
{
	SetParameters(playerOfServer);
	SetTexture();
	m_isDrawable = true;
	m_nickname.setCharacterSize(CHARACTER_SIZE);
	m_nickname.setColor(COLOR_NICKNAME);
	m_nickname.setFont(m_assets.BREE_SERIF_FONT);
	m_nickname.setStyle(STYLE_TEXT_NICKNAME);
}

void ShooterView::SetTexture()
{
	sf::Texture & texture = m_assets.PLAYER_HUMAN_TEXTURE;
	if (m_numberTexture == int(PlayerTexture::Swat))
	{
		texture = m_assets.PLAYER_SWAT_TEXTURE;
	}
	else if (m_numberTexture == int(PlayerTexture::Knight))
	{
		texture = m_assets.PLAYER_KNIGHT_TEXTURE;
	}
	else if (m_numberTexture == int(PlayerTexture::Biker))
	{
		texture = m_assets.PLAYER_BIKER_TEXTURE;
	}
	m_body.setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body.setTexture(texture);
}

void ShooterView::Draw(sf::RenderWindow & window) const
{
	if (m_isDrawable)
	{
		window.draw(m_body);
		window.draw(m_nickname);
	}
}

void ShooterView::Update()
{
	if (m_direction == Right)
	{
		m_body.setRotation(90.f);
		const auto OFFSET = sf::Vector2f(float(m_body.getTexture()->getSize().x), 0.f);
		m_body.setPosition(m_body.getPosition() + OFFSET);
	}
	else if (m_direction == Left)
	{
		m_body.setRotation(-90.f);
		const auto OFFSET = sf::Vector2f(0.f, float(m_body.getTexture()->getSize().y));
		m_body.setPosition(m_body.getPosition() + OFFSET);
	}
	else if (m_direction == Up)
	{
		m_body.setRotation(0.f);
	}
	else if (m_direction == Down)
	{
		m_body.setRotation(180.f);
		const auto OFFSET = sf::Vector2f(m_body.getTexture()->getSize());
		m_body.setPosition(m_body.getPosition() + OFFSET);
	}
}

bool ShooterView::IsDead() const
{
	return m_isDead;
}

void ShooterView::SetOpportunityDrawable(bool isDrawable)
{
	m_isDrawable = isDrawable;
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
	m_body.setPosition(playerOfServer.position - 0.5f * sf::Vector2f(m_assets.PLAYER_SWAT_TEXTURE.getSize()));
	m_direction = playerOfServer.direction;
	m_health = playerOfServer.health;
	m_ip = playerOfServer.playerId;

	m_nickname.setString(playerOfServer.nickname);
	const auto AVERAGE_CHARACTER_WIDTH = 15;
	const auto offsetX = float(std::ceil((AVERAGE_CHARACTER_WIDTH * m_nickname.getString().getSize()) / 2));
	const auto xText = playerOfServer.position.x - offsetX;
	const auto OFFSET_Y = 35.f;
	const auto yText = m_body.getPosition().y - OFFSET_Y;
	m_nickname.setPosition(sf::Vector2f(xText, yText));
	
	m_numberTexture = playerOfServer.numberTexture;
	m_isDead = playerOfServer.isDead;
}

unsigned ShooterView::GetHealth() const
{
	return m_health;
}
