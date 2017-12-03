#pragma once
#include "Assets.h"
#include "sheet.h"
#include <AudioPlayer.h>

class StartGameScene
{
public:
	StartGameScene() = delete;
	StartGameScene(sf::RenderWindow & window, CAssets & assets, CAudioPlayer & audioPlayer);

	SceneInfo Advance(float dt, bool isConnected);
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
	sf::Sprite m_background;

	CAudioPlayer & m_audioPlayer;
	sf::Text m_text;
	sf::Text m_title;

	std::string m_stringWithText;
	SceneType m_nextSceneType;
	bool  m_isNextScene = false;
};
