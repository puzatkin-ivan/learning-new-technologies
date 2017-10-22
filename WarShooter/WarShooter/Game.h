#pragma once
#include "Shooter.h"
#include "Block.h"
#include "Bullet.h"

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
	void Draw(sf::RenderWindow & window);

	sf::RenderWindow m_window;
	KeyMap m_keyMap;
	Shooter m_player;
	Block m_block;
	Bullet m_bullet;
};
