#include <iostream>
#include <cmath>
#include "Constants.h"
#include "SFML/Graphics.hpp"

const float kr = 2;
const float ks = 3;
const float pi = 3.14;
const float r = 200;
const int circleCount = 6;


void Draw(sf::RenderWindow& window, double x, 
	double y, double radius, double r1, int depth)
{
	if (!depth)
		return;
	sf::CircleShape circle(radius, 70);
	circle.setOrigin(sf::Vector2f(radius, radius));
	circle.setPosition(sf::Vector2f(x, y));
	window.draw(circle);
	r1 = kr * radius;

	for (auto i = 0; i < circleCount; i++)
	{
		float newX = x + r1 * cos(static_cast<double>(2 * pi * i) 
			/ static_cast<double>(circleCount));
		float newY = y + r1 * sin(static_cast<double>(2 * pi * i) 
			/ static_cast<double>(circleCount));
		Draw(window, newX, newY, radius / ks, r1, depth - 1);
	}
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(1920,
		1080), "Circle", sf::Style::Fullscreen, settings);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}
		window.clear(sf::Color::Black);
		Draw(window, halfWidth, halfHeight, r, 0.0, 5);
		window.display();
	}
	return 0;
}