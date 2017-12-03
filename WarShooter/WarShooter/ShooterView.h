#pragma once
#include "sheet.h"
#include "Assets.h"
#include "DataOfServer.h"

class ShooterView
{
public:
	ShooterView(CAssets & assets, const Shooter & playerOfServer);

	void Draw(sf::RenderWindow & window);
	void Update();
	void SetParameters(const Shooter & playerOfServer);
	sf::Vector2f GetPosition() const;
	std::string GetIp() const;
	sf::Vector2f GetSize() const;
	bool GetIsDead() const;
	void SetIsDraw(bool isDraw);
	bool GetIsDraw() const;

private:
	void SetTexture(const sf::Texture & texture);
	
	std::string m_ip;
	std::string m_nickname;
	unsigned m_health;
	CAssets m_assets;
	sf::Sprite m_body;
	std::string m_direction;
	bool m_isDraw;
};
