#pragma once
#include "Assets.h"

const sf::Vector2u WINDOW_SIZE = { 1500, 850 };
const sf::Vector2f TEXT_POSITION = { 50, 400 };
const unsigned FRAME_LIMIT = 60;

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

enum class CodeKey
{
	W = 87,
	A = 65,
	D = 68,
	S = 83,
	ArrowUp = 38,
	ArrowDown = 40,
	ArrowLeft = 37,
	ArrowRight = 39,
	BackSpace = 8,
};

enum class SceneType
{
	StartScene = 0,
	GameScene,
	PauseScene,
	GameOverScene,
};

struct SceneInfo
{
public:
	SceneInfo() = delete;
	SceneInfo(const SceneType & type)
		:nextSceneType(type)
	{}

	SceneType nextSceneType;
};
