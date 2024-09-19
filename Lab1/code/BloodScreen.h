#pragma once
#include "constants.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
class BloodScreen
{
public:
	BloodScreen();

	void die();
	void refresh();

	sf::RectangleShape getSprite();

private:
	int bloodLevel = 0;
	sf::RectangleShape screen = sf::RectangleShape(sf::Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));


};

