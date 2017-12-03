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

	~Game()
	{
		m_audioPlayer.Stop();
	}

	void DoGameLoop();

private:
	void CheckEvents();
	void CheckKeyboardEvent(const sf::Event & event);
	void CheckKeyPressed(const sf::Event & event);
	void CheckKeyReleased(const sf::Event & event);
	void CheckInputText(const sf::Event & event);
	void CheckMovement(const sf::Event & event, bool isPressed);
	void CheckDirection(const sf::Event & event, bool isPressed);
	void CheckSpecialKey(const sf::Event & event);
	void ChangeStatusAudioPlayer();

	void SendKeyMap(const CodeKey & keyCode, const bool & isPressed);
	bool IsConnected() const;

	void Update();
	void Draw();
	
	sf::Sprite m_menuBackground;
	sf::RenderWindow m_window;
	sf::View m_view;
	sf::Text m_text;
	std::string m_stringWithText;
	sf::Clock m_clock;

	CAssets m_assets;
	KeyMap m_keyMap;
	GameContext m_gameContext;
	StartGameScene m_startGameScene;
	GameScene m_gameScene;
	PauseScene m_pauseScene;
	GameOverScene m_gameoverScene;
	
	DataOfServer m_data;
	SocketMaster m_socketMaster;
	std::string m_ipClient;

	CAudioPlayer m_audioPlayer;
};
