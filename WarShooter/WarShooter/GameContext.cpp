#include "stdafx.h"

#include "GameContext.h"
#include <iostream>

GameContext::GameContext(CAssets & assets)
	:m_assets(assets)
{
	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.BACKGROUND_TEXTURE);
}

void GameContext::Update(const DataOfServer & data, sf::View & view, const std::string & ip)
{
	UpdateBlocks(data.m_vectorBlocks);
	UpdateBullets(data.m_vectorBullets);
	UpdatePlayers(data.m_vectorPlayers, view, ip);
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
	if (m_bullets.empty())
	{
		for (auto & bullet : vectorBullets)
		{
			auto itemBullet = std::make_unique<BulletView>(m_assets, bullet.getPosition());
			m_bullets.push_back(std::move(itemBullet));
		}
	}
	else
	{
		size_t index = 0;
		for (auto & bullet : vectorBullets)
		{
			if (index < m_bullets.size())
			{
				m_bullets[index]->SetPosition(bullet.getPosition());
				m_bullets[index]->SetIsDraw(true);
				++index;
			}
			else
			{
				auto itemBullet = std::make_unique<BulletView>(m_assets, bullet.getPosition());
				m_bullets.push_back(std::move(itemBullet));
			}
		}
		if (index < m_bullets.size())
		{
			for (index; index < m_bullets.size(); ++index)
			{
				m_bullets[index]->SetIsDraw(false);
			}
		}
	}
}

void GameContext::SetView(const std::unique_ptr<ShooterView> & player, sf::View & view)
{
	const sf::Vector2f playerPosition = player->GetPosition() + 0.5f * player->GetSize();
	view.setCenter(playerPosition);

	const auto newPositionBackground = playerPosition - 0.5f * sf::Vector2f(WINDOW_SIZE);
	m_background.setPosition(newPositionBackground);
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
				SetView(player, view);
			}
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
					SetView(m_players[index], view);
				}

				index++;
			}
			else
			{
				auto player = std::make_unique<ShooterView>(m_assets, playerObject);
				m_players.push_back(std::move(player));
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
		player->Draw(window);
	}
}
