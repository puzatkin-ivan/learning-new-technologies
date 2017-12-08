#include "stdafx.h"

#include "StartGameScene.h"

const std::string DEFALUT_INPUT_STRING = "Enter Your Nickname";

StartGameScene::StartGameScene(sf::RenderWindow & window, CAssets & assets, SocketMaster & socketMaster, CAudioPlayer & audioPlayer)
	:m_window(window)
	,m_assets(assets)
	,m_socketMaster(socketMaster)
	,m_audioPlayer(audioPlayer)
{
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));

	m_background.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	m_background.setTexture(m_assets.MENU_BACKGROUND_TEXTURE);

	m_textNickname = DEFALUT_INPUT_STRING;

	m_nickname.setFont(m_assets.ARIAL_FONT);
	m_nickname.setString(m_textNickname);
	m_nickname.setPosition(TEXT_POSITION);
	m_nickname.setCharacterSize(30);

	m_message.setFont(m_assets.ARIAL_FONT);
	m_message.setCharacterSize(14);
	m_message.setPosition({ 100.f, 200.f });
	m_message.setFillColor(sf::Color::Red);

	m_title.setFont(m_assets.CRETE_ROUND_FONT);
	m_title.setString("WarShooter 2.0");;
	m_title.setPosition({ 0.f, 250.f });
	m_title.setFillColor(sf::Color::White);
	m_title.setCharacterSize(75);
}

SceneInfo StartGameScene::Advance(float dt, bool isConnected)
{
	m_nextSceneType = SceneType::StartScene;
	m_isNextScene = false;
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
				if (!m_textNickname.empty() && m_textNickname != DEFALUT_INPUT_STRING)
				{
					m_textNickname.pop_back();
				}
				else
				{
					m_textNickname = "";
				}
			}
			else if (codeKey != 10 && codeKey != 13)
			{
				if (m_textNickname == DEFALUT_INPUT_STRING)
				{
					m_textNickname = static_cast<char>(codeKey);
				}
				else
				{
					m_textNickname += static_cast<char>(codeKey);
				}
			}
			m_nickname.setString(m_textNickname);
		}
	}
}

void StartGameScene::CheckSpecialKeys(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Return:
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
		m_socketMaster.Emit("nickname", m_textNickname);
	}
	else if (m_isNextScene)
	{
		if (!isConnected)
		{
			m_message.setString("No Connection to the Server");
		}
		else
		{
			m_message.setString("No Entered Nickname");
		}
	}
}

void StartGameScene::Draw()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_background);
	m_window.draw(m_nickname);
	m_window.draw(m_title);
	m_window.draw(m_message);
}

bool StartGameScene::isNoEmptyStringNickname() const
{
	return (!m_textNickname.empty() && m_textNickname != DEFALUT_INPUT_STRING);
}

std::string StartGameScene::GetNickname() const
{
	return m_textNickname;
}
