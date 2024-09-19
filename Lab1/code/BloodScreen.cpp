/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Class for handling a dying effect
*
*/

#include "BloodScreen.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <utility>

/**
 * @brief Constructor
 */
BloodScreen::BloodScreen()
{
}

/**
 * @brief Activate when dying
 */
void BloodScreen::die()
{
	bloodLevel = 255;
}

/**
 * @brief Reducing the blood level
 */
void BloodScreen::refresh()
{
	bloodLevel = std::max(bloodLevel - 1, 0);
}

/**
 * @brief Get the blood screen sprite
 * @return Sprite
 */
sf::RectangleShape BloodScreen::getSprite()
{
	screen.setFillColor(sf::Color(255, 0, 0, bloodLevel));

	return screen;
}


