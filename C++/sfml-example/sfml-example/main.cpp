#include "stdafx.h"
#include "HouseOnTheLawn.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "House on the lawn");
	window.setFramerateLimit(60);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.setVerticalSyncEnabled(true);
	}
    return 0;
}
