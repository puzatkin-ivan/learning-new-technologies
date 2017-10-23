#pragma once
#include "sheet.h"
#include "Bullet.h"
#include "Block.h"
#include "Shooter.h"

class GameContext
{
public:
	GameContext();

	void Update();
	void Draw(sf::RenderWindow & window);

private:
	std::vector<Bullet> m_bullets;
	std::vector<Block> m_blocks;
	std::vector<Shooter> m_players;
};
