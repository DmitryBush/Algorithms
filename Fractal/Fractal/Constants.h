#pragma once
#include "SFML\Graphics.hpp"

/*
* Заранее вычисленные константы, для оптимизации программы
*/
const float width = static_cast<float>(sf::VideoMode::getDesktopMode().width);
const float height = static_cast<float>(sf::VideoMode::getDesktopMode().height);

const float halfWidth = width / 2.f;
const float halfHeight = height / 2.f;