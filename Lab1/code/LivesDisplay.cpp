/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Class for displaying remaining lives
*
*/

#include "constants.h"
#include "LivesDisplay.h"
#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

/**
 * @brief Constructor
 * @param numLives		Number of lives to start with
 * @param initPosition	Where to place the indicator
 */
LivesDisplay::LivesDisplay(int numLives, sf::Vector2f initPosition)
{
	maxLives = numLives;
	currentLives = numLives;

	position = initPosition;

	texture.loadFromFile("./graphics/StarShip.png");
	initializeSprites();
}

/**
 * @brief Initialize the indicator sprites
 */
void LivesDisplay::initializeSprites() {
	for (int i = 0; i < currentLives; i++) {
		sf::Sprite liveSprite(texture);
		liveSprite.setPosition(sf::Vector2f(position.x + i * GRID_SIZE_PIXELS, position.y));
		sprites.push_back(liveSprite);
	}
}

/**
 * @brief Reset the display to full life
 */
void LivesDisplay::reset() {
	currentLives = maxLives;
	initializeSprites();
}

/**
 * @brief Get the current number of remaining lives
 * @return remaining lives
 */
int LivesDisplay::getCurrentLives()
{
	return currentLives;
}

/**
 * @brief Kill one life and remove one indicator
 */
void LivesDisplay::die()
{
	currentLives--;
	if (!sprites.empty()) {
		sprites.pop_back();
	}

}

/**
 * @brief  Get the sprites
 * @return List of sprites
 */
std::list<sf::Sprite> LivesDisplay::getSprites()
{
	return sprites;
}

