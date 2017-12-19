#include "stdafx.h"

#include "PauseScene.h"

namespace
{

static const sf::Vector2f POSITION_TITLE = { 100.f, 100.f };

static const auto COLOR_TITLE = sf::Color::White;

static const auto CONTENT_TITLE = "Pause Game";

static const unsigned CHARACTER_SIZE = 50;

static const auto WINDOW_COLOR = sf::Color::White;

}

PauseScene::PauseScene(sf::RenderWindow & window, SAssets & assets, CAudioPlayer & audioPlayer)
	:m_assets(assets)
	,m_window(window)
	,m_audioPlayer(audioPlayer)
{
	m_nextSceneType = SceneType::PauseScene;
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.MENU_BACKGROUND_TEXTURE); 
	
	m_title.setFont(m_assets.BREE_SERIF_FONT);
	m_title.setPosition(POSITION_TITLE);
	m_title.setFillColor(COLOR_TITLE);
	m_title.setCharacterSize(CHARACTER_SIZE);
	m_title.setString(CONTENT_TITLE);
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

void PauseScene::Draw() const
{
	m_window.clear(WINDOW_COLOR);
	m_window.draw(m_background);
	m_window.draw(m_title);
}

void PauseScene::ResumePauseAudio()
{
	m_audioPlayer.IsPaused() ? m_audioPlayer.Resume() : m_audioPlayer.Pause();
}

void PauseScene::CheckSpecialKey(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::F10:
			ResumePauseAudio();
			break;
		case sf::Keyboard::F11:
			m_audioPlayer.PlayNextTrack();
			break;
		case sf::Keyboard::F9:
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
