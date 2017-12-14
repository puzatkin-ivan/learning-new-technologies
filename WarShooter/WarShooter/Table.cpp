#include "stdafx.h"

#include "sheet.h"
#include "Table.h"

namespace
{

static const auto BACKGROUND_COLOR = sf::Color({ 0, 0, 0, 179 });

static const auto LINE_COLOR = sf::Color({ 0, 230, 0 });

static const auto CHARACTER_SIZE = 24;

static const auto DELTA_LENGTH = 50.f;

static const auto TEXT_TITLE_NAME = "Players";

static const auto TEXT_TITLE_STATUS = "Status";

static const auto TEXT_TITLE_SCORE = "Score";

static const auto TEXT_TITLE_DEAD = "Dead";

static const auto DELTA_POSITION = sf::Vector2f({ 250, 0.f });

static const auto OFFSET_FOR_TITLE = sf::Vector2f({ 200.f, 20.f });

static const auto OFFSET_BY_Y_FOR_LINE = sf::Vector2f({ 0.f, 50.f });

}

Table::Table(SAssets & assets)
	:m_assets(assets)
{
	m_background.setSize(TABLE_SIZE);
	m_background.setFillColor(BACKGROUND_COLOR);

	m_line.setSize(LINE_TABLE_SIZE);
	m_line.setFillColor(LINE_COLOR);

	m_titlePlayers.setString(TEXT_TITLE_NAME);
	m_titlePlayers.setFont(m_assets.BREE_SERIF_FONT);
	m_titlePlayers.setCharacterSize(CHARACTER_SIZE);

	m_titleStatus.setString(TEXT_TITLE_STATUS);
	m_titleStatus.setFont(m_assets.BREE_SERIF_FONT);
	m_titleStatus.setCharacterSize(CHARACTER_SIZE);

	m_titleScore.setString(TEXT_TITLE_SCORE);
	m_titleScore.setFont(m_assets.BREE_SERIF_FONT);
	m_titleScore.setCharacterSize(CHARACTER_SIZE);

	m_titleDead.setString(TEXT_TITLE_DEAD);
	m_titleDead.setFont(m_assets.BREE_SERIF_FONT);
	m_titleDead.setCharacterSize(CHARACTER_SIZE);
}

void Table::Update(std::vector<PlayerTable> & listPlayer, const sf::Vector2f & viewPosition, const std::string & ip)
{
	SetPosition(viewPosition);
	size_t index = 0;
	for (auto player : listPlayer)
	{
		if (index < m_vectorPlayers.size())
		{	
			if (player.isDrawble)
			{
				UpdatePlayer(player, index, ip);
			}
			else
			{
				m_vectorPlayers[index]->SetOpportunityDrawble(false);
			}
		}
		else
		{
			AddPlayerForDraw(player, index, ip);
		}

		++index;
	}
}

void Table::AddPlayerForDraw(const PlayerTable & player, size_t index, const std::string & ip)
{
	auto playerForTable = std::make_unique<CPlayerTableView>(m_assets);

	playerForTable->SetContent(player, index, ip);
	m_vectorPlayers.push_back(std::move(playerForTable));
}

void Table::UpdatePlayer(const PlayerTable & player, size_t index, const std::string & ip)
{
	m_vectorPlayers[index]->SetContent(player, index, ip);
	m_vectorPlayers[index]->SetOpportunityDrawble(true);
}

void Table::Draw(sf::RenderWindow & window) const
{
	window.draw(m_background);
	window.draw(m_line);
	window.draw(m_titlePlayers);
	window.draw(m_titleStatus);
	window.draw(m_titleScore);
	window.draw(m_titleDead);

	for (const auto & player : m_vectorPlayers)
	{
		player->Draw(window);
	}
}

void Table::SetPosition(const sf::Vector2f & center)
{
	const sf::Vector2f position = center - 0.5f * TABLE_SIZE;
	const sf::Vector2f positionLine = position + OFFSET_BY_Y_FOR_LINE;
	const sf::Vector2f positionTitlePlayers = position + OFFSET_FOR_TITLE;
	const sf::Vector2f positionTitleStatus = positionTitlePlayers + DELTA_POSITION;
	const sf::Vector2f positionTitleScore = positionTitleStatus + DELTA_POSITION;
	const sf::Vector2f positionTitleDead = positionTitleScore + DELTA_POSITION;

	m_background.setPosition(position);
	m_line.setPosition(positionLine);

	m_titlePlayers.setPosition(positionTitlePlayers);
	m_titleStatus.setPosition(positionTitleStatus);
	m_titleScore.setPosition(positionTitleScore);
	m_titleDead.setPosition(positionTitleDead);

	for (size_t index = 0; index < m_vectorPlayers.size(); ++index)
	{
		m_vectorPlayers[index]->SetPositionX(m_titlePlayers.getPosition());
		const auto offsetY = float((index + 1) * DELTA_LENGTH) + m_titlePlayers.getPosition().y;
		m_vectorPlayers[index]->SetPositionY(sf::Vector2f(0,  offsetY));
	}
}
