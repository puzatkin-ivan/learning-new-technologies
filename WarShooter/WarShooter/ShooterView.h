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
	bool IsDead() const;
	unsigned GetHealth() const;
	void SetOpportunityDrawable(bool isDrawable);

private:
	void SetTexture();

	sf::Sprite m_body;

	sf::Text m_nickname;
	std::string m_ip;
	unsigned m_health;
	SAssets m_assets;
	std::string m_direction;
	bool m_isDrawable;
	bool m_isDead;
	unsigned m_numberTexture;
};
