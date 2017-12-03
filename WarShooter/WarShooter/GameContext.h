#pragma once
#include "sheet.h"
#include "BulletView.h"
#include "BlockView.h"
#include "ShooterView.h"
#include "Assets.h"
#include "DataOfServer.h"

class GameContext
{
public:
	GameContext(CAssets & assets);

	bool isClientDead() const;
	void ProcessInitMessage(const std::string & path);
	void ProcessUpdateData(const std::string & path);
	void Update(sf::View & view, const std::string & ip);
	void Draw(sf::RenderWindow & window);
	
private:
	void UpdateBlocks(const std::vector<Block> & vectorBlocks);
	void UpdateBullets(const std::vector<Bullet> & vectorBullets);
	void UpdatePlayers(const std::vector<Shooter> & vectorPlayers, sf::View & view, const std::string & ip);

	CAssets m_assets;
	sf::Sprite m_background;
	std::vector<std::unique_ptr<BulletView>> m_bullets;
	std::vector<std::unique_ptr<BlockView>> m_blocks;
	std::vector<std::unique_ptr<ShooterView>> m_players;
	DataOfServer m_data;
	bool isDeadClient = false;
};
