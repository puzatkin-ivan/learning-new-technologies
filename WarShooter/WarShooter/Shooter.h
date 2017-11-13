#pragma once
#include "sheet.h"
#include "Assets.h"
#include "DataOfServer.h"

class Shooter
{
public:
	Shooter(CAssets & assets, const PlayerForDraw & playerOfServer);

	void Draw(sf::RenderWindow & window);
	void Update();
	void SetParameters(const PlayerForDraw & playerOfServer);
	sf::Vector2f GetPosition() const;
	std::string GetIp() const;
	sf::Vector2f GetSize() const;

private:
	void SetTexture(const sf::Texture & texture);
	
	std::string m_ip;
	std::string m_nickname;
	int m_health;
	CAssets m_assets;
	sf::Sprite m_body;
	std::string m_direction = "no_direction";
};
