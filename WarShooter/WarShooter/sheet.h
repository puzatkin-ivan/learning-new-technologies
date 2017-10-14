#pragma once
#include "SFML\Graphics.hpp"

const sf::Vector2u WINDOW_SIZE = { 1500, 600 };
const sf::Vector2f INITINAL_POSITION = { 400, 300 };
const unsigned FRAME_LIMIT = 60;
const float SPEED = 300;

struct KeyMap
{
	bool isPressedKeyW = false;
	bool isPressedKeyA = false;
	bool isPressedKeyS = false;
	bool isPressedKeyD = false;
};

struct Direction
{
	static const unsigned None = 0;
	static const unsigned Up = 1;
	static const unsigned Down = 2;
	static const unsigned Left = 3;
	static const unsigned Right = 4;
};
