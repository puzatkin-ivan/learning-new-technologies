#pragma once
#include "Shooter.h"

class Game
{
public:
	Game();

	void DoGameLoop();

private:
	void CheckEvents();
	void CheckKeyboardEvent(const sf::Event & event);
	void CheckKeyPressed(const sf::Event & event, bool & isNeedUpdate);
	void CheckKeyReleased(const sf::Event & event, bool & isNeedUpdate);

	void Update();
	void Draw(sf::RenderWindow & window);

	sf::RenderWindow m_window;
	KeyMap m_keyMap;
	Shooter m_player;
};
