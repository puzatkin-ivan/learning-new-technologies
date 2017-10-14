#pragma once
#include "Shooter.h"

class Game
{
public:
	Game();

	void DoGameLoop();

private:

	void CheckEvents();
	void CheckKeyboardEvent(sf::Event & event);
	void CheckKeyPressed(const sf::Event & event, bool & isNeedUpdate);
	void CheckKeyReleased(const sf::Event & event, bool & isNeedUpdate);

	void Update();
	void Draw(sf::RenderWindow & window);


	KeyMap keyMap;
	sf::RenderWindow m_window;
	Shooter player;
};
