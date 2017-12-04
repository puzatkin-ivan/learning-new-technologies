#include "stdafx.h"
#include "Game.h"

const sf::Color WINDOW_COLOR = sf::Color::White;

using json = nlohmann::json;

namespace
{
	static const auto PORT = "https://192.168.21.54:3000";
}

Game::Game()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "WarShooter 2.0", sf::Style::Close)
	,m_gameContext(m_assets)
	,m_socketMaster(PORT)
	,m_audioPlayer("sounds/")
	,m_startGameScene(m_window, m_assets, m_audioPlayer)
	,m_gameScene(m_window, m_gameContext, m_socketMaster, m_audioPlayer)
	,m_pauseScene(m_window, m_assets)
	,m_gameoverScene(m_window, m_gameContext, m_assets)
{
	m_socketMaster.Emit("nickname", "Ghost");
	m_socketMaster.SetHandler("new_player", [&](sio::event & e) {
		m_gameContext.ProcessInitMessage(e.get_message()->get_string());
	});
	m_socketMaster.SetHandler("update_data", [&](sio::event & e) {
		m_gameContext.ProcessUpdateData(e.get_message()->get_string());
	});
	m_menuBackground.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_menuBackground.setTexture(m_assets.MENU_BACKGROUND_TEXTURE);

	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(FRAME_LIMIT);
	const auto icon = m_assets.WINDOW_ICON;
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));

	m_text.setFont(m_assets.ARIAL_FONT);
	m_text.setCharacterSize(30);
	m_stringWithText = "";

	m_audioPlayer.SetVolume(100);
}

void Game::DoGameLoop()
{
	SceneInfo info = SceneInfo(SceneType::StartScene);
	while (m_window.isOpen())
	{
		const auto deltaTime = m_clock.getElapsedTime().asSeconds();

		switch (info.nextSceneType)
		{
		case SceneType::StartScene:
			info = m_startGameScene.Advance(deltaTime, m_socketMaster.IsConnected());
			break;
		case SceneType::GameScene:
			info = m_gameScene.Advance(deltaTime);
			break;
		case SceneType::PauseScene:
			info = m_pauseScene.Advance(deltaTime);
			break;
		case SceneType::GameOverScene:
			info = m_gameoverScene.Advance(deltaTime);
			break;
		}
		/*if (IsConnected())
		{
			CheckEvents();
			Update();
			m_window.setView(m_view);
			Draw();
			m_window.display();
		}
		else
		{
			CheckEvents();
			m_text.setPosition(100.f, 400.f);
			m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
			m_window.setView(m_view);
			m_window.draw(m_menuBackground);
			m_window.draw(m_text);
			m_window.display();
		}*/
	}
}

void Game::Update()
{
	m_gameContext.Update(m_view, m_ipClient);
}

void Game::CheckEvents()
{
	sf::Event event;
	if (m_window.pollEvent(event))
	{
		CheckInputText(event);
		CheckKeyboardEvent(event);
		
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
			_exit(0);
		}
	}
}

void Game::CheckInputText(const sf::Event & event)
{
	if (event.type == sf::Event::TextEntered && !IsConnected())
	{
		const auto codeKey = event.text.unicode;
		if (codeKey < 128)
		{
			if (codeKey == int(CodeKey::BackSpace))
			{
				if (!m_stringWithText.empty())
				{
					m_stringWithText.pop_back();
				}
			}
			else
			{
				m_stringWithText += static_cast<char>(codeKey);
			}
			m_text.setString(m_stringWithText);
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
		CheckSpecialKey(event);
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
		SendKeyMap(CodeKey::A, isPressed);
		break;
	case sf::Keyboard::D:
		SendKeyMap(CodeKey::D, isPressed);
		break;
	case sf::Keyboard::W:
		SendKeyMap(CodeKey::W, isPressed);
		break;
	case sf::Keyboard::S:
		SendKeyMap(CodeKey::S, isPressed);
		break;
	}
}

void Game::CheckDirection(const sf::Event & event, bool isPressed)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		SendKeyMap(CodeKey::ArrowUp, isPressed);
		break;
	case sf::Keyboard::Down:
		SendKeyMap(CodeKey::ArrowDown, isPressed);
		break;
	case sf::Keyboard::Left:
		SendKeyMap(CodeKey::ArrowLeft, isPressed);
		break;
	case sf::Keyboard::Right:
		SendKeyMap(CodeKey::ArrowRight, isPressed);
		break;
	}
}


void Game::CheckSpecialKey(const sf::Event & event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::K:
		ChangeStatusAudioPlayer();
		break;
	case sf::Keyboard::J:
		m_audioPlayer.PlayNextTrack();
		break;
	case sf::Keyboard::L:
		m_audioPlayer.PlayPrevTrack();
		break;
	case sf::Keyboard::Tab:
		break;
	case sf::Keyboard::Escape:
		//m_nextSceneType = SceneType::PauseScene;
		break;
	}
}

void Game::ChangeStatusAudioPlayer()
{
	if (m_audioPlayer.IsPaused())
	{
		m_audioPlayer.Resume();
	}
	else
	{
		m_audioPlayer.Pause();
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

void Game::SendKeyMap(const CodeKey & keyCode, const bool & isPressed)
{
	json message;
	message["key"] = keyCode;
	message["isPressed"] = isPressed;
	m_socketMaster.Emit("keyMap", message.dump());
}
