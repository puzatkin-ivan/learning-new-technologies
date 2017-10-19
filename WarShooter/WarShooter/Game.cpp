#include "stdafx.h"
#include "Game.h"

const sf::Color WINDOW_COLOR = sf::Color::White;

Game::Game()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "WarShooter 2.0", sf::Style::Close)
	,m_block(BLOCK_POSITION, BLOCK_SIZE)
	,m_bullet(BULLET_POSITION, BULLET_SIZE)
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
		m_window.display();
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

void Game::CheckKeyboardEvent(const sf::Event & event)
{
	bool isNeedUpdate = false;
	CheckKeyPressed(event, isNeedUpdate);
	CheckKeyReleased(event, isNeedUpdate);

	if (isNeedUpdate)
	{
		m_player.UpdateDirection(m_keyMap);
	}
}

void Game::CheckKeyPressed(const sf::Event & event, bool & isNeedUpdate)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::A:
			m_keyMap.isPressedKeyA = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::D:
			m_keyMap.isPressedKeyD = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::W:
			m_keyMap.isPressedKeyW = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::S:
			m_keyMap.isPressedKeyS = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::Up:
			m_keyMap.isPressedArrowUp = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::Down:
			m_keyMap.isPressedArrowDown = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::Left:
			m_keyMap.isPressedArrowLeft = true;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::Right:
			m_keyMap.isPressedArrowRight = true;
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
			m_keyMap.isPressedKeyA = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::D:
			m_keyMap.isPressedKeyD = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::W:
			m_keyMap.isPressedKeyW = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::S:
			m_keyMap.isPressedKeyS = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::Up:
			m_keyMap.isPressedArrowUp = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::Down:
			m_keyMap.isPressedArrowDown = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::Left:
			m_keyMap.isPressedArrowLeft = false;
			isNeedUpdate = true;
			break;
		case sf::Keyboard::Right:
			m_keyMap.isPressedArrowRight = false;
			isNeedUpdate = true;
			break;
		}
	}
}

void Game::Update()
{
	m_player.Update();
}

void Game::Draw(sf::RenderWindow & window)
{
	m_window.clear(WINDOW_COLOR);
	m_block.Draw(m_window);
	m_bullet.Draw(m_window);
	m_player.Draw(m_window);
}
