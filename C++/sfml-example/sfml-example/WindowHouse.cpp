#include "stdafx.h"
#include "WindowHouse.h"

WindowHouse::WindowHouse()
{
	width = 50; 
	height = 100;
	windowHouse1.setSize({ width, height });
	windowHouse2.setSize({ width, height });
	windowHouse3.setSize({ width, height });
	
	windowHouse1.setPosition({ 200, 300 });
	windowHouse2.setPosition({ 275, 300 });
	windowHouse3.setPosition({ 350, 300 });
	windowHouse1.setFillColor(WHITE);
}

void WindowHouse::Draw(sf::RenderWindow & window)
{
	window.draw(windowHouse1);
	window.draw(windowHouse2);
	window.draw(windowHouse3);
}