#pragma once
#include "Assets.h"

const sf::Vector2u WINDOW_SIZE = { 1500, 850 };
const sf::Vector2f INITIAL_POSITION = { 400, 400 };
const unsigned FRAME_LIMIT = 60;

const sf::Vector2f BLOCK_POSITION0 = { 100.f, 500.f };
const sf::Vector2f BLOCK_POSITION1 = { 200.f, 400.f };
const sf::Vector2f BLOCK_POSITION2 = { 100.f, 100.f };
const sf::Vector2f BLOCK_POSITION3 = { 400.f, 250.f };
const sf::Vector2f BLOCK_POSITION4 = { 500.f, 550.f };
const sf::Vector2f BLOCK_POSITION5 = { 600.f, 150.f };
const sf::Vector2f BLOCK_POSITION6 = { 700.f, 350.f };
const sf::Vector2f BLOCK_POSITION7 = { 900.f, 150.f };
const sf::Vector2f BLOCK_POSITION8 = { 900.f, 550.f };
const sf::Vector2f BLOCK_POSITION9 = { 1000.f, 350.f };
const sf::Vector2f BLOCK_POSITION10 = { 1200.f, 50.f };
const sf::Vector2f BLOCK_POSITION11 = { 1100.f, 450.f };
const sf::Vector2f BLOCK_POSITION12 = { 1300.f, 600.f };
const sf::Vector2f BLOCK_SIZE = { 150, 50 };

const sf::Vector2f BULLET_POSITION = { 450, 325 };
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
