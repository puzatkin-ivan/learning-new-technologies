#pragma once
#include "sheet.h"

class BulletView
{
public:
	BulletView(CAssets & assets, const sf::Vector2f & position);

	void Update(float dt);
	void Draw(sf::RenderWindow & window);
	void SetPosition(const sf::Vector2f & position);
	void SetIsDraw(bool isDraw);
	bool GetIsDraw() const;

private:
	void SetTexture(sf::Texture & texture);

	CAssets m_assets;
	sf::Sprite m_body;
	bool m_isDraw;
};
