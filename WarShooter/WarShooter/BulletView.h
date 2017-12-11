#pragma once
#include "sheet.h"

class BulletView
{
public:
	BulletView() = delete;
	BulletView(SAssets & assets, const sf::Vector2f & position);
	~BulletView() = default;

	void Update(float dt);
	void Draw(sf::RenderWindow & window) const;
	void SetPosition(const sf::Vector2f & position);
	void SetOpportunityDrawing(bool isDraw);
	bool GetIsDraw() const;

private:
	void SetTexture(sf::Texture & texture);

	SAssets m_assets;
	sf::Sprite m_body;
	bool m_isDraw;
};
