#include "stdafx.h"
#include "Assets.h"

Assets::Assets()
{
	addRepeatedTexture(m_backgroundTexture, "images/background.jpg");
	addTexture(m_playerTexture, "images/player.png");
	addTexture(m_blockTexture, "images/block.png");
}


void Assets::addTexture(sf::Texture & texture, std::string string)
{
	if (!texture.loadFromFile(string))
	{
		_exit(-1);
	}

	texture.setSmooth(true);
	texture.setRepeated(false);
}

void Assets::addRepeatedTexture(sf::Texture & texture, std::string string)
{
	addTexture(texture, string);
	texture.setRepeated(true);
}

sf::Texture Assets::getTextureBlock()
{
	return m_blockTexture;
}

sf::Texture Assets::getTexturePlayer()
{
	return m_playerTexture;
}