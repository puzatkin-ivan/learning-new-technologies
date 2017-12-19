#pragma once

#include "Assets.h"

class CHealthPoints
{
public:
	CHealthPoints() = delete;
	CHealthPoints(SAssets & assets);

	void SetPosition(const sf::Vector2f & position);
	void SetHealtsPoints(unsigned health);

	void Draw(sf::RenderWindow & window) const;

private:
	SAssets & m_assets;

	sf::Sprite m_redCross;
	sf::Text m_healthPoints;
};
