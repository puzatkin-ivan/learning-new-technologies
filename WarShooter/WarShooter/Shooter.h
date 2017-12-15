#pragma once

struct Shooter
{
public:
	sf::Vector2f position;
	unsigned health;
	std::string direction;
	std::string nickname;
	std::string playerId;
	bool isDrawble;
	bool isDead;
	unsigned numberTexture;

private:
};
