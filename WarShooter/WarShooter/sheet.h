#pragma once

const sf::Vector2u WINDOW_SIZE = { 1500, 850 };
const sf::Vector2f TEXT_POSITION = { 50, 400 };
const unsigned FRAME_LIMIT = 60;
const sf::Vector2f TABLE_POSITION = { 150.f, 150.f };
const sf::Vector2f TABLE_SIZE = { 1200.f, 500.f };
const sf::Vector2f LINE_TABLE_POSITION = { 150.f, 250.f };
const sf::Vector2f LINE_TABLE_SIZE = { 1200.f, 10.f };

const std::string ARRAY_BULLETS = "bullets";
const std::string ARRAY_BLOCKS = "blocks";
const std::string ARRAY_PLAYERS = "players";
const std::string ARRAY_PLAYERS_FOR_DRAW = "playersForDraw";
const std::string ARRAY_PLAYERS_FOR_TABLE = "playersForTable";
const std::string X = "x";
const std::string Y = "y";
const std::string PLAYER_ID = "playerId";
const std::string NICKNAME = "nickname";
const std::string DIRECTION = "direction";
const std::string HEALTH = "health";
const std::string SCORE = "score";
const std::string KILL_COUNT = "killCount";
const std::string DEATH_COUNT = "deathCount";
const std::string IS_DEAD = "isDead";
const std::string MESSAGE_KEY = "key";
const std::string MESSAGE_KEY_MAP = "keyMap";
const std::string MESSAGE_KEY_PRESSED = "isPressed";
const std::string NUMBER_TEXTURE = "texture";
const std::string STATUS_ALIVE = "Alive";
const std::string STATUS_DEAD = "Dead";

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

enum class ASCIICodeKey
{
	W = 87,
	A = 65,
	D = 68,
	S = 83,
	R = 82,
	ArrowUp = 38,
	ArrowDown = 40,
	ArrowLeft = 37,
	ArrowRight = 39,
	BackSpace = 8,
	Enter = 10,
	Ctrl_Enter = 13,
};

enum class SceneType
{
	ServerClose = -1,
	StartScene = 0,
	GameScene,
	PauseScene,
	GameOverScene,
};

enum class PlayerTexture
{
	Human = 0,
	Swat,
	Knight,
	Biker,
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
