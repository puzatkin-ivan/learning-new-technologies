#pragma once
#include "sheet.h"
#include "Assets.h"

class Shooter
{
public:
	Shooter(CAssets & assets);

	void Draw(sf::RenderWindow & window);
	void Update(float dt, const KeyMap & keyMap);
	sf::Vector2f GetPosition() const;
	unsigned GetIp() const;

private:
	void UpdatePosition(float dt);
	void UpdatePositionX(float deltaMove);
	void UpdatePositionY(float deltaMove);

	void UpdateDirection(const KeyMap & keyMap);
	void UpdateDirectionX(bool isLeft, bool isRight);
	void UpdateDirectionY(bool isUp, bool isDown);

	void SetTexture(const sf::Texture & texture);
	
	unsigned m_ip = 10;
	CAssets m_assets;
	sf::Sprite m_body;
	sf::Vector2f m_position = INITIAL_POSITION;
	Direction m_directionX = Direction::None;
	Direction m_directionY = Direction::None;
};
