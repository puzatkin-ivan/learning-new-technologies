#pragma once

struct SAssets
{
public:
	SAssets();
	~SAssets() = default;

	void AddTexture(sf::Texture & texture, const std::string & path);
	void AddRepeatedTexture(sf::Texture & texture, const std::string & path);
	void AddImage(sf::Image & image, const std::string & path);

	void AddFont(sf::Font & font, const std::string & string);

	sf::Texture BACKGROUND_TEXTURE;
	sf::Texture PLAYER_SWAT_TEXTURE;
	sf::Texture PLAYER_KNIGHT_TEXTURE;
	sf::Texture PLAYER_BIKER_TEXTURE;
	sf::Texture PLAYER_HUMAN_TEXTURE;
	sf::Texture BLOCK_TEXTURE;
	sf::Texture BULLET_TEXTURE;
	sf::Texture MENU_BACKGROUND_TEXTURE;
	
	sf::Image WINDOW_ICON;

	sf::Font ARIAL_FONT;
	sf::Font BREE_SERIF_FONT;

private:
};
