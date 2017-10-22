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

void Game::Update()
{
	m_player.Update(m_keyMap);
}

void Game::Draw(sf::RenderWindow & window)
{
	m_window.clear(WINDOW_COLOR);
	m_block.Draw(m_window);
	m_bullet.Draw(m_window);
	m_player.Draw(m_window);
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
	CheckKeyPressed(event);
	CheckKeyReleased(event);
}

void Game::CheckKeyPressed(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		const auto isPressed = true;
		CheckMovement(event, isPressed);
		CheckDirection(event, isPressed);
	}
}

void Game::CheckKeyReleased(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		const auto isPressed = false;
		CheckMovement(event, isPressed);
		CheckDirection(event, isPressed);
	}
}

void Game::CheckMovement(const sf::Event & event, bool isPressed)
{
	switch (event.key.code)
	{
	case sf::Keyboard::A:
		m_keyMap.isPressedKeyA = isPressed;
		break;
	case sf::Keyboard::D:
		m_keyMap.isPressedKeyD = isPressed;
		break;
	case sf::Keyboard::W:
		m_keyMap.isPressedKeyW = isPressed;
		break;
	case sf::Keyboard::S:
		m_keyMap.isPressedKeyS = isPressed;
		break;
	}
}

void Game::CheckDirection(const sf::Event & event, bool isPressed)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		m_keyMap.isPressedArrowUp = isPressed;
		break;
	case sf::Keyboard::Down:
		m_keyMap.isPressedArrowDown = isPressed;
		break;
	case sf::Keyboard::Left:
		m_keyMap.isPressedArrowLeft = isPressed;
		break;
	case sf::Keyboard::Right:
		m_keyMap.isPressedArrowRight = isPressed;
		break;
	}
}