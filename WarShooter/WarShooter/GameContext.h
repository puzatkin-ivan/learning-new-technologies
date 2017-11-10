#pragma once
#include "sheet.h"
#include "Bullet.h"
#include "Block.h"
#include "Shooter.h"
#include "Assets.h"
#include "Application.h"
#include "DataOfServer.h"

class GameContext
{
public:
	GameContext(CAssets & assets);

	void Update(const DataOfServer & data, sf::View & view, const std::string & ip);
	void Draw(sf::RenderWindow & window);

private:
	CAssets m_assets;

	sf::Sprite m_background;
	std::vector<std::unique_ptr<Bullet>> m_bullets;
	std::vector<std::unique_ptr<Block>> m_blocks;
	std::vector<std::unique_ptr<Shooter>> m_players;
};
