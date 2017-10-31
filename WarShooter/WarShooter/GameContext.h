#pragma once
#include "sheet.h"
#include "Bullet.h"
#include "Block.h"
#include "Shooter.h"
#include "Assets.h"

class GameContext
{
public:
	GameContext();

	void Update(float dt, const KeyMap & keyMap);
	void Draw(sf::RenderWindow & window);

private:
	CAssets m_assets;

	sf::Sprite m_background;
	std::vector<Bullet> m_bullets;
	std::vector<Block> m_blocks;
	std::vector<Shooter> m_players;
	
	Block m_block;
};
