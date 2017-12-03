#pragma once
#include "Assets.h"
#include "sheet.h"
#include "GameContext.h"
#include <AudioPlayer.h>

class GameOverScene
{
public:
	GameOverScene(sf::RenderWindow & window, GameContext & gameContext, CAssets & assets);

	SceneInfo Advance(float dt);
private:
	void CheckEvents();
	void CheckSpecialKeys(const sf::Event & event);
	void ChangeTypeScene();
	void ChangeStatusAudioPlayer();

	void Draw();
	void Update(float dt);

	sf::RenderWindow & m_window;
	sf::View m_view;
	sf::Sprite m_background;
	sf::Text m_title;

	CAssets & m_assets;
	GameContext & m_gameContext;
	CAudioPlayer m_audioPlayer;

	SceneType m_nextSceneType;
};