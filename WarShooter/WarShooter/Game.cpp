#include "stdafx.h"
#include "Game.h"

Game::Game()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "WarShooter 2.0", sf::Style::Close)
{
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(FRAME_LIMIT);
}

void Game::DoGameLoop()
{
	while (m_window.isOpen())
	{
		CheckEvents();
		Update();
		Draw(m_window);
		
	}
}

void Game::CheckEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		CheckKeyboardEvent(event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Game::CheckKeyboardEvent(sf::Event & event)
{
	bool isNeedUpdate = false;
	CheckKeyPressed(event, isNeedUpdate);
	CheckKeyReleased(event, isNeedUpdate);

	if (isNeedUpdate)
	{
		player.UpdateDirection(keyMap);
	}
}

void Game::CheckKeyPressed(const sf::Event & event, bool & isNeedUpdate)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::A:
			keyMap.isPressedKeyA = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::D:
			keyMap.isPressedKeyD = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::W:
			keyMap.isPressedKeyW = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::S:
			keyMap.isPressedKeyS = true;
			isNeedUpdate = true;
			break;
		}
	}
}

void Game::CheckKeyReleased(const sf::Event & event, bool & isNeedUpdate)
{
	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::A:
			keyMap.isPressedKeyA = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::D:
			keyMap.isPressedKeyD = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::W:
			keyMap.isPressedKeyW = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::S:
			keyMap.isPressedKeyS = false;
			isNeedUpdate = true;
			break;
		}
	}
}

void Game::Update()
{
	player.UpdatePosition();
}

void Game::Draw(sf::RenderWindow & window)
{
	m_window.clear({255, 255, 255});
	player.Draw(m_window);
	m_window.display();
}