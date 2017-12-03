#pragma once
#include "GameContext.h"
#include "SocketMaster.h"
#include <AudioPlayer.h>
#include "Assets.h"

class GameScene
{
public:
	GameScene(sf::RenderWindow & window, GameContext & gameContext, SocketMaster & socketMaster, CAudioPlayer & audioPlayer);

	SceneInfo Advance(float dt);

private:
	void CheckEvents();
	void CheckKeyboardEvent(const sf::Event & event);
	void CheckKeyPressed(const sf::Event & event);
	void CheckKeyReleased(const sf::Event & event);
	void CheckMovement(const sf::Event & event, bool isPressed);
	void CheckDirection(const sf::Event & event, bool isPressed);
	void CheckSpecialKey(const sf::Event & event);
	void ChangeStatusAudioPlayer();

	void SendKeyMap(const CodeKey & keyCode, const bool & isPressed);
	void ProcessUpdateData(const std::string & path);

	void Update(float deltaTime);
	void Draw();

	sf::RenderWindow & m_window;
	GameContext & m_gameContext;
	CAudioPlayer & m_audioPlayer;
	SocketMaster & m_socketMaster;

	sf::View m_view;
	KeyMap m_keyMap;
	DataOfServer m_data;

	SceneType m_nextSceneType;
};