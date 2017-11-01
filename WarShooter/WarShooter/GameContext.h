#pragma once
#include "sheet.h"
#include "Bullet.h"
#include "Block.h"
#include "Shooter.h"
#include "Assets.h"

class GameContext
{
public:
	GameContext(CAssets & assets);

	void Update(float dt, const KeyMap & keyMap, sf::View & view);
	void Draw(sf::RenderWindow & window);

private:
	CAssets m_assets;

	sf::Sprite m_background;
	std::vector<Bullet> m_bullets;
	std::vector<std::unique_ptr<Block>> m_blocks;
	std::vector<std::unique_ptr<Shooter>> m_players;
	unsigned m_clientIp = 10;
};
