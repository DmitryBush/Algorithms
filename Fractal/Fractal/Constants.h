#pragma once
#include "SFML\Graphics.hpp"

// Ширина и высота экрана
const float width = static_cast<float>(sf::VideoMode::getDesktopMode().width);
const float height = static_cast<float>(sf::VideoMode::getDesktopMode().height);

// Центр экрана
const float halfWidth = width / 2.f;
const float halfHeight = height / 2.f;

// Коэффициент радиуса центрального круга, к рекурсивному кругу
const float kr = 2;
// Коэффициент уменьшения радиуса
const float ks = 3;
// Число пи
const float pi = 3.14;
// Радиус центрального круга
const float r = 200;
// Количество кругов
const int circleCount = 6;