#pragma once
#include "sheet.h"
#include "Bullet.h"
#include "Block.h"
#include "Shooter.h"

class GameContext
{
public:
	GameContext();

	void Update(float dt, const KeyMap & keyMap);
	void Draw(sf::RenderWindow & window);

private:
	std::vector<Bullet> m_bullets;
	std::vector<Block> m_blocks;
	std::vector<Shooter> m_players;

	Shooter m_player;
	Block m_block;
	Block m_block2;
	Block m_block3;
	Bullet m_bullet;
};
