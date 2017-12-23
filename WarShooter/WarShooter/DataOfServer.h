#pragma once

#include "Block.h"
#include "Shooter.h"

struct DataOfServer
{
public:
	void Clear();

	std::vector<Shooter> players;
	std::vector<Block> blocks;
	std::vector<Block> marginGameField;

private:
};
