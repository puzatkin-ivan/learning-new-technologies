#include "stdafx.h"
#include "Game.h"

int main()
{
	try
	{
		Game game;
		game.DoGameLoop();
	}
	catch (const std::exception & ex)
	{
		std::cerr << "NOTE: " << ex.what() << std::endl;
	}
}
