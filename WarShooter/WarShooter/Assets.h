#pragma once
#include "sheet.h"

struct Assets
{
public:
	Assets();

	void addTexture(sf::Texture & texture, std::string string);
	void addRepeatedTexture(sf::Texture & texture, std::string string);

	sf::Texture getTexturePlayer();
	sf::Texture getTextureBlock();

private:
	sf::Texture m_backgroundTexture;
	sf::Texture m_playerTexture;
	sf::Texture m_blockTexture;
};
