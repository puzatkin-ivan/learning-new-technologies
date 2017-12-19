#include "stdafx.h"

#include "GameOverScene.h"

using json = nlohmann::json;

namespace
{

static const sf::Vector2f POSITION_TITLE = { 100.f, 100.f };

static const auto COLOR_TITLE = sf::Color::White;

static const auto CONTENT_TITLE = "GameOver";

static const unsigned CHARACTER_SIZE = 50;

static const auto WINDOW_COLOR = sf::Color::White;

}

GameOverScene::GameOverScene(sf::RenderWindow & window, GameContext & gameContext, SocketMaster & socketMaster, SAssets & assets, CAudioPlayer & audioPlayer)
	:m_window(window)
	,m_gameContext(gameContext)
	,m_socketMaster(socketMaster)
	,m_assets(assets)
	,m_audioPlayer(audioPlayer)
{
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));

	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.MENU_BACKGROUND_TEXTURE);
	
	m_title.setFont(m_assets.BREE_SERIF_FONT);
	m_title.setPosition(POSITION_TITLE);
	m_title.setFillColor(COLOR_TITLE);
	m_title.setCharacterSize(CHARACTER_SIZE);
	m_title.setString(CONTENT_TITLE);

	m_nextSceneType = SceneType::GameOverScene;
}

SceneInfo GameOverScene::Advance(float dt, const std::string & ip)
{
	m_nextSceneType = SceneType::GameOverScene;
	CheckEvents();
	Update(dt, ip);
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
			ResumePauseAudio();
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
	else
	{
		SendKey(ASCIICodeKey::R);
	}
}

void GameOverScene::ResumePauseAudio()
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

void GameOverScene::Update(float dt, const std::string & ip)
{
	(void)&dt;
	m_gameContext.Update(m_view, ip);
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
}

void GameOverScene::Draw() const
{
	m_window.clear(WINDOW_COLOR);
	m_window.draw(m_background);
	m_window.draw(m_title);
}

void GameOverScene::SendKey(const ASCIICodeKey & keyCode)
{
	json message;
	message[MESSAGE_KEY] = keyCode;
	message[MESSAGE_KEY_PRESSED] = true;
	m_socketMaster.Emit(MESSAGE_KEY_MAP, message.dump());
}
