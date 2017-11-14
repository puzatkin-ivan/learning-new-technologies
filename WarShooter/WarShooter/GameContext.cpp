#include "stdafx.h"

#include "GameContext.h"

GameContext::GameContext(CAssets & assets)
	:m_assets(assets)
{
	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.BACKGROUND_TEXTURE);
}

void GameContext::Update(const DataOfServer & data, sf::View & view, const std::string & ip)
{
	if (m_blocks.empty())
	{
		for (auto & block : data.m_vectorBlocks)
		{
			m_blocks.push_back(std::make_unique<BlockView>(m_assets, block.position));
		}
	}

	if (m_bullets.empty())
	{
		for (auto & bullet : data.m_vectorBullets)
		{
			(void)&bullet;
			m_bullets.push_back(std::make_unique<BulletView>(m_assets/*, bullet.position*/));
		}
	}

	if (m_players.empty())
	{
		for (auto & playerObject : data.m_vectorPlayers)
		{
			auto player = std::make_unique<ShooterView>(m_assets, playerObject);
			if (player->GetIp() == ip)
			{
				const sf::Vector2f playerPosition = player->GetPosition() + 0.5f * player->GetSize();
				view.setCenter(playerPosition);

				const auto newPositionBackground = playerPosition - 0.5f * sf::Vector2f(WINDOW_SIZE);
				m_background.setPosition(newPositionBackground);
			}
			m_players.push_back(std::move(player));
		}
	}
	else
	{
		size_t index = 0;
		for (auto & playerObject : data.m_vectorPlayers)
		{
			if (index <= m_players.size() - 1)
			{
				m_players[index]->SetParameters(playerObject);
				if (m_players[index]->GetIp() == ip)
				{
					const sf::Vector2f playerPosition = m_players[index]->GetPosition() + 0.5f * m_players[index]->GetSize();
					view.setCenter(playerPosition);

					const auto newPositionBackground = playerPosition - 0.5f * sf::Vector2f(WINDOW_SIZE);
					m_background.setPosition(newPositionBackground);
				}

				index++;
			}
			else
			{
				auto player = std::make_unique<ShooterView>(m_assets, playerObject);
				if (player->GetIp() == ip)
				{
					const sf::Vector2f playerPosition = player->GetPosition() + 0.5f * player->GetSize();
					view.setCenter(playerPosition);

					const auto newPositionBackground = playerPosition - 0.5f * sf::Vector2f(WINDOW_SIZE);
					m_background.setPosition(newPositionBackground);
				}
				m_players.push_back(std::move(player));
			}
		}
	}
}

void GameContext::Draw(sf::RenderWindow & window)
{
	window.draw(m_background);
	for (auto & block : m_blocks)
	{
		block->Draw(window);
	}
	for (auto & bullet : m_bullets)
	{
		bullet->Draw(window);
	}
	for (auto & player : m_players)
	{
		player->Draw(window);
	}
}
