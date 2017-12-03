#include "stdafx.h"

#include "GameContext.h"
#include <iostream>

using json = nlohmann::json;

GameContext::GameContext(CAssets & assets)
	:m_assets(assets)
{
	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.BACKGROUND_TEXTURE);
}

void GameContext::Update(sf::View & view, const std::string & ip)
{
	UpdateBlocks(m_data.m_vectorBlocks);
	UpdateBullets(m_data.m_vectorBullets);
	UpdatePlayers(m_data.m_vectorPlayers, view, ip);
}

bool GameContext::isClientDead() const
{
	return isDeadClient;
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

void GameContext::UpdateBullets(const std::vector<Bullet> & vectorBullets)
{
	(void)&vectorBullets;
}

void GameContext::UpdatePlayers(const std::vector<Shooter> & vectorPlayers, sf::View & view, const std::string & ip)
{
	if (m_players.empty())
	{
		for (auto & playerObject : vectorPlayers)
		{
			auto player = std::make_unique<ShooterView>(m_assets, playerObject);			
			if (player->GetIp() == ip)
			{
				const sf::Vector2f playerPosition = player->GetPosition() + 0.5f * player->GetSize();
				view.setCenter(playerPosition);

				const auto newPositionBackground = playerPosition - 0.5f * sf::Vector2f(WINDOW_SIZE);
				m_background.setPosition(newPositionBackground);
				isDeadClient = player->GetIsDead();
			}
			player->Update();
			m_players.push_back(std::move(player));
		}
	}
	else
	{
		size_t index = 0;
		for (auto & playerObject : vectorPlayers)
		{
			if (index < m_players.size())
			{
				m_players[index]->SetParameters(playerObject);
				if (m_players[index]->GetIp() == ip)
				{
					const sf::Vector2f playerPosition = m_players[index]->GetPosition() + 0.5f * m_players[index]->GetSize();
					view.setCenter(playerPosition);

					const auto newPositionBackground = playerPosition - 0.5f * sf::Vector2f(WINDOW_SIZE);
					m_background.setPosition(newPositionBackground);
					isDeadClient = m_players[index]->GetIsDead();
				}
				m_players[index]->Update();
				m_players[index]->SetIsDraw(true);

				++index;
			}
			else
			{
				auto player = std::make_unique<ShooterView>(m_assets, playerObject);
				player->Update();
				m_players.push_back(std::move(player));
			}
		}

		if (index < m_players.size())
		{
			for (index; index < m_players.size(); ++index)
			{
				m_players[index]->SetIsDraw(false);
			}
		}
	}
}

void GameContext::Draw(sf::RenderWindow & window)
{
	window.draw(m_background);
	for (auto & bullet : m_bullets)
	{
		if (bullet->GetIsDraw())
		{
			bullet->Draw(window);
		}
	}
	for (auto & block : m_blocks)
	{
		block->Draw(window);
	}
	for (auto & player : m_players)
	{
		if (player->GetIsDraw())
		{
			player->Draw(window);
		}
	}
}


void GameContext::ProcessInitMessage(const std::string & path)
{
	auto data = json::parse(path);
	for (auto & element : data["blocks"])
	{
		Block block;
		block.setPosition(sf::Vector2f(float(element["x"]), float(element["y"])));
		m_data.m_vectorBlocks.push_back(block);
	}
	
	m_data.m_vectorPlayers.clear();
	for (auto & element : data["players"])
	{
		Shooter player;
		player.position = sf::Vector2f(float(element["x"]), float(element["y"]));
		player.health = element["health"];
		player.direction = element["direction"].get<std::string>();
		player.nickname = "";
		player.playerId = element["playerId"].get<std::string>();
		m_data.m_vectorPlayers.push_back(player);
	}

	for (auto & element : data["bullets"])
	{
		auto x = float(element["x"]);
		auto y = float(element["y"]);
		auto position = sf::Vector2f(x, y);
		auto bullet = std::make_unique<BulletView>(m_assets, position);
		m_bullets.push_back(std::move(bullet));
	}
}

void GameContext::ProcessUpdateData(const std::string & path)
{
	auto data = json::parse(path);
	if (m_bullets.empty())
	{
		for (auto & element : data["bullets"])
		{
			auto x = float(element["x"]);
			auto y = float(element["y"]);
			auto position = sf::Vector2f(x, y);
			auto bullet = std::make_unique<BulletView>(m_assets, position);
			m_bullets.push_back(std::move(bullet));
		}
	}
	else 
	{
		size_t index = 0;
		for (auto & element : data["bullets"])
		{
			auto x = float(element["x"]);
			auto y = float(element["y"]);
			auto position = sf::Vector2f(x, y);
			if (index < m_bullets.size())
			{
				m_bullets[index]->SetPosition(position);
				m_bullets[index]->SetIsDraw(true);
				++index;
			}
			else
			{
				auto bullet = std::make_unique<BulletView>(m_assets, position);
				bullet->SetIsDraw(true);
				m_bullets.push_back(std::move(bullet));
			}
		}
		if (index < m_bullets.size())
		{
			for (index; index <= m_bullets.size() - 1; ++index)
			{
				m_bullets[index]->SetIsDraw(false);
			}
		}
	}

	if (m_data.m_vectorPlayers.empty())
	{
		for (auto & element : data["playersForDraw"])
		{
			Shooter player;
			player.position = sf::Vector2f(float(element["x"]), float(element["y"]));
			player.health = element["health"];
			player.direction = element["direction"].get<std::string>();
			player.nickname = "";
			player.playerId = element["playerId"].get<std::string>();
			m_data.m_vectorPlayers.push_back(player);
		}
	}
	else
	{
		size_t index = 0;
		for (auto & element : data["playersForDraw"])
		{
			if (index < m_data.m_vectorPlayers.size())
			{
				auto & player = m_data.m_vectorPlayers[index];
				player.position = sf::Vector2f(float(element["x"]), float(element["y"]));
				player.health = element["health"];
				player.direction = element["direction"].get<std::string>();
				player.nickname = "";
				player.playerId = element["playerId"].get<std::string>();
				++index;
			}
			else
			{
				Shooter player;
				player.position = sf::Vector2f(float(element["x"]), float(element["y"]));
				player.health = element["health"];
				player.direction = element["direction"].get<std::string>();
				player.nickname = "";
				player.playerId = element["playerId"].get<std::string>();
				m_data.m_vectorPlayers.push_back(player);
			}
		}
	}

	for (auto & element : data["playersForTable"])
	{
		(void)&element;
	}
}
