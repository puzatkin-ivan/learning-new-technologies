#pragma once
#include "sheet.h"

class Shooter
{
public:
	Shooter();
	void Draw(sf::RenderWindow & window);
	void UpdatePosition();
	void UpdateDirection(KeyMap keyMap);

	float x;
	float y;


private:
	void UpdatePositionX(float deltaMove);
	void UpdatePositionY(float deltaMove);
	void UpdateDirectionX(bool isLeft, bool isRight);
	void UpdateDirectionY(bool isUp, bool isDown);

	sf::RectangleShape m_body;

	unsigned directionX;
	unsigned directionY;

};

