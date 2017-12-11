#include "stdafx.h"

#include "GameContext.h"

using json = nlohmann::json;

GameContext::GameContext(SAssets & assets)
	:m_assets(assets)
	,m_table(assets)
{
	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.BACKGROUND_TEXTURE);
}

void GameContext::Update(sf::View & view, const std::string & ip)
{
	UpdateBlocks(m_data.m_vectorBlocks);
	UpdatePlayers(m_data.m_vectorPlayers, view, ip);
	m_table.Update(m_listPlayers, view.getCenter(), ip);
}

bool GameContext::isClientDead() const
{
	return m_isDeadClient;
}

void GameContext::UpdateBlocks(const std::vector<Block> & vectorBlocks)
{
	if (m_blocks.empty())
	{
		for (auto & block : vectorBlocks)
		{
			m_blocks.push_back(std::make_unique<BlockView>(m_assets, block.getPosition()));
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
			if (playerObject.isDraw)
			{
				m_players[index]->SetParameters(playerObject);
				SetCenterView(view, m_players[index], ip);
				m_players[index]->Update();
				m_players[index]->SetOpportunityDrawing(true);
			}
			else
			{
				m_players[index]->SetOpportunityDrawing(false);
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
		m_players[index]->SetOpportunityDrawing(false);
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

		m_isDeadClient = player->GetIsDead();
	}
}

void GameContext::Draw(sf::RenderWindow & window, bool isDrawTable) const
{
	window.draw(m_background);
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

	if (isDrawTable)
	{
		m_table.Draw(window);
	}
}


void GameContext::ProcessInitMessage(const std::string & path)
{
	auto data = json::parse(path);

	for (auto & element : data[ARRAY_BLOCKS])
	{
		Block block;
		block.setPosition(sf::Vector2f(float(element[X]), float(element[Y])));
		m_data.m_vectorBlocks.push_back(block);
	}
	
	for (auto & element : data[ARRAY_PLAYERS])
	{
		Shooter player;
		InitParametersPlayer(element, player);
		m_data.m_vectorPlayers.push_back(player);
	}

	for (auto & element : data[ARRAY_BULLETS])
	{
		auto x = float(element[X]);
		auto y = float(element[Y]);
		auto position = sf::Vector2f(x, y);
		auto bullet = std::make_unique<BulletView>(m_assets, position);
		m_bullets.push_back(std::move(bullet));
	}
}

void GameContext::InitParametersPlayer(const nlohmann::basic_json<> & path, Shooter & player)
{
	
	player.position = sf::Vector2f(float(path[X]), float(path[Y]));
	player.health = path[HEALTH];
	player.direction = path[DIRECTION].get<std::string>();
	player.nickname = !path[NICKNAME].get<std::string>().empty() ? path[NICKNAME].get<std::string>() : "";
	player.playerId = path[PLAYER_ID].get<std::string>();
}

void GameContext::ProcessUpdateData(const std::string & path)
{
	auto data = json::parse(path);
	
	UpdateParametersBullets(data);
	UpdateParametersPlayers(data);
	UpdateParametersTable(data);
}

void GameContext::UpdateParametersBullets(const nlohmann::basic_json<> & data)
{
	size_t index = 0;
	for (auto & element : data[ARRAY_BULLETS])
	{
		auto position = sf::Vector2f(float(element[X]), float(element[Y]));

		if (index < m_bullets.size())
		{
			m_bullets[index]->SetPosition(position);
			m_bullets[index]->SetOpportunityDrawing(true);
		}
		else
		{
			auto bullet = std::make_unique<BulletView>(m_assets, position);
			bullet->SetOpportunityDrawing(true);
			m_bullets.push_back(std::move(bullet));
		}

		++index;
	}

	for (index; index < m_bullets.size(); ++index)
	{
		m_bullets[index]->SetOpportunityDrawing(false);
	}
}

void GameContext::UpdateParametersPlayers(const nlohmann::basic_json<> & data)
{
	size_t index = 0;
	for (auto & element : data[ARRAY_PLAYERS_FOR_DRAW])
	{
		if (index < m_data.m_vectorPlayers.size())
		{
			auto & player = m_data.m_vectorPlayers[index];
			InitPlayerDraw(element, player);
		}
		else if (!m_data.m_vectorPlayers.empty())
		{
			Shooter player;
			InitPlayerDraw(element, player);
			m_data.m_vectorPlayers.push_back(player);
		}

		++index;
	}
	for (index; index < m_data.m_vectorPlayers.size(); ++index)
	{
		 m_data.m_vectorPlayers[index].isDraw = false;
	}
}

void GameContext::InitPlayerDraw(const nlohmann::basic_json<> & path, Shooter & player)
{

	player.position = sf::Vector2f(float(path[X]), float(path[Y]));
	player.health = path[HEALTH];
	player.direction = path[DIRECTION].get<std::string>();
	player.nickname = path[NICKNAME].get<std::string>();
	player.playerId = path[PLAYER_ID].get<std::string>();
	player.isDraw = true;
}

void GameContext::UpdateParametersTable(const nlohmann::basic_json<> & data)
{
	size_t index = 0;
	for (auto & element : data[ARRAY_PLAYERS_FOR_TABLE])
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
		m_listPlayers[index].isDraw = false;
	}
}

void GameContext::InitPlayerTable(const nlohmann::basic_json<> & path, PlayerTable & player)
{
	player.playerId = path[PLAYER_ID].get<std::string>();
	player.nickname = path[NICKNAME].get<std::string>();
	player.isDead = path[IS_DEAD].get<bool>();
	player.killCount = path[KILL_COUNT].get<int>();
	player.score = path[SCORE].get<int>();
	player.deathCount = path[DEATH_COUNT].get<int>();
	player.isDraw = true;
}
