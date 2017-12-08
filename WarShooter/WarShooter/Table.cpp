#include "stdafx.h"
#include "sheet.h"
#include "Table.h"

namespace
{
	static const auto DEFAULT_SCORE = -1;
	static const auto COLOR_CLIENT = sf::Color({ 159, 255, 34 });
	static const auto COLOR_ENEMY = sf::Color({ 199, 159, 40 });
}

Table::Table(CAssets & assets)
	:m_assets(assets)
{
	m_background.setSize(TABLE_SIZE);
	m_background.setFillColor(sf::Color({ 0, 0, 0, 179}));

	m_line.setSize(LINE_TABLE_SIZE);
	m_line.setFillColor(sf::Color({ 0, 230, 0 }));

	m_titlePlyers.setString("Players");
	m_titlePlyers.setFont(m_assets.CRETE_ROUND_FONT);
	m_titlePlyers.setCharacterSize(24);

	m_titleStatus.setString("Status");
	m_titleStatus.setFont(m_assets.CRETE_ROUND_FONT);
	m_titleStatus.setCharacterSize(24);

	m_titleScore.setString("Score");
	m_titleScore.setFont(m_assets.CRETE_ROUND_FONT);
	m_titleScore.setCharacterSize(24);

	m_titleDead.setString("Dead");
	m_titleDead.setFont(m_assets.CRETE_ROUND_FONT);
	m_titleDead.setCharacterSize(24);
}

void Table::Update(std::vector<PlayerTable> & listPlayer, const sf::Vector2f & viewPosition, const std::string & ip)
{
	SetPosition(viewPosition);
	size_t index = 0;
	if (m_columnPlayers.empty())
	{
		for (auto player : listPlayer)
		{
			AddPlayerForDraw(player, index, ip);
			++index;
		}
	}
	else
	{
		for (auto player : listPlayer)
		{
			if (index < m_columnPlayers.size())
			{			
				UpdatePlayer(player, index, ip);
				++index;
			}
			else
			{
				AddPlayerForDraw(player, index, ip);
				++index;
			}
		}
	}
}

void Table::AddPlayerForDraw(const PlayerTable & player, size_t index, const std::string & ip)
{
	const auto offset = float(index + 1) * sf::Vector2f({ 0.f, 50.f });

	sf::Text temp;
	temp.setFont(m_assets.CRETE_ROUND_FONT);
	temp.setCharacterSize(24);

	const sf::Color colorText = player.playerId == ip ? COLOR_CLIENT : COLOR_ENEMY;
	temp.setFillColor(colorText);

	std::string nicknamePlayer = std::to_string(index + 1) + ". " + player.nickname;
	temp.setString(nicknamePlayer);
	temp.setPosition(m_titlePlyers.getPosition() + offset);
	m_columnPlayers.push_back(temp);


	std::string statusPlayer = player.isDead ? "Dead" : "Alive";
	temp.setString(statusPlayer);
	temp.setPosition(m_titleStatus.getPosition() + offset);
	m_columnStatus.push_back(temp);

	std::string score = std::to_string(player.killCount);
	temp.setString(score);
	temp.setPosition(m_titleScore.getPosition() + offset);
	m_columnScore.push_back(temp);

	std::string killCount = std::to_string(player.deathCount);
	temp.setString(killCount);
	temp.setPosition(m_titleDead.getPosition() + offset);
	m_columnDead.push_back(temp);
}

void Table::UpdatePlayer(const PlayerTable & player, size_t index, const std::string & ip)
{
	const auto offset = float(index + 1) * sf::Vector2f({ 0.f, 50.f });
	
	const sf::Color colorText = player.playerId == ip ? COLOR_CLIENT : COLOR_ENEMY;
	auto & itemPlayers = m_columnPlayers[index];
	std::string temp1 = std::to_string(index + 1) + ". " + player.nickname;
	itemPlayers.setString(temp1);
	itemPlayers.setPosition(m_titlePlyers.getPosition() + offset);
	itemPlayers.setFillColor(colorText);

	auto & itemStatus = m_columnStatus[index];
	temp1 = player.isDead ? "Dead" : "Alive";
	itemStatus.setString(temp1);
	itemStatus.setPosition(m_titleStatus.getPosition() + offset);
	itemStatus.setFillColor(colorText);

	auto & itemScore = m_columnScore[index];
	std::string score = std::to_string(player.killCount);
	itemScore.setString(score);
	itemScore.setPosition(m_titleScore.getPosition() + offset);
	itemScore.setFillColor(colorText);

	auto & itemDead = m_columnDead[index];
	std::string killCount = std::to_string(player.deathCount);
	itemDead.setString(killCount);
	itemDead.setPosition(m_titleDead.getPosition() + offset);
	itemDead.setFillColor(colorText);
}

void Table::Draw(sf::RenderWindow & window)
{
	window.draw(m_background);
	window.draw(m_line);
	window.draw(m_titlePlyers);
	window.draw(m_titleStatus);
	window.draw(m_titleScore);
	window.draw(m_titleDead);

	for (auto item : m_columnPlayers)
	{
		window.draw(item);
	}
	for (auto item : m_columnStatus)
	{
		window.draw(item);
	}
	for (auto item : m_columnScore)
	{
		window.draw(item);
	}
	for (auto item : m_columnDead)
	{
		window.draw(item);
	}
}

void Table::SetPosition(const sf::Vector2f & center)
{
	const sf::Vector2f position = center - 0.5f * TABLE_SIZE;
	const sf::Vector2f positionLine = position + sf::Vector2f({ 0.f, 50.f });
	const sf::Vector2f positionTitlePlayers = position + sf::Vector2f({ 200.f, 20.f });
	const sf::Vector2f positionTitleStatus = positionTitlePlayers + sf::Vector2f({ 250, 0.f });
	const sf::Vector2f positionTitleScore = positionTitleStatus + sf::Vector2f({ 250, 0.f });
	const sf::Vector2f positionTitleDead = positionTitleScore + sf::Vector2f({ 250, 0.f });

	m_background.setPosition(position);
	m_line.setPosition(positionLine);
	m_titlePlyers.setPosition(positionTitlePlayers);
	m_titleStatus.setPosition(positionTitleStatus);
	m_titleScore.setPosition(positionTitleScore);
	m_titleDead.setPosition(positionTitleDead);
}
