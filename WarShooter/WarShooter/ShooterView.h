#pragma once

#include "sheet.h"
#include "Assets.h"
#include "DataOfServer.h"

class ShooterView
{
public:
	ShooterView() = delete;
	ShooterView(SAssets & assets, const Shooter & playerOfServer);
	~ShooterView() = default;

	void Draw(sf::RenderWindow & window) const;
	void Update();
	void SetParameters(const Shooter & playerOfServer);
	sf::Vector2f GetPosition() const;
	std::string GetIp() const;
	sf::Vector2f GetSize() const;
	bool GetInformationAboutHealth() const;
	void SetOpportunityDrawing(bool isDrawble);

private:
	void SetTexture();
	
	std::string m_ip;
	std::string m_nickname;
	unsigned m_health;
	SAssets m_assets;
	sf::Sprite m_body;
	std::string m_direction;
	bool m_isDrawble;
	bool m_isDead;
	unsigned m_numberTexture;
};
