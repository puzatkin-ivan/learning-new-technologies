#include "stdafx.h"

#include "Assets.h"

SAssets::SAssets()
{
	AddRepeatedTexture(BACKGROUND_TEXTURE, "images/background.jpg");
	AddRepeatedTexture(MENU_BACKGROUND_TEXTURE, "images/menu_background.jpg");
	AddTexture(PLAYER_TEXTURE, "images/player.png");
	AddTexture(BLOCK_TEXTURE, "images/block.png");
	AddTexture(BULLET_TEXTURE, "images/bullet.png");
	AddImage(WINDOW_ICON, "images/icon.png");

	AddFont(ARIAL_FONT, "fonts/arial.ttf");
	AddFont(CRETE_ROUND_FONT, "fonts/BreeSerif.ttf");
}

void SAssets::AddTexture(sf::Texture & texture, const std::string & path)
{
	if (!texture.loadFromFile(path))
	{
		MessageBoxA(nullptr, std::string("File " + path + " not founded").c_str(), "Error", MB_ICONERROR | MB_OK);
		_exit(-1);
	}

	texture.setSmooth(true);
	texture.setRepeated(false);
}

void SAssets::AddRepeatedTexture(sf::Texture & texture, const std::string & path)
{
	AddTexture(texture, path);
	texture.setRepeated(true);
}

void SAssets::AddImage(sf::Image & image, const std::string & path)
{
	if (!image.loadFromFile(path))
	{
		MessageBoxA(nullptr, std::string("File " + path + " not founded").c_str(), "Error", MB_ICONERROR | MB_OK);
		_exit(-1);
	}
}

void SAssets::AddFont(sf::Font & font, const std::string & string)
{
	if (!font.loadFromFile(string))
	{
		MessageBoxA(nullptr, "File not founded", "Error", MB_ICONERROR | MB_OK);
		_exit(-1);
	}
}
