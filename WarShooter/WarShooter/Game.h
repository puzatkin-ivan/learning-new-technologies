#pragma once

#include "GameContext.h"
#include "SocketMaster.h"
#include "DataOfServer.h"

class Game
{
public:
	Game();

	void DoGameLoop();

private:
	void CheckEvents();
	void CheckKeyboardEvent(const sf::Event & event);
	void CheckKeyPressed(const sf::Event & event);
	void CheckKeyReleased(const sf::Event & event);
	void CheckMovement(const sf::Event & event, bool isPressed);
	void CheckDirection(const sf::Event & event, bool isPressed);

	void SendKeyMap(const unsigned & keyCode, const bool & isPressed);
	bool IsConnected() const;
	void ProcessInitMessage(const std::string & path);
	void ProcessUpdateData(const std::string & path); 
	void ClearVectors();

	void Update();
	void Draw();
	
	sf::RenderWindow m_window;
	sf::View m_view;
	sf::Clock m_clock;
	CAssets m_assets;
	KeyMap m_keyMap;
	GameContext m_gameContext;
	
	DataOfServer m_data;
	SocketMaster m_socketMaster;
	std::string m_ipClient;
};
