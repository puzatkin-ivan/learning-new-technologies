#include "stdafx.h"
#include "Shooter.h"

const sf::Color SHOOTER_COLOR = { 0, 0, 170 };
const sf::Vector2f SHOOTER_SIZE = { 40, 40 };
const auto NO_DIRECTION_MOVE = 0.f;
const auto SPEED = 200.f;

Shooter::Shooter()
{
	m_body.setFillColor(SHOOTER_COLOR);
	m_body.setSize(SHOOTER_SIZE);
	m_body.setPosition(m_position);
}

void Shooter::Draw(sf::RenderWindow & window)
{
	window.draw(m_body);
}

void Shooter::Update(float dt, const KeyMap & keyMap)
{
	UpdateDirection(keyMap);
	UpdatePosition(dt);
	m_body.setPosition(m_position);
}

void Shooter::UpdatePosition(float dt)
{
	const float singleDirectionMove = SPEED * dt;

	if (m_directionX == Direction::None)
	{
		UpdatePositionX(NO_DIRECTION_MOVE);
		UpdatePositionY(singleDirectionMove);
	}
	else if (m_directionY == Direction::None)
	{
		UpdatePositionX(singleDirectionMove);
		UpdatePositionY(NO_DIRECTION_MOVE);
	}
	else
	{
		const float multiDirectionMove = singleDirectionMove / std::sqrt(2.f);
		UpdatePositionX(multiDirectionMove);
		UpdatePositionY(multiDirectionMove);
	}
}

void Shooter::UpdatePositionX(float deltaMove)
{
	switch (m_directionX)
	{
	case Direction::Left:
		m_position.x -= deltaMove;
		break;
	case Direction::Right:
		m_position.x += deltaMove;
		break;
	}
}

void Shooter::UpdatePositionY(float deltaMove)
{
	switch (m_directionY)
	{
	case Direction::Up:
		m_position.y -= deltaMove;
		break;
	case Direction::Down:
		m_position.y += deltaMove;
		break;
	}
}

sf::Vector2f Shooter::GetPosition() const
{
	return m_body.getPosition();
}

void Shooter::UpdateDirection(const KeyMap & keyMap)
{
	UpdateDirectionX(keyMap.isPressedKeyA, keyMap.isPressedKeyD);
	UpdateDirectionY(keyMap.isPressedKeyW, keyMap.isPressedKeyS);
}

void Shooter::UpdateDirectionX(bool isLeft, bool isRight)
{
	if (isLeft)
	{
		m_directionX = Direction::Left;
	}
	else if (isRight)
	{
		m_directionX = Direction::Right;
	}
	else
	{
		m_directionX = Direction::None;
	}
}

void Shooter::UpdateDirectionY(bool isUp, bool isDown)
{
	if (isUp)
	{
		m_directionY = Direction::Up;
	}
	else if (isDown)
	{
		m_directionY = Direction::Down;
	}
	else
	{
		m_directionY = Direction::None;
	}
}
