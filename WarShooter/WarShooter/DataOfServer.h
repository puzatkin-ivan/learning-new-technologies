#pragma once

struct PlayerForDraw
{
public:
	sf::Vector2f position;
	int health;
	std::string direction;
	std::string nickname;
	std::string playerId;
private:
};

struct BlockForDraw
{
public:
	sf::Vector2f position;

private:
};

struct BulletForDraw
{
public:
	sf::Vector2f position;

private:
};

struct DataOfServer
{
public:
	void Clear();

	std::vector<PlayerForDraw> m_vectorPlayers;
	std::vector<BlockForDraw> m_vectorBlocks;
	std::vector<BulletForDraw> m_vectorBullets;

private:
};
