#pragma once

#include <string>

struct PlayerTable
{
public:
	std::string playerId;
	unsigned killCount;
	unsigned deathCount;
	bool isDead;
	std::string nickname;
	bool isDrawble;

private:
};
