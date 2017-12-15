#include "stdafx.h"

#include "Assets.h"

namespace
{

static const std::string IMG_PATH = "images/";

static const std::string PATH_FONTS = "fonts/";

}

SAssets::SAssets()
{
	AddRepeatedTexture(BACKGROUND_TEXTURE, IMG_PATH + "background.jpg");
	AddRepeatedTexture(MENU_BACKGROUND_TEXTURE, IMG_PATH + "menu_background.jpg");
	AddTexture(PLAYER_SWAT_TEXTURE, IMG_PATH + "player.png");
	AddTexture(PLAYER_KNIGHT_TEXTURE, IMG_PATH + "player2.png");
	AddTexture(PLAYER_BIKER_TEXTURE, IMG_PATH + "player3.png");
	AddTexture(PLAYER_HUMAN_TEXTURE, IMG_PATH + "player4.png");
	AddTexture(BLOCK_TEXTURE, IMG_PATH + "block.png");
	AddTexture(BULLET_TEXTURE, IMG_PATH + "bullet.png");
	AddImage(WINDOW_ICON, IMG_PATH + "icon.png");

	AddFont(ARIAL_FONT, PATH_FONTS + "arial.ttf");
	AddFont(BREE_SERIF_FONT, PATH_FONTS + "BreeSerif.ttf");
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
