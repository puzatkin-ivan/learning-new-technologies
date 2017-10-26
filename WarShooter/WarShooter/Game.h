#pragma once
#include "GameContext.h"

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

	void Update(float deltaTime);
	void Draw(sf::RenderWindow & window);

	sf::RenderWindow m_window;
	sf::View m_view;
	sf::Clock m_clock;
	KeyMap m_keyMap;
	GameContext gameContext;
	Shooter m_player;
};
