#include "stdafx.h"
#include "Cloud.h"

const unsigned NUMBER_PARTS = 3;

Cloud::Cloud()
{
	for (int i = 0; i < NUMBER_PARTS; ++i)
	{
		sf::CircleShape part(30);
		part.setPosition();
		m_body.push_back(part);
	}
}

void Cloud::Draw(sf::RenderWindow & window)
{
	for (auto & pathCloud : m_body)
	{
		window.draw(pathCloud);
	}
}
