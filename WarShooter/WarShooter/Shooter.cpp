#include "stdafx.h"
#include "Shooter.h"

Shooter::Shooter()
{
	const sf::Color ColorShooter = { 0, 0, 170 };
	m_body.setFillColor(ColorShooter);

	const sf::Vector2f Shooter_Size = { 40, 40 };
	m_body.setSize(Shooter_Size);

	x = INITINAL_POSITION.x;
	y = INITINAL_POSITION.y;
	m_body.setPosition({ x, y });
}

void Shooter::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}

void Shooter::UpdatePosition()
{
	const float singleDirectionMove = 6;

	if (directionX == Direction::None)
	{
		UpdatePositionY(singleDirectionMove);
	}
	else if (directionY == Direction::None)
	{
		UpdatePositionX(singleDirectionMove);
	}
	else 
	{
		const float multiDirectionMove = singleDirectionMove / float(std::sqrt(2));
		UpdatePositionX(multiDirectionMove);
		UpdatePositionY(multiDirectionMove);
	}
	m_body.setPosition({ x, y });
}


void Shooter::UpdatePositionX(float deltaMove)
{
	switch (directionX)
	{
	case Direction::Left:
		x -= deltaMove;
		break;
	case Direction::Right:
		x += deltaMove;
		break;
	}
}

void Shooter::UpdatePositionY(float deltaMove)
{
	switch (directionY)
	{
	case Direction::Up:
		y -= deltaMove;
		break;
	case Direction::Down:
		y += deltaMove;
		break;
	}
}

void Shooter::UpdateDirection(KeyMap keyMap)
{
	UpdateDirectionX(keyMap.isPressedKeyA, keyMap.isPressedKeyD);
	UpdateDirectionY(keyMap.isPressedKeyW, keyMap.isPressedKeyS);
}

void Shooter::UpdateDirectionX(bool isLeft, bool isRight)
{
	if (isLeft)
	{
		directionX = Direction::Left;
	}
	else if (isRight)
	{
		directionX = Direction::Right;
	}
	else
	{
		directionX = Direction::None;
	}
}

void Shooter::UpdateDirectionY(bool isUp, bool isDown)
{
	if (isUp)
	{
		directionY = Direction::Up;
	}
	else if (isDown)
	{
		directionY = Direction::Down;
	}
	else
	{
		directionY = Direction::None;
	}
}
