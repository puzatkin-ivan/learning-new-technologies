#include "stdafx.h"
#include "Game.h"

const sf::Color WINDOW_COLOR = sf::Color::White;
const sf::String WINDOW_TITLE = "WarShooter 2.0";
const std::string FOLDER_WITH_MUSIC = "sounds/";

using json = nlohmann::json;

namespace
{
	static const auto PORT = "http://127.0.0.1:3000";
}

Game::Game()
	:m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_TITLE, sf::Style::Close)
	,m_gameContext(m_assets)
	,m_socketMaster(PORT)
	,m_audioPlayer(FOLDER_WITH_MUSIC)
	,m_startGameScene(m_window, m_assets, m_socketMaster, m_audioPlayer)
	,m_gameScene(m_window, m_gameContext, m_socketMaster, m_audioPlayer)
	,m_pauseScene(m_window, m_assets)
	,m_gameoverScene(m_window, m_gameContext, m_socketMaster, m_assets, m_audioPlayer)
{
	m_socketMaster.SetHandler("new_player", [&](sio::event & e) {
		m_gameContext.ProcessInitMessage(e.get_message()->get_string());
	});
	m_socketMaster.SetHandler("update_data", [&](sio::event & e) {
		m_gameContext.ProcessUpdateData(e.get_message()->get_string());
	});

	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(FRAME_LIMIT);

	const auto icon = m_assets.WINDOW_ICON;
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	m_audioPlayer.Pause();
	m_audioPlayer.SetVolume(100);
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
		}
	}
}
