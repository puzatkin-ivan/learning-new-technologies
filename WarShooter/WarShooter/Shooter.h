#pragma once
#include "sheet.h"

class Shooter
{
public:
	Shooter();

	void Draw(sf::RenderWindow & window);
	void Update(float dt, const KeyMap & keyMap);
	sf::Vector2f GetPosition() const;

private:
	void UpdatePosition(float dt);
	void UpdatePositionX(float deltaMove);
	void UpdatePositionY(float deltaMove);

	void UpdateDirection(const KeyMap & keyMap);
	void UpdateDirectionX(bool isLeft, bool isRight);
	void UpdateDirectionY(bool isUp, bool isDown);

	sf::RectangleShape m_body;
	sf::Vector2f m_position = INITIAL_POSITION;

	Direction m_directionX = Direction::None;
	Direction m_directionY = Direction::None;
};
