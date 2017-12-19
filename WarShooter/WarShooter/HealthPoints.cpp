#include "stdafx.h"

#include "sheet.h"
#include "HealthPoints.h"

namespace
{

static const unsigned CHARACTER_SIZE = 50;

static const auto COLOR_TEXT = sf::Color(107, 0, 0);

}

CHealthPoints::CHealthPoints(SAssets & assets)
	:m_assets(assets)
{
	m_redCross.setTextureRect(sf::IntRect(0, 0, int(m_assets.RED_CROSS.getSize().x), int(m_assets.RED_CROSS.getSize().y)));
	m_redCross.setTexture(m_assets.RED_CROSS);

	m_healthPoints.setCharacterSize(CHARACTER_SIZE);
	m_healthPoints.setColor(COLOR_TEXT);
	m_healthPoints.setFont(m_assets.BREE_SERIF_FONT);
}

void CHealthPoints::SetPosition(const sf::Vector2f & position)
{
	const auto positionHealthPoints = position - 0.5f * sf::Vector2f(WINDOW_SIZE);

	m_redCross.setPosition(positionHealthPoints);
	const auto offsetX = float(m_redCross.getTexture()->getSize().x);
	m_healthPoints.setPosition(positionHealthPoints + sf::Vector2f(offsetX, 0.f));
}

void CHealthPoints::SetHealtsPoints(unsigned health)
{
	const std::string valueHealth = std::to_string(health);
	m_healthPoints.setString(valueHealth);
}

void CHealthPoints::Draw(sf::RenderWindow & window) const
{
	window.draw(m_redCross);
	window.draw(m_healthPoints);
}