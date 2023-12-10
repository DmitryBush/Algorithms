#pragma once
#include "SFML\Graphics.hpp"

// ������ � ������ ������
const float width = static_cast<float>(sf::VideoMode::getDesktopMode().width);
const float height = static_cast<float>(sf::VideoMode::getDesktopMode().height);

// ����� ������
const float halfWidth = width / 2.f;
const float halfHeight = height / 2.f;

// ����������� ������� ������������ �����, � ������������ �����
const float kr = 2;
// ����������� ���������� �������
const float ks = 3;
// ����� ��
const float pi = 3.14;
// ������ ������������ �����
const float r = 200;
// ���������� ������
const int circleCount = 6;