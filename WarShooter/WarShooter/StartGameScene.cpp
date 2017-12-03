#include "stdafx.h"

#include "StartGameScene.h"

const std::string DEFALUT_INPUT_STRING = "Enter Your Nickname";

StartGameScene::StartGameScene(sf::RenderWindow & window, CAssets & assets, CAudioPlayer & audioPlayer)
	:m_window(window)
	,m_assets(assets)
	,m_audioPlayer(audioPlayer)
{
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));

	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.MENU_BACKGROUND_TEXTURE);

	m_stringWithText = DEFALUT_INPUT_STRING;

	m_text.setFont(m_assets.ARIAL_FONT);
	m_text.setString(m_stringWithText);
	m_text.setPosition(TEXT_POSITION);
	m_text.setCharacterSize(30);


	m_title.setFont(m_assets.ARIAL_FONT);
	m_title.setPosition({ 100.f, 100.f });
	m_title.setFillColor(sf::Color::Yellow);
	m_title.setCharacterSize(50);
	m_title.setString("Start Menu Game");
}

SceneInfo StartGameScene::Advance(float dt, bool isConnected)
{
	m_nextSceneType = SceneType::StartScene;
	CheckEvents();
	Update(dt, isConnected);
	m_window.setView(m_view);
	Draw();
	m_window.display();

	return SceneInfo(m_nextSceneType);
}

void StartGameScene::CheckEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		CheckInputText(event);
		CheckSpecialKeys(event);
		
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
			_exit(0);
		}
	}
}

void StartGameScene::CheckInputText(const sf::Event & event)
{
	if (event.type == sf::Event::TextEntered)
	{
		const auto codeKey = event.text.unicode;
		if (codeKey < 128)
		{
			if (codeKey == int(CodeKey::BackSpace))
			{
				if (!m_stringWithText.empty() && m_stringWithText != DEFALUT_INPUT_STRING)
				{
					m_stringWithText.pop_back();
				}
				else
				{
					m_stringWithText = "";
				}
			}
			else
			{
				if (m_stringWithText == DEFALUT_INPUT_STRING)
				{
					m_stringWithText = "";
				}
				m_stringWithText += static_cast<char>(codeKey);
			}
			m_text.setString(m_stringWithText);
		}
	}
}

void StartGameScene::CheckSpecialKeys(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::F5:
			m_isNextScene = true;
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

void StartGameScene::ChangeStatusAudioPlayer()
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

void StartGameScene::Update(float dt, bool isConnected)
{
	(void)&dt;
	if (isConnected && m_isNextScene && isNoEmptyStringNickname())
	{
		m_nextSceneType = SceneType::GameScene;
	}
}

void StartGameScene::Draw()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_background);
	m_window.draw(m_text);
	m_window.draw(m_title);
}

bool StartGameScene::isNoEmptyStringNickname() const
{
	return (!m_stringWithText.empty() && m_stringWithText != DEFALUT_INPUT_STRING);
}
