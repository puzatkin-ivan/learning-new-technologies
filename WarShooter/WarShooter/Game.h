#pragma once

#include <AudioController.h>
#include <AudioPlayer.h>
#include <json.hpp>

#include "GameContext.h"
#include "SocketMaster.h"
#include "DataOfServer.h"
#include "StartGameScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"

class Game
{
public:
	Game();
	~Game();

	void DoGameLoop();

private:	
	void onInitData(const sio::event & event);
	void onUpdateData(const sio::event & event);

	sf::RenderWindow m_window;

	SAssets m_assets;
	SocketMaster m_socketMaster;
	GameContext m_gameContext;
	CAudioPlayer m_audioPlayer;

	StartGameScene m_startGameScene;
	GameScene m_gameScene;
	PauseScene m_pauseScene;
	GameOverScene m_gameoverScene;

	sf::Clock m_clock;
};
