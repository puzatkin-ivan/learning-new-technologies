#pragma once

#include <AudioPlayer.h>

#include "GameContext.h"
#include "SocketMaster.h"
#include "Assets.h"
#include "Table.h"

class GameScene
{
public:
	GameScene() = delete;
	GameScene(sf::RenderWindow & window, GameContext & gameContext, SocketMaster & socketMaster, CAudioPlayer & audioPlayer);
	~GameScene() = default;

	SceneInfo Advance(float dt);

private:
	void CheckEvents();
	void CheckKeyboardEvent(const sf::Event & event);
	void CheckKeyPressed(const sf::Event & event);
	void CheckKeyReleased(const sf::Event & event);
	void CheckMovement(const sf::Event & event, bool isPressed);
	void CheckDirection(const sf::Event & event, bool isPressed);
	void CheckSpecialKey(const sf::Event & event, bool isPressed);
	void ResumePauseAudio();

	void SendKeyMap(const ASCIICodeKey & keyCode, bool isPressed);

	void Update(float deltaTime);
	void Draw() const;

	sf::RenderWindow & m_window;
	GameContext & m_gameContext;
	CAudioPlayer & m_audioPlayer;
	SocketMaster & m_socketMaster;

	sf::View m_view;
	KeyMap m_keyMap;
	DataOfServer m_data;

	SceneType m_nextSceneType;
	
	bool m_isOpportunityDrawbleTable;
};
