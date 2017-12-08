#pragma once

struct PlayerTable
{
public:
	std::string playerId;
	int killCount;
	int deathCount;
	int score;
	bool isDead;
	std::string nickname;
private:
};
