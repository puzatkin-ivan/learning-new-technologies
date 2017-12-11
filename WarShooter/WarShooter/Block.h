#pragma once

struct Block
{
public:
	sf::Vector2f getPosition() const;

	void setPosition(const sf::Vector2f & position);

private:
	sf::Vector2f m_position;
	bool m_isDraw;
};
