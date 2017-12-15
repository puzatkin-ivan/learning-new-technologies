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

class GameContext
{
public:
	GameContext() = delete;
	GameContext(SAssets & assets);
	~GameContext() = default;

	bool isClientDead() const;
	void ProcessInitMessage(const std::string & path);
	void ProcessUpdateData(const std::string & path);
	void Update(sf::View & view, const std::string & ip);
	void Draw(sf::RenderWindow & window, bool isOpportunityDrawingTable) const;
	
private:
	void UpdateBlocks(const std::vector<Block> & vectorBlocks);
	void UpdatePlayers(const std::vector<Shooter> & vectorPlayers, sf::View & view, const std::string & ip);

	void UpdateParametersBullets(const nlohmann::basic_json<> & data);
	void UpdateParametersPlayers(const nlohmann::basic_json<> & data);
	void InitParametersPlayer(const nlohmann::basic_json<> & path, Shooter & player);
	void UpdateParametersTable(const nlohmann::basic_json<> & data);

	void InitPlayerTable(const nlohmann::basic_json<> & path, PlayerTable & newPlayer);
	void SetCenterView(sf::View & view, const std::unique_ptr<ShooterView> & player, const std::string & ip);

	SAssets m_assets;
	Table m_table;
	sf::Sprite m_background;
	std::vector<std::unique_ptr<BulletView>> m_bullets;
	std::vector<std::unique_ptr<BlockView>> m_blocks;
	std::vector<std::unique_ptr<ShooterView>> m_players;
	std::vector<PlayerTable> m_listPlayers;

	DataOfServer m_data;
	bool m_isDeadClient = false;
};
