#pragma once
#include "Assets.h"

const sf::Vector2u WINDOW_SIZE = { 1500, 600 };
const sf::Vector2f INITIAL_POSITION = { 400, 300 };
const unsigned FRAME_LIMIT = 60;

const sf::Vector2f BLOCK_POSITION = { 100, 100 };
const sf::Vector2f BLOCK_POSITION2 = { 100, 200 };
const sf::Vector2f BLOCK_POSITION3 = { 100, 350 };
const sf::Vector2f BLOCK_SIZE = { 150, 50 };

const sf::Vector2i BULLET_POSITION = { 450, 325 };
const sf::Vector2f BULLET_SIZE = { 10, 10 };

struct KeyMap
{
	bool isPressedKeyW = false;
	bool isPressedKeyA = false;
	bool isPressedKeyS = false;
	bool isPressedKeyD = false;
	bool isPressedArrowUp = false;
	bool isPressedArrowDown = false;
	bool isPressedArrowLeft = false;
	bool isPressedArrowRight = false;
};

enum class Direction
{
	None = 0,
	Up,
	Down,
	Left,
	Right,
};
