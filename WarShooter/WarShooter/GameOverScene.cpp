#include "stdafx.h"

#include "GameOverScene.h"

GameOverScene::GameOverScene(sf::RenderWindow & window, GameContext & gameContext, CAssets & assets)
	:m_window(window)
	,m_gameContext(gameContext)
	,m_assets(assets)
	,m_audioPlayer("sounds/")
{
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));

	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.MENU_BACKGROUND_TEXTURE);
	
	m_title.setFont(m_assets.ARIAL_FONT);
	m_title.setPosition({ 100.f, 100.f });
	m_title.setFillColor(sf::Color::Yellow);
	m_title.setCharacterSize(50);
	m_title.setString("GameOver");
}

SceneInfo GameOverScene::Advance(float dt)
{
	m_nextSceneType = SceneType::GameOverScene;
	CheckEvents();
	Update(dt);
	m_window.setView(m_view);
	Draw();
	m_window.display();

	return SceneInfo(m_nextSceneType);
}

void GameOverScene::CheckEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		CheckSpecialKeys(event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
			_exit(0);
		}
	}
}

void GameOverScene::CheckSpecialKeys(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::R:
			ChangeTypeScene();
			break;
		case sf::Keyboard::F10:
			ChangeStatusAudioPlayer();
			break;
		case sf::Keyboard::F9:
			m_audioPlayer.PlayNextTrack();
			break;
		case sf::Keyboard::F11:
			m_audioPlayer.PlayPrevTrack();
			break;
		}
	}
}

void GameOverScene::ChangeTypeScene()
{
	if (!m_gameContext.isClientDead())
	{
		m_nextSceneType = SceneType::GameScene;
	}
}

void GameOverScene::ChangeStatusAudioPlayer()
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

void GameOverScene::Update(float dt)
{
	(void)&dt;
}

void GameOverScene::Draw()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_background);
	m_window.draw(m_title);
}
