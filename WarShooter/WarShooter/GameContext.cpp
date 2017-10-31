#include "stdafx.h"
#include "GameContext.h"

GameContext::GameContext(CAssets & assets)
	:m_assets(assets)
{
	m_blocks.push_back(Block(m_assets));
	m_players.push_back(Shooter(m_assets));

	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.BACKGROUND_TEXTURE);
}

void GameContext::Update(float dt, const KeyMap & keyMap, sf::View & view)
{
	for (auto & block : m_blocks)
	{
		block.Update(dt);
	}

	for (auto & bullet : m_bullets)
	{
		bullet.Update(dt);
	}

	for (auto & player : m_players)
	{
		player.Update(dt, keyMap);
		if (player.GetIp() == m_clientIp)
		{
			view.setCenter(player.GetPosition());
		}
	}
}

void GameContext::Draw(sf::RenderWindow & window)
{
	window.draw(m_background);
	for (auto & block : m_blocks)
	{
		block.Draw(window);
	}
	for (auto & bullet : m_bullets)
	{
		bullet.Draw(window);
	}
	for (auto & player : m_players)
	{
		player.Draw(window);
	}
}
