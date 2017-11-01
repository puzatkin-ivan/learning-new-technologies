#include "stdafx.h"
#include "Assets.h"

CAssets::CAssets()
{
	addRepeatedTexture(BACKGROUND_TEXTURE, "images/background.jpg");
	addTexture(PLAYER_TEXTURE, "images/player.png");
	addTexture(BLOCK_TEXTURE, "images/block.png");
}

CAssets::~CAssets()
{
}

void CAssets::addTexture(sf::Texture & texture, const std::string & path)
{
	if (!texture.loadFromFile(path))
	{
		MessageBoxA(nullptr, std::string("File " + path + " not founded").c_str(), "Error", MB_ICONERROR | MB_OK);
		_exit(-1);
	}

	texture.setSmooth(true);
	texture.setRepeated(false);
}

void CAssets::addRepeatedTexture(sf::Texture & texture, std::string string)
{
	addTexture(texture, string);
	texture.setRepeated(true);
}
