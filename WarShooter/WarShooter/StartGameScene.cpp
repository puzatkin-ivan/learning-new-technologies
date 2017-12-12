#include "stdafx.h"

#include "StartGameScene.h"

namespace
{

static const std::string DEFALUT_INPUT_STRING = "Enter Your Nickname";

static const auto POSITION_MESSAGE = sf::Vector2f({ 100.f, 200.f });

static const auto COLOR_MESSAGE = sf::Color::Red;

static const unsigned CHARACTER_SIZE_MESSAGE = 14;

static const unsigned CHARACTER_SIZE_NICKNAME = 30;

static const auto TEXT_TITLE = "WarShooter 2.0";

static const auto POSITION_TITLE = sf::Vector2f({ 0.f, 250.f });

static const auto COLOR_TITLE = sf::Color::White;

static const auto CHARACTER_SIZE_TITLE = 75;

static const unsigned MAX_VALUE_RANGE_CHARACTERS = 128;

static const auto MESSAGE_NO_COONECTION_SERVER = "No Connection to the Server";

static const auto MESSAGE_NO_NICKNAME = "No Entered Nickname";

}

StartGameScene::StartGameScene(sf::RenderWindow & window, SAssets & assets, SocketMaster & socketMaster, CAudioPlayer & audioPlayer)
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
	m_nickname.setCharacterSize(CHARACTER_SIZE_NICKNAME);

	m_message.setFont(m_assets.ARIAL_FONT);
	m_message.setCharacterSize(CHARACTER_SIZE_MESSAGE);
	m_message.setPosition(POSITION_MESSAGE);
	m_message.setFillColor(COLOR_MESSAGE);

	m_title.setFont(m_assets.BREE_SERIF_FONT);
	m_title.setString(TEXT_TITLE);;
	m_title.setPosition(POSITION_TITLE);
	m_title.setFillColor(COLOR_TITLE);
	m_title.setCharacterSize(CHARACTER_SIZE_TITLE);

	m_nextSceneType = SceneType::StartScene;
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
		}
	}
}

void StartGameScene::CheckInputText(const sf::Event & event)
{
	if (event.type == sf::Event::TextEntered)
	{
		const auto codeKey = event.text.unicode;
		if (codeKey < MAX_VALUE_RANGE_CHARACTERS)
		{
			if (codeKey == int(ASCIICodeKey::BackSpace))
			{
				if (!m_textNickname.empty() && m_textNickname != DEFALUT_INPUT_STRING)
				{
					m_textNickname.pop_back();
				}
				else
				{
					m_textNickname.clear();
				}
			}
			else if (codeKey != int(ASCIICodeKey::Enter) && codeKey != int(ASCIICodeKey::Ctrl_Enter))
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
			ChangeBehaviorAudioPlayer();
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

void StartGameScene::ChangeBehaviorAudioPlayer()
{
	m_audioPlayer.IsPaused() ? m_audioPlayer.Resume() : m_audioPlayer.Pause();
}

void StartGameScene::Update(float dt, bool isConnected)
{
	(void)&dt;
	if (isConnected && m_isNextScene && isNicknameStringEmpty())
	{
		m_nextSceneType = SceneType::GameScene;
		m_socketMaster.Emit(NICKNAME, m_textNickname);
	}
	else if (m_isNextScene)
	{
		if (!isConnected)
		{
			m_message.setString(MESSAGE_NO_COONECTION_SERVER);
		}
		else
		{
			m_message.setString(MESSAGE_NO_NICKNAME);
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

bool StartGameScene::isNicknameStringEmpty() const
{
	return (!m_textNickname.empty() && (m_textNickname != DEFALUT_INPUT_STRING));
}

std::string StartGameScene::GetNickname() const
{
	return m_textNickname;
}
