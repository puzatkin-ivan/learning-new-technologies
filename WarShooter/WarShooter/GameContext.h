#pragma once

#include "sheet.h"
#include "Assets.h"
#include "BulletView.h"
#include "BlockView.h"
#include "ShooterView.h"
#include "Table.h"
#include "DataOfServer.h"
#include "PlayerTable.h"
#include "SocketMaster.h"
#include "HealthPoints.h"

using json = nlohmann::json;

class GameContext
{
public:
	GameContext() = delete;
	GameContext(SAssets & assets);
	~GameContext() = default;

	bool IsClientDead() const;
	void ProcessInitMessage(const std::string & path);
	void ProcessUpdateData(const std::string & path);
	void Update(sf::View & view, const std::string & ip);
	void Draw(sf::RenderWindow & window, bool isOpportunityDrawingTable) const;

	void Clear();
	
private:
	void UpdateBlocks(const std::vector<Block> & vectorBlocks);
	void UpdatePlayers(const std::vector<Shooter> & vectorPlayers, sf::View & view, const std::string & ip);

	void UpdateParametersBullets(const json & data);
	void UpdateParametersPlayers(const json & data);
	void InitParametersPlayer(const json & path, Shooter & player);
	void UpdateParametersTable(const json & data);

	void InitPlayerTable(const json & path, PlayerTable & newPlayer);
	void SetCenterView(sf::View & view, const std::unique_ptr<ShooterView> & player, const std::string & ip);

	void InitMarginField();

	SAssets m_assets;
	Table m_table;
	sf::Sprite m_background;
	std::vector<sf::RectangleShape> m_marginField;
	std::vector<std::unique_ptr<BulletView>> m_bullets;
	std::vector<std::unique_ptr<BlockView>> m_blocks;
	std::vector<std::unique_ptr<ShooterView>> m_players;
	std::vector<PlayerTable> m_listPlayers;
	CHealthPoints m_healthPoints;

	DataOfServer m_data;
	bool m_isClientDead;
};
