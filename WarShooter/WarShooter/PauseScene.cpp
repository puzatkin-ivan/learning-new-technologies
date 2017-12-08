#include "stdafx.h"
#include "PauseScene.h"

PauseScene::PauseScene(sf::RenderWindow & window, CAssets & assets)
	:m_assets(assets)
	, m_window(window)
	, m_audioPlayer("sounds/")
{
	m_nextSceneType = SceneType::PauseScene;
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.MENU_BACKGROUND_TEXTURE); 
	
	m_title.setFont(m_assets.CRETE_ROUND_FONT);
	m_title.setPosition({ 100.f, 100.f });
	m_title.setFillColor(sf::Color::White);
	m_title.setCharacterSize(50);
	m_title.setString("Pause Game");
}

SceneInfo PauseScene::Advance(float dt)
{
	m_nextSceneType = SceneType::PauseScene;
	CheckEvents();
	Update(dt);
	m_window.setView(m_view);
	Draw();
	m_window.display();

	return SceneInfo(m_nextSceneType);
}

void PauseScene::CheckEvents()
{
	sf::Event event;
	if (m_window.pollEvent(event))
	{
		CheckSpecialKey(event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void PauseScene::Update(float dt)
{
	(void)&dt;
}

void PauseScene::Draw()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_background);
	m_window.draw(m_title);
}

void PauseScene::ChangeStatusAudioPlayer()
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

void PauseScene::CheckSpecialKey(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
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
			m_nextSceneType = SceneType::GameScene;
			break;
		}
	}
}
