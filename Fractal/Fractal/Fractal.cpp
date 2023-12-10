#include <iostream>
#include <cmath>
#include "Constants.h"
#include "SFML/Graphics.hpp"

// Функция рекурсивной отрисовки кругов
void Draw(sf::RenderWindow& window, float x, 
	float y, float radius, float newRadius, int depth)
{
	if (!depth)
		return;
	sf::CircleShape circle(radius, 70);
	circle.setOrigin(sf::Vector2f(radius, radius));
	circle.setPosition(sf::Vector2f(x, y));
	window.draw(circle);

	newRadius = kr * radius;
	for (auto i = 0; i < circleCount; i++)
	{
		float newX = x + newRadius * cos(static_cast<float>(2 * pi * i)
			/ static_cast<float>(circleCount));
		float newY = y + newRadius * sin(static_cast<float>(2 * pi * i)
			/ static_cast<float>(circleCount));
		Draw(window, newX, newY, radius / ks, newRadius, depth - 1);
	}
}

// Инициализация окна и рекурсивная отрисовка кругов
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
		Draw(window, halfWidth, halfHeight, r, 0.0f, 5);
		window.display();
	}
	return 0;
}