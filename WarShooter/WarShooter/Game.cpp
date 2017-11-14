#include "stdafx.h"
#include "Game.h"

const sf::Color WINDOW_COLOR = sf::Color::White;

using json = nlohmann::json;

namespace
{
	static const auto PORT = "https://127.0.0.1:3000";
}

Game::Game()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "WarShooter 2.0", sf::Style::Close)
	,m_gameContext(m_assets)
	,m_socketMaster(PORT)
{
	m_socketMaster.Emit("nickname", "Ghost");
	m_socketMaster.SetHandler("new_player", [&](sio::event & e) {
		ProcessInitMessage(e.get_message()->get_string());
	});

	m_socketMaster.SetHandler("update_data", [&](sio::event & e) {
		ProcessUpdateData(e.get_message()->get_string());
	});

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
		while (IsConnected())
		{
			CheckEvents();
			Update();
			m_window.setView(m_view);
			Draw();
			m_window.display();
		}
	}
}

void Game::Update()
{
	m_gameContext.Update(m_data, m_view, m_ipClient);
	ClearVectors();
}

void Game::ClearVectors()
{
	m_data.Clear();
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
		SendKeyMap(65, isPressed);
		break;
	case sf::Keyboard::D:
		SendKeyMap(68, isPressed);
		break;
	case sf::Keyboard::W:
		SendKeyMap(87, isPressed);
		break;
	case sf::Keyboard::S:
		SendKeyMap(83, isPressed);
		break;
	}
}

void Game::CheckDirection(const sf::Event & event, bool isPressed)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		SendKeyMap(38, isPressed);
		break;
	case sf::Keyboard::Down:
		SendKeyMap(40, isPressed);
		break;
	case sf::Keyboard::Left:
		SendKeyMap(37, isPressed);
		break;
	case sf::Keyboard::Right:
		SendKeyMap(39, isPressed);
		break;
	}
}

bool Game::IsConnected() const
{
	return m_socketMaster.IsConnected();
}

void Game::Draw()
{
	m_window.clear(WINDOW_COLOR);
	m_gameContext.Draw(m_window);
}

void Game::ProcessInitMessage(const std::string & path)
{
	std::cout << path << std::endl;
	auto data = json::parse(path);
	for (auto & element : data["blocks"])
	{
		Block block;
		block.position = sf::Vector2f(float(element["x"]), float(element["y"]));
		m_data.m_vectorBlocks.push_back(block);
	}

	for (auto& element : data["players"])
	{
		Shooter player;
		player.position = sf::Vector2f(float(element["x"]), float(element["y"]));
		player.health = element["health"];
		player.direction = element["direction"].get<std::string>();
		//player.nickname = element["nickname"].get<std::string>();
		player.nickname = "";
		player.playerId = element["playerId"].get<std::string>();
		m_data.m_vectorPlayers.push_back(player);
	}

	for (auto& element : data["bullets"])
	{
		Bullet bullet;
		bullet.position = sf::Vector2f(float(element["x"]), float(element["y"]));
		m_data.m_vectorBullets.push_back(bullet);
	}

	m_ipClient = data["id"].get<std::string>();
}

void Game::ProcessUpdateData(const std::string & path)
{
	auto data = json::parse(path);
	for (auto & element : data["bullets"])
	{
		Bullet bullet;
		bullet.position = sf::Vector2f(float(element["x"]), float(element["y"]));
		m_data.m_vectorBullets.push_back(bullet);;
	}

	if (m_data.m_vectorPlayers.empty())
	{

		for (auto & element : data["playersForDraw"])
		{
			Shooter player;
			player.position = sf::Vector2f(float(element["x"]), float(element["y"]));
			player.health = element["health"];
			std::cout << player.position.x << " " << player.position.y << std::endl;
			player.direction = element["direction"].get<std::string>();
			//player.nickname = element["nickname"].get<std::string>();
			player.nickname = "";
			player.playerId = element["playerId"].get<std::string>();
			m_data.m_vectorPlayers.push_back(player);
		}
	}

	for (auto & element : data["playersForTable"])
	{
		(void)&element;
	}
}

void Game::SendKeyMap(const unsigned & keyCode, const bool & isPressed)
{
	json message;
	message["key"] = keyCode;
	message["isPressed"] = isPressed;
	m_socketMaster.Emit("keyMap", message.dump());
}
