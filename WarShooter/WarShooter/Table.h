#pragma once

#include <SFML\Graphics.hpp>
#include "Assets.h"
#include "PlayerTable.h"
#include "PlayerTableView.h"

class Table
{
public:
	Table() = delete;
	Table(SAssets & assets);
	~Table() = default;
	
	void Update(std::vector<PlayerTable> & listPlay, const sf::Vector2f & viewPosition, const std::string & ip);
	void Draw(sf::RenderWindow & window) const;

private:
	void SetPosition(const sf::Vector2f & center);
	void AddPlayerForDraw(const PlayerTable & player, size_t index, const std::string & ip);
	void UpdatePlayer(const PlayerTable & player, size_t index, const std::string & ip);
	SAssets & m_assets;

	std::vector<std::unique_ptr<CPlayerTableView>> m_vectorPlayers;
	std::vector<sf::Text> m_columnPlayers;
	std::vector<sf::Text> m_columnStatus;
	std::vector<sf::Text> m_columnScore;
	std::vector<sf::Text> m_columnDead;

	sf::RectangleShape m_background;
	sf::RectangleShape m_line;
	sf::Text m_titlePlayers;
	sf::Text m_titleStatus;
	sf::Text m_titleScore;
	sf::Text m_titleDead;
};
