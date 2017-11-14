#pragma once
#include "sheet.h"

class BlockView
{
public:
	BlockView(CAssets & assets, const sf::Vector2f & position);
	
	void Update(float dt);
	void Draw(sf::RenderWindow & window);

private:
	void SetTexture(sf::Texture & texture);

	CAssets m_assets;
	sf::Sprite m_body;
};
