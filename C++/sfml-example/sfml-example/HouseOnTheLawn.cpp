#include "stdafx.h"
#include "HouseOnTheLawn.h"

HouseOnTheLawn::HouseOnTheLawn()
{

}

void HouseOnTheLawn::DrawLoop(sf::RenderWindow & window)
{
	window.clear();
	window.draw(sky);
	window.draw(lawn);
	window.draw(house);
	window.draw(chimney);
	window.draw(roof);
	windowsHouse.Draw(window);

	window.display();
}