#pragma once

#include "Assets.h"
#include "PlayerTable.h"

class CPlayerTableView
{
public:
	CPlayerTableView() = delete;
	CPlayerTableView(SAssets & assets);
	~CPlayerTableView() = default;

	void SetContent(const PlayerTable & player, size_t index, const std::string & ip);
	void SetPositionX(const sf::Vector2f & positon);
	void SetPositionY(const sf::Vector2f & positionY);
	void SetOpportunityDrawing(bool isDraw);

	void Draw(sf::RenderWindow & window) const;

private:
	SAssets & m_assets;
	sf::Text m_name;
	sf::Text m_status;
	sf::Text m_killCount;
	sf::Text m_deathCount;

	bool m_isOpportunityDrawing;
};

