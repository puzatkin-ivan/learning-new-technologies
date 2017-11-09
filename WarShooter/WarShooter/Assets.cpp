#include "stdafx.h"
#include "Assets.h"

CAssets::CAssets()
{
	AddRepeatedTexture(BACKGROUND_TEXTURE, "images/background.jpg");
	AddTexture(PLAYER_TEXTURE, "images/player.png");
	AddTexture(BLOCK_TEXTURE, "images/block.png");
	AddImage(WINDOW_ICON, "images/icon.png");
}

CAssets::~CAssets()
{
}

void CAssets::AddTexture(sf::Texture & texture, const std::string & path)
{
	if (!texture.loadFromFile(path))
	{
		MessageBoxA(nullptr, std::string("File " + path + " not founded").c_str(), "Error", MB_ICONERROR | MB_OK);
		_exit(-1);
	}

	texture.setSmooth(true);
	texture.setRepeated(false);
}

void CAssets::AddRepeatedTexture(sf::Texture & texture, const std::string & path)
{
	AddTexture(texture, path);
	texture.setRepeated(true);
}

void CAssets::AddImage(sf::Image & image, const std::string & path)
{
	if (!image.loadFromFile(path))
	{
		MessageBoxA(nullptr, std::string("File " + path + " not founded").c_str(), "Error", MB_ICONERROR | MB_OK);
		_exit(-1);
	}
}
