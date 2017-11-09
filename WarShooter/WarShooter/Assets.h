#pragma once

struct CAssets
{
public:
	CAssets();
	~CAssets();

	void AddTexture(sf::Texture & texture, const std::string & path);
	void AddRepeatedTexture(sf::Texture & texture, const std::string & path);
	void AddImage(sf::Image & image, const std::string & path);

	sf::Texture BACKGROUND_TEXTURE;
	sf::Texture PLAYER_TEXTURE;
	sf::Texture BLOCK_TEXTURE;
	
	sf::Image WINDOW_ICON;

private:
};
