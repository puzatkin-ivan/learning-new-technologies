#pragma once

#include "Assets.h"
#include "sheet.h"

class BlockView
{
public:
	BlockView() = delete;
	BlockView(SAssets & assets, const sf::Vector2f & position);
	~BlockView() = default;

	void Update(float dt);
	void Draw(sf::RenderWindow & window) const;

private:
	void SetTexture(sf::Texture & texture);

	SAssets m_assets;
	sf::Sprite m_body;
};
