#pragma once
#include <SFML\Graphics.hpp>

const sf::Vector2u WINDOW_SIZE = { 1500, 600 };
const sf::Vector2f INITIAL_POSITION = { 400, 300 };
const unsigned FRAME_LIMIT = 60;

struct KeyMap
{
	bool isPressedKeyW = false;
	bool isPressedKeyA = false;
	bool isPressedKeyS = false;
	bool isPressedKeyD = false;
};

enum class Direction
{
	None = 0,
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4,
};
