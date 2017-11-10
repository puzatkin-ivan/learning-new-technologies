#include "stdafx.h"
#include "Game.h"

const sf::Color WINDOW_COLOR = sf::Color::White;

Game::Game()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "WarShooter 2.0", sf::Style::Close)
	,m_assets()
	,m_gameContext(m_assets)
	,app()
{
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(FRAME_LIMIT);
	const auto icon = m_assets.WINDOW_ICON;
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
}

void Game::DoGameLoop()
{
	while (m_window.isOpen())
	{
		CheckEvents();
		Update();
		m_window.setView(m_view);
		Draw();
		m_window.display();
	}
}

void Game::Update()
{
	app.Update(m_gameContext, m_view);
}

void Game::Draw()
{
	m_window.clear(WINDOW_COLOR);
	m_gameContext.Draw(m_window);
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
		const auto isReleased = false;
		CheckMovement(event, isReleased);
		CheckDirection(event, isReleased);
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
