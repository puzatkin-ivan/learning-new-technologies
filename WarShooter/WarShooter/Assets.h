#pragma once

struct CAssets
{
public:
	CAssets();
	~CAssets();

	void AddTexture(sf::Texture & texture, const std::string & path);
	void AddRepeatedTexture(sf::Texture & texture, const std::string & path);
	void AddImage(sf::Image & image, const std::string & path);

	void AddFont(sf::Font & font, std::string string);

	sf::Texture BACKGROUND_TEXTURE;
	sf::Texture PLAYER_TEXTURE;
	sf::Texture BLOCK_TEXTURE;
	sf::Texture BULLET_TEXTURE;
	sf::Texture MENU_BACKGROUND_TEXTURE;
	
	sf::Image WINDOW_ICON;

	sf::Font ARIAL_FONT;
	sf::Font CRETE_ROUND_FONT;
private:
};
