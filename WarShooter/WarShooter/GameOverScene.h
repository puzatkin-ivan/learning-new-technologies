#pragma once

#include "Assets.h"
#include "sheet.h"
#include "GameContext.h"
#include "SocketMaster.h"
#include <AudioPlayer.h>

class GameOverScene
{
public:
	GameOverScene() = delete;
	GameOverScene(sf::RenderWindow & window, GameContext & gameContext, SocketMaster & socketMaster, SAssets & assets, CAudioPlayer & audioPlayer);
	~GameOverScene() = default;

	SceneInfo Advance(float dt, const std::string & ip);
private:
	void CheckEvents();
	void CheckSpecialKeys(const sf::Event & event);
	void ChangeTypeScene();
	void ChangeStatusAudioPlayer();
	void SendKey(const CodeKey & keyCode);

	void Draw();
	void Update(float dt, const std::string & ip);

	sf::RenderWindow & m_window;
	sf::View m_view;
	sf::Sprite m_background;
	sf::Text m_title;
	SocketMaster & m_socketMaster;
	SAssets & m_assets;
	GameContext & m_gameContext;
	CAudioPlayer & m_audioPlayer;

	SceneType m_nextSceneType;
};
