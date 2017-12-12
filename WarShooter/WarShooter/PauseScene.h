#pragma once

#include <AudioPlayer.h>
#include "sheet.h"

class PauseScene
{
public:
	PauseScene() = delete;
	PauseScene(sf::RenderWindow & window, SAssets & assets, CAudioPlayer & audioPlayer);
	~PauseScene() = default;

	SceneInfo Advance(float dt);

private:
	void CheckEvents();
	void CheckSpecialKey(const sf::Event & event);
	void ChangeBehaviorAudioPlayer();

	void Draw();
	void Update(float dt);

	sf::RenderWindow & m_window;
	sf::View m_view;
	sf::Sprite m_background;
	sf::Text m_title;

	SAssets & m_assets;
	CAudioPlayer & m_audioPlayer;

	SceneType m_nextSceneType;
};
