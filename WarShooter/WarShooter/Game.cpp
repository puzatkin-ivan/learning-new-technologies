#include "stdafx.h"

#include "Game.h"
#include <AudioController.h>

using json = nlohmann::json;

namespace
{

static const auto PORT = "http://146.185.243.128:3000";

static const sf::Color WINDOW_COLOR = sf::Color::White;

static const sf::String WINDOW_TITLE = "WarShooter 2.0";

static const std::string MUSIC_PATH = "sounds/";

static const unsigned MAX_VOLUME = 100;

static const auto PATH_TO_SOUND_FIRE = "sounds/fire.ogg";

static const auto MESSAGE_NEW_PLAYER = "new_player";

static const auto MESSAGE_UPDATE_DATA = "update_data";

static const auto MESSAGE_FIRE = "fire";
}

Game::Game()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_TITLE, sf::Style::Close)
	,m_gameContext(m_assets)
	,m_socketMaster(PORT)
	,m_audioPlayer(MUSIC_PATH)
	,m_startGameScene(m_window, m_assets, m_socketMaster, m_audioPlayer)
	,m_gameScene(m_window, m_gameContext, m_socketMaster, m_audioPlayer)
	,m_pauseScene(m_window, m_assets, m_audioPlayer)
	,m_gameoverScene(m_window, m_gameContext, m_socketMaster, m_assets, m_audioPlayer)
	,m_audioController(CAudioController::GetInstance())
	,m_sound(PATH_TO_SOUND_FIRE)
{
	m_socketMaster.SetHandler(MESSAGE_NEW_PLAYER, std::bind(&Game::onInitData, this, std::placeholders::_1));
	m_socketMaster.SetHandler(MESSAGE_UPDATE_DATA, std::bind(&Game::onUpdateData, this, std::placeholders::_1));
	m_socketMaster.SetHandler(MESSAGE_FIRE, std::bind(&Game::onSound, this, std::placeholders::_1));

	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(FRAME_LIMIT);

	const auto icon = m_assets.WINDOW_ICON;
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	m_audioPlayer.SetVolume(MAX_VOLUME / 2);
	m_audioController.SetSoundVolume(MAX_VOLUME);
}

Game::~Game()
{
	m_audioPlayer.Stop();
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
			info = m_gameoverScene.Advance(deltaTime, m_socketMaster.GetSessionId());
			break;
		case SceneType::ServerClose:
			info = ProcessClosingConnect();
			break;
		}
	}
}

void Game::onInitData(const sio::event & event)
{
	const auto data = event.get_message()->get_string();
	m_gameContext.ProcessInitMessage(data);
}

void Game::onUpdateData(const sio::event & event)
{
	const auto data = event.get_message()->get_string();
	m_gameContext.ProcessUpdateData(data);
}

SceneInfo Game::ProcessClosingConnect()
{
	m_socketMaster.CloseConnect();
	m_gameContext.Clear();
	m_socketMaster.Connect(PORT);

	return SceneInfo(SceneType::StartScene);
}

void Game::onSound(const sio::event & event)
{
	(void)&event;
	m_audioController.PlayAudio(m_sound);
}
