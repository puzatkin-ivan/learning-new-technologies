#include "stdafx.h"
#include "Cloud.h"

Cloud::Cloud()
{
	
}

void Cloud::Draw(sf::RenderWindow & window)
{
	window.draw(cloud1);
	window.draw(cloud2);
	window.draw(cloud3);
}