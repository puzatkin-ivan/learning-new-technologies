#pragma once

#include <AudioPlayer.h>

#include "Assets.h"
#include "sheet.h"
#include "SocketMaster.h"

class StartGameScene
{
public:
	StartGameScene() = delete;
	StartGameScene(sf::RenderWindow & window, SAssets & assets, SocketMaster & socketMaster, CAudioPlayer & audioPlayer);
	~StartGameScene() = default;

	SceneInfo Advance(float dt, bool isConnected);
	std::string GetNickname() const;

private:
	void CheckEvents();
	void CheckInputText(const sf::Event & event);
	void CheckSpecialKeys(const sf::Event & event);
	void ResumePauseAudio();
	void Update(float dt, bool isConnected);
	void Draw() const;

	bool IsNicknameStringEmpty() const;

	sf::RenderWindow & m_window;
	sf::View m_view;
	SAssets & m_assets;
	SocketMaster & m_socketMaster;
	CAudioPlayer & m_audioPlayer;
	
	sf::Sprite m_background;

	sf::Text m_nickname;
	sf::Text m_title;
	sf::Text m_message;

	SceneType m_nextSceneType;
	bool m_isNextScene;
	std::string m_stringWithMessage;
	std::string m_textNickname;
};
