#pragma once

struct Block
{
public:
	sf::Vector2f getPosition() const
	{
		return m_position;
	}

	void setPosition(const sf::Vector2f & position)
	{
		m_position = position;
	}

private:
	sf::Vector2f m_position;
};
