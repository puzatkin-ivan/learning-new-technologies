#include "stdafx.h"

#include "Assets.h"

namespace
{

static const auto PATH_TO_BACKGROUND = "images/background.jpg";

static const auto PATH_TO_MENU_BACKGROUND = "images/menu_background.jpg";

static const auto PATH_TO_PLAYER_TEXTURE = "images/player.png";

static const auto PATH_TO_BLOCK_TEXTURE = "images/block.png";

static const auto PATH_TO_BULLET_TEXTRURE = "images/bullet.png";

static const auto PATH_TO_WINDOW_ICON = "images/icon.png";

static const auto PATH_TO_ARIAL_FONT = "fonts/arial.ttf";

static const auto PATH_TO_BREE_SERIF_FONT = "fonts/BreeSerif.ttf";

}

SAssets::SAssets()
{
	AddRepeatedTexture(BACKGROUND_TEXTURE, PATH_TO_BACKGROUND);
	AddRepeatedTexture(MENU_BACKGROUND_TEXTURE, PATH_TO_MENU_BACKGROUND);
	AddTexture(PLAYER_TEXTURE, PATH_TO_PLAYER_TEXTURE);
	AddTexture(BLOCK_TEXTURE, PATH_TO_BLOCK_TEXTURE);
	AddTexture(BULLET_TEXTURE, PATH_TO_BULLET_TEXTRURE);
	AddImage(WINDOW_ICON, PATH_TO_WINDOW_ICON);

	AddFont(ARIAL_FONT, PATH_TO_ARIAL_FONT);
	AddFont(BREE_SERIF_FONT, PATH_TO_BREE_SERIF_FONT);
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
