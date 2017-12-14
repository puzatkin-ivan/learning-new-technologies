#pragma once

#include "Assets.h"
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
	void SetOpportunityDrawble(bool isDrawble);

private:
	void SetTexture(sf::Texture & texture);

	SAssets m_assets;
	sf::Sprite m_body;
	bool m_isOpportunityDrawing;
};
