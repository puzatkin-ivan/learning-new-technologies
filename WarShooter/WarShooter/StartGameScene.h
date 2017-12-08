#pragma once
#include "Assets.h"
#include "sheet.h"
#include "SocketMaster.h"
#include <AudioPlayer.h>

class StartGameScene
{
public:
	StartGameScene() = delete;
	StartGameScene(sf::RenderWindow & window, CAssets & assets, SocketMaster & socketMaster, CAudioPlayer & audioPlayer);

	SceneInfo Advance(float dt, bool isConnected);
	std::string GetNickname() const;

private:
	void CheckEvents();
	void CheckInputText(const sf::Event & event);
	void CheckSpecialKeys(const sf::Event & event);
	void ChangeStatusAudioPlayer();
	void Update(float dt, bool isConnected);
	void Draw();

	bool isNoEmptyStringNickname() const;

	sf::RenderWindow & m_window;
	sf::View m_view;
	CAssets & m_assets;
	SocketMaster & m_socketMaster;
	CAudioPlayer & m_audioPlayer;
	
	sf::Sprite m_background;

	sf::Text m_nickname;
	sf::Text m_title;
	sf::Text m_message;

	SceneType m_nextSceneType;
	bool  m_isNextScene = false;
	std::string m_stringWithMessage;
	std::string m_textNickname;
};
