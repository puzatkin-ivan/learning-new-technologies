#include "stdafx.h"

#include "GameScene.h"

using json = nlohmann::json;

namespace
{

static const sf::Color WINDOW_COLOR = sf::Color::White;

}

GameScene::GameScene(sf::RenderWindow & window, GameContext & gameContext, SocketMaster & socketMaster, CAudioPlayer & audioPlayer)
	:m_window(window)
	,m_audioPlayer(audioPlayer)
	,m_gameContext(gameContext)
	,m_socketMaster(socketMaster)
{
	m_nextSceneType = SceneType::GameScene;
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(FRAME_LIMIT);

	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));

	m_isDrawTable = false;
}

SceneInfo GameScene::Advance(float dt)
{
	m_nextSceneType = SceneType::GameScene;
	CheckEvents();
	Update(dt);
	m_window.setView(m_view);
	Draw();
	m_window.display();

	return SceneInfo(m_nextSceneType);
}

void GameScene::Update(float deltaTime)
{
	(void)&deltaTime;

	m_gameContext.Update(m_view, m_socketMaster.GetSessionId());
	if (m_gameContext.isClientDead())
	{
		m_nextSceneType = SceneType::GameOverScene;
	}
}

void GameScene::Draw()
{
	m_window.clear(WINDOW_COLOR);
	m_gameContext.Draw(m_window, m_isDrawTable);
}

void GameScene::CheckEvents()
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

void GameScene::CheckKeyboardEvent(const sf::Event & event)
{
	CheckKeyPressed(event);
	CheckKeyReleased(event);
}

void GameScene::CheckKeyPressed(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		const auto isPressed = true;
		CheckMovement(event, isPressed);
		CheckDirection(event, isPressed);
		if (event.key.code == sf::Keyboard::Tab)
		{
			m_isDrawTable = isPressed;
		}
	}
}

void GameScene::CheckKeyReleased(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		const auto isReleased = false;
		CheckMovement(event, isReleased);
		CheckDirection(event, isReleased);
		CheckSpecialKey(event, isReleased);
		if (event.key.code == sf::Keyboard::Tab)
		{
			m_isDrawTable = isReleased;
		}
	}
}

void GameScene::CheckMovement(const sf::Event & event, bool isPressed)
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

void GameScene::CheckDirection(const sf::Event & event, bool isPressed)
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

void GameScene::SendKeyMap(const CodeKey & keyCode, bool isPressed)
{
	json message;
	message["key"] = keyCode;
	message["isPressed"] = isPressed;
	m_socketMaster.Emit("keyMap", message.dump());
}

void GameScene::CheckSpecialKey(const sf::Event & event, bool isPressed)
{
	(void)&isPressed;

	switch (event.key.code)
	{
	case sf::Keyboard::F10:
		ChangeStatusAudioPlayer();
		break;
	case sf::Keyboard::F9:
		m_audioPlayer.PlayNextTrack();
		break;
	case sf::Keyboard::F11:
		m_audioPlayer.PlayPrevTrack();
		break;
	case sf::Keyboard::Escape:
		m_nextSceneType = SceneType::PauseScene;
		break;
	}
}

void GameScene::ChangeStatusAudioPlayer()
{
	m_audioPlayer.IsPaused() ? m_audioPlayer.Resume() : m_audioPlayer.Pause();
}
