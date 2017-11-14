#pragma once
#include "Block.h"
#include "Bullet.h"
#include "Shooter.h"

struct DataOfServer
{
public:
	void Clear();

	std::vector<Shooter> m_vectorPlayers;
	std::vector<Block> m_vectorBlocks;
	std::vector<Bullet> m_vectorBullets;

private:
};
