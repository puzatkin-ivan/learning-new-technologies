#pragma once

#include "Application.h"

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

	void Update();
	void Draw();

	Application m_app;
	sf::RenderWindow m_window;
	sf::View m_view;
	sf::Clock m_clock;
	CAssets m_assets;
	KeyMap m_keyMap;
	GameContext m_gameContext;
};
