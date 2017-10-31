#pragma once

struct CAssets
{
public:
	CAssets();
	~CAssets();

	void addTexture(sf::Texture & texture, const std::string & path);
	void addRepeatedTexture(sf::Texture & texture, std::string string);

	sf::Texture BACKGROUND_TEXTURE;
	sf::Texture PLAYER_TEXTURE;
	sf::Texture BLOCK_TEXTURE;

private:
};
