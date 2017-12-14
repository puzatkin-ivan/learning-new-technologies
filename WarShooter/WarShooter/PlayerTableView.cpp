#include "stdafx.h"

#include "PlayerTableView.h"

namespace
{

static const auto CLIENT_COLOR = sf::Color({ 159, 255, 34 });

static const auto ENEMY_COLOR = sf::Color({ 199, 159, 40 });

static const unsigned CHARACTER_SIZE = 24;

static const auto DEFAULT_POSITION = sf::Vector2f({ 0.f, 0.f });

static const auto DELTA_POSITION_BY_Y = sf::Vector2f({ 0.f, 50.f });

static const auto DELTA_POSITION_BY_X = sf::Vector2f({ 250.f, 0.f });

static const auto STATUS_ALIVE = "Alive";

static const auto STATUS_DEAD = "Dead";

}

CPlayerTableView::CPlayerTableView(SAssets & assets)
	:m_assets(assets)
{
	m_name.setFont(m_assets.BREE_SERIF_FONT);
	m_name.setCharacterSize(CHARACTER_SIZE);
	m_name.setPosition(DEFAULT_POSITION);

	m_status.setFont(m_assets.BREE_SERIF_FONT);
	m_status.setCharacterSize(CHARACTER_SIZE);
	m_name.setPosition(DEFAULT_POSITION);

	m_killCount.setFont(m_assets.BREE_SERIF_FONT);
	m_killCount.setCharacterSize(CHARACTER_SIZE);
	m_name.setPosition(DEFAULT_POSITION);

	m_deathCount.setFont(m_assets.BREE_SERIF_FONT);
	m_deathCount.setCharacterSize(CHARACTER_SIZE);
	m_name.setPosition(DEFAULT_POSITION);

	m_isOpportunityDrawing = true;
}

void CPlayerTableView::SetContent(const PlayerTable & player, size_t index, const std::string & ip)
{
	const auto offset = float(index + 1) * DELTA_POSITION_BY_Y;

	const sf::Color colorText = player.playerId == ip ? CLIENT_COLOR : ENEMY_COLOR;
	m_name.setFillColor(colorText);
	m_status.setFillColor(colorText);
	m_killCount.setFillColor(colorText);
	m_deathCount.setFillColor(colorText);

	std::string nicknamePlayer = std::to_string(index + 1) + ". " + player.nickname;
	m_name.setString(nicknamePlayer);

	std::string statusPlayer = player.isDead ? STATUS_DEAD : STATUS_ALIVE;
	m_status.setString(statusPlayer);

	std::string killCount = std::to_string(player.killCount);
	m_killCount.setString(killCount);

	std::string deathCount = std::to_string(player.deathCount);
	m_deathCount.setString(deathCount);
}

void CPlayerTableView::SetPositionX(const sf::Vector2f & position)
{
	m_name.setPosition(position);
	m_status.setPosition(m_name.getPosition() + DELTA_POSITION_BY_X);
	m_killCount.setPosition(m_status.getPosition() + DELTA_POSITION_BY_X);
	m_deathCount.setPosition(m_killCount.getPosition() + DELTA_POSITION_BY_X);
}

void CPlayerTableView::SetPositionY(const sf::Vector2f & position)
{
	m_name.setPosition(m_name.getPosition().x, position.y);
	m_status.setPosition(m_status.getPosition().x, position.y);
	m_killCount.setPosition(m_killCount.getPosition().x, position.y);
	m_deathCount.setPosition(m_deathCount.getPosition().x, position.y);
}

void CPlayerTableView::SetOpportunityDrawble(bool isOpportunityDrawing)
{
	m_isOpportunityDrawing = isOpportunityDrawing;
}

void CPlayerTableView::Draw(sf::RenderWindow & window) const
{
	if (m_isOpportunityDrawing)
	{
		window.draw(m_name);
		window.draw(m_status);
		window.draw(m_killCount);
		window.draw(m_deathCount);
	}
}
