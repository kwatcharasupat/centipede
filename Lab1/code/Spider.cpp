/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Class for handling the autoroam spider
*
*/

#include "constants.h"
#include "Spider.h"
#include <algorithm>
#include <cmath>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
using namespace std;

/**
 * @brief Constructor
 * @param initPosition	Starting position 
 */
Spider::Spider(sf::Vector2f initPosition)
{
	position = initPosition;
	state = SpiderState::ALIVE;

	texture.loadFromFile("graphics/Spider.png");
	sprite.setTexture(texture);

	currentAngle = randomAngleDistribution(rng);

	clock.restart();
}

/**
 * @brief  Get spider position
 * @return position
 */
sf::Vector2f Spider::getPosition()
{
	return position;
}

/**
 * @brief Get sprite, return an empty sprite if the spider is dead
 * @return sprite
 */
sf::Sprite Spider::getSprite()
{

	switch (state) {
	case SpiderState::ALIVE:
		sprite.setPosition(position);
		return sprite;
	case SpiderState::DEAD:
		return sf::Sprite();
	}

	throw; // this should not be reached
}

/**
 * @brief Update the spider location
 */
void Spider::refresh() {
	switch (state) {
	case SpiderState::ALIVE:
		// if alive, roam
		roam();
		break;
	case SpiderState::DEAD:
		// if dead, regenerate
		regenerate();
		break;
	}
}

/**
 * @brief Destroy the spider
 */
void Spider::destroy() {
	timeOfLastDeath = clock.getElapsedTime();
	state = SpiderState::DEAD;
}

/**
 * @brief Set the position
 * @param newPosition  New position
 */
void Spider::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
}

/**
 * @brief Check if the spider has regenerated and update state
 */
void Spider::regenerate() {
	if ((clock.getElapsedTime() - timeOfLastDeath).asSeconds() > secondsBeforeRevival) {
		state = SpiderState::ALIVE;
	}
}

/**
 * @brief Autoroam the spider with random angle
 */
void Spider::roam()
{

	if ((clock.getElapsedTime() - timeOfLastDirectionChange).asSeconds() > secondsBeforeDirectionChange) {
		currentAngle = randomAngleDistribution(rng);
		timeOfLastDirectionChange = clock.getElapsedTime();
	}

	sf::Vector2f oldPosition(position);

	position.x = std::clamp(
		position.x + movementDelta * cos(currentAngle),
		0.0f,
		(float)(WINDOW_WIDTH - GRID_SIZE_PIXELS)
	);

	position.y = std::clamp(
		position.y + movementDelta * sin(currentAngle),
		(float)TOP_BAR_HEIGHT,
		(float)(WINDOW_HEIGHT - GRID_SIZE_PIXELS)
	);

	if (oldPosition == position) {
		currentAngle = randomAngleDistribution(rng);
		timeOfLastDirectionChange = clock.getElapsedTime();
	}

}

