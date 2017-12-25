#include "stdafx.h"

#include "GameContext.h"

using json = nlohmann::json;

namespace
{

static const size_t AMOUNT_BLOCKS = 100;

static const auto POSITION_MARGIN_UP = sf::Vector2f(-30.f, -30.f);

static const auto POSITION_MARGIN_LEFT = sf::Vector2f(-30.f, 0.f);

static const auto POSITION_MARGIN_DOWN = sf::Vector2f(0.f, 1800.f);

static const auto POSITION_MARGIN_RIGHT = sf::Vector2f(4500.f, 0.f);

static const auto COLOR_MARGIN = sf::Color({ 127, 116, 63 });

static const auto SIZE_MARGIN_UP_DOWN = sf::Vector2f(4500.f, 30.f);

static const auto SIZE_MARGIN_LEFT_RIGHT = sf::Vector2f(30.f, 1830.f);

}

GameContext::GameContext(SAssets & assets)
	:m_assets(assets)
	,m_table(assets)
	,m_healthPoints(assets)
{
	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.BACKGROUND_TEXTURE);

	m_isClientDead = false;
	m_blocks.reserve(AMOUNT_BLOCKS);
	InitMarginField();
}

void GameContext::Update(sf::View & view, const std::string & ip)
{
	UpdateBlocks(m_data.blocks);
	UpdatePlayers(m_data.players, view, ip);
	m_table.Update(m_listPlayers, view.getCenter(), ip);
	m_healthPoints.SetPosition(view.getCenter());
}

bool GameContext::IsClientDead() const
{
	return m_isClientDead;
}

void GameContext::UpdateBlocks(const std::vector<Block> & vectorBlocks)
{
	if (m_blocks.empty())
	{
		for (auto & block : vectorBlocks)
		{
			m_blocks.push_back(std::make_unique<BlockView>(m_assets, block.position));
		}
	}
}

void GameContext::UpdatePlayers(const std::vector<Shooter> & vectorPlayers, sf::View & view, const std::string & ip)
{
	size_t index = 0;
	for (auto & playerObject : vectorPlayers)
	{
		if (index < m_players.size())
		{
			if (playerObject.isDrawable)
			{
				m_players[index]->SetParameters(playerObject);
				SetCenterView(view, m_players[index], ip);
				m_players[index]->Update();
				m_players[index]->SetOpportunityDrawable(true);
			}
			else
			{
				m_players[index]->SetOpportunityDrawable(false);
			}
		}
		else
		{
			auto player = std::make_unique<ShooterView>(m_assets, playerObject);
			SetCenterView(view, player, ip);
			player->Update();
			m_players.push_back(std::move(player));
		}

		++index;
	}
	
	for (index; index < m_players.size(); ++index)
	{
		m_players[index]->SetOpportunityDrawable(false);
	}
}

void GameContext::SetCenterView(sf::View & view, const std::unique_ptr<ShooterView> & player, const std::string & ip)
{
	if (player->GetIp() == ip)
	{
		const sf::Vector2f playerPosition = player->GetPosition() + 0.5f * player->GetSize();
		view.setCenter(playerPosition);

		const auto newPositionBackground = playerPosition - 0.5f * sf::Vector2f(WINDOW_SIZE);
		m_background.setPosition(newPositionBackground);

		m_isClientDead = player->IsDead();

		m_healthPoints.SetHealtsPoints(player->GetHealth());
	}
}

void GameContext::Draw(sf::RenderWindow & window, bool isOpportunityDrawableTable) const
{
	window.draw(m_background);
	for (const auto margin : m_marginField)
	{
		window.draw(margin);
	}
	for (const auto & bullet : m_bullets)
	{
		bullet->Draw(window);
	}
	for (const auto & block : m_blocks)
	{
		block->Draw(window);
	}
	for (const auto & player : m_players)
	{
		player->Draw(window);
	}

	if (isOpportunityDrawableTable)
	{
		m_table.Draw(window);
	}

	m_healthPoints.Draw(window);
}

void GameContext::ProcessInitMessage(const std::string & path)
{
	const auto data = json::parse(path);
		
	for (const auto & element : data[ARRAY_PLAYERS])
	{
		Shooter player;
		InitParametersPlayer(element, player);
		m_data.players.push_back(player);
	}

	for (const auto & element : data[ARRAY_BULLETS])
	{
		const auto position = sf::Vector2f(float(element[X]), float(element[Y]));
		auto bullet = std::make_unique<BulletView>(m_assets, position);
		m_bullets.push_back(std::move(bullet));
	}
	
	m_data.blocks.reserve(AMOUNT_BLOCKS);

	for (const auto & element : data[ARRAY_BLOCKS])
	{
		Block block;
		block.position = sf::Vector2f(float(element[X]), float(element[Y]));
		m_data.blocks.push_back(block);
	}
}

