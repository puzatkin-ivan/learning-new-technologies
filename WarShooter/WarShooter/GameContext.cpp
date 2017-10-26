#include "stdafx.h"
#include "GameContext.h"

GameContext::GameContext()
	:m_block(BLOCK_POSITION, BLOCK_SIZE)
	, m_block2(BLOCK_POSITION2, BLOCK_SIZE)
	, m_block3(BLOCK_POSITION3, BLOCK_SIZE)
	, m_bullet(BULLET_POSITION, BULLET_SIZE)
{
	m_blocks.push_back(m_block);
	m_blocks.push_back(m_block2);
	m_blocks.push_back(m_block3);

}

void GameContext::Update(float dt, const KeyMap & keyMap)
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
	}
}

void GameContext::Draw(sf::RenderWindow & window)
{
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
