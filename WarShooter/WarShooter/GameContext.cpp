#include "stdafx.h"
#include "GameContext.h"

GameContext::GameContext(CAssets & assets)
	:m_assets(assets)
{
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION0));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION1));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION2));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION3));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION4));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION5));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION6));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION7));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION8));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION9));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION10));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION11));
	m_blocks.push_back(std::make_unique<Block>(m_assets, BLOCK_POSITION12));
	m_players.push_back(std::make_unique<Shooter>(m_assets));

	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.BACKGROUND_TEXTURE);
}

void GameContext::Update(float dt, const KeyMap & keyMap, sf::View & view)
{
	for (auto & block : m_blocks)
	{
		block->Update(dt);
	}

	for (auto & bullet : m_bullets)
	{
		bullet.Update(dt);
	}

	for (auto & player : m_players)
	{
		player->Update(dt, keyMap);
		if (player->GetIp() == m_clientIp)
		{
			view.setCenter(player->GetPosition());
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
		bullet.Draw(window);
	}
	for (auto & player : m_players)
	{
		player->Draw(window);
	}
}