void GameContext::ProcessUpdateData(const std::string & path)
{
	const auto data = json::parse(path);
	
	UpdateParametersBullets(data);
	UpdateParametersPlayers(data);
	UpdateParametersTable(data);
}

void GameContext::UpdateParametersBullets(const nlohmann::basic_json<> & data)
{
	size_t index = 0;
	for (const auto & element : data[ARRAY_BULLETS])
	{
		const auto position = sf::Vector2f(float(element[X]), float(element[Y]));

		if (index < m_bullets.size())
		{
			m_bullets[index]->SetPosition(position);
			m_bullets[index]->SetOpportunityDrawable(true);
		}
		else
		{
			auto bullet = std::make_unique<BulletView>(m_assets, position);
			bullet->SetOpportunityDrawable(true);
			m_bullets.push_back(std::move(bullet));
		}

		++index;
	}

	for (index; index < m_bullets.size(); ++index)
	{
		m_bullets[index]->SetOpportunityDrawable(false);
	}
}

void GameContext::UpdateParametersPlayers(const nlohmann::basic_json<> & data)
{
	size_t index = 0;
	for (const auto & element : data[ARRAY_PLAYERS_FOR_DRAW])
	{
		if (index < m_data.players.size())
		{
			auto & player = m_data.players[index];
			InitParametersPlayer(element, player);
		}
		else if (!m_data.players.empty())
		{
			Shooter player;
			InitParametersPlayer(element, player);
			m_data.players.push_back(player);
		}

		++index;
	}

	for (index; index < m_data.players.size(); ++index)
	{
		 m_data.players[index].isDrawable = false;
	}
}

void GameContext::InitParametersPlayer(const nlohmann::basic_json<> & path, Shooter & player)
{
	player.position = sf::Vector2f(float(path[X]), float(path[Y]));
	player.health = path[HEALTH];
	player.direction = path[DIRECTION].get<std::string>();
	player.nickname = !path[NICKNAME].get<std::string>().empty() ? path[NICKNAME].get<std::string>() : "";
	player.playerId = path[PLAYER_ID].get<std::string>();
	player.numberTexture = path[NUMBER_TEXTURE].get<int>();
	player.isDead = path[IS_DEAD].get<bool>();
	player.isDrawable = true;
}

void GameContext::UpdateParametersTable(const nlohmann::basic_json<> & data)
{
	size_t index = 0;
	for (const auto & element : data[ARRAY_PLAYERS_FOR_TABLE])
	{
		if (index < m_listPlayers.size())
		{
			auto & player = m_listPlayers[index];
			InitPlayerTable(element, player);
		}
		else 
		{
			PlayerTable newPlayer;
			InitPlayerTable(element, newPlayer);
			m_listPlayers.push_back(newPlayer);
		}

		++index;
	}

	for (index; index < m_listPlayers.size(); ++index)
	{
		m_listPlayers[index].isDrawable = false;
	}
}

void GameContext::InitPlayerTable(const nlohmann::basic_json<> & path, PlayerTable & player)
{
	player.playerId = path[PLAYER_ID].get<std::string>();
	player.nickname = path[NICKNAME].get<std::string>();
	player.isDead = path[IS_DEAD].get<bool>();
	player.killCount = path[KILL_COUNT].get<int>();
	player.deathCount = path[DEATH_COUNT].get<int>();
	player.isDrawable = true;
}

void GameContext::Clear()
{
	m_data.Clear();
	m_blocks.clear();
	m_bullets.clear();
	m_players.clear();
	m_listPlayers.clear();
}

void GameContext::InitMarginField()
{
	sf::RectangleShape margin(POSITION_MARGIN_UP);
	margin.setFillColor(COLOR_MARGIN);
	margin.setSize(SIZE_MARGIN_UP_DOWN);
	m_marginField.push_back(margin);

	margin.setPosition(POSITION_MARGIN_DOWN);
	m_marginField.push_back(margin);

	margin.setPosition(POSITION_MARGIN_LEFT);
	margin.setSize(SIZE_MARGIN_LEFT_RIGHT);
	m_marginField.push_back(margin);

	margin.setPosition(POSITION_MARGIN_RIGHT);
	m_marginField.push_back(margin);
}
