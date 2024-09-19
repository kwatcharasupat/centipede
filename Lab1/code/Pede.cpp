/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Class for handling a single pede (a centipede segment)
*
*/

#include "constants.h"
#include "Pede.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

/**
 * @brief Constructor
 * @param isHead_				Whether this is a head pede
 * @param initialGridPosition	Starting position
 * @param initialRotation		Starting rotation
 * @param texture				Texture to use
 */
Pede::Pede(bool isHead_, sf::Vector2f initialGridPosition, float initialRotation, Texture& texture)
{
	isHead = isHead_;
	gridPosition = initialGridPosition;
	rotation = initialRotation;

	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(GRID_SIZE_PIXELS / 2.0f, GRID_SIZE_PIXELS / 2.0f));

	state = PedeState::ACTIVE;
}

/**
 * @brief Get position in grid units
 * @return grid position
 */
sf::Vector2f Pede::getGridPosition()
{
	return gridPosition;
}

/**
 * @brief Set position in grid units
 * @param newGridPosition	Mew grid position
 */
void Pede::setGridPosition(sf::Vector2f newGridPosition)
{
	gridPosition = newGridPosition;
}

/**
 * @brief Get position in pixels
 * @return position in pixels
 */
sf::Vector2f Pede::getPosition()
{
	return sf::Vector2f(
		(gridPosition.x + 0.5f) * (float)GRID_SIZE_PIXELS,
		(gridPosition.y + 0.5f) * (float)GRID_SIZE_PIXELS + (float)TOP_BAR_HEIGHT);
}

/**
 * @brief  Get rotation
 * @return rotation
 */
float Pede::getRotation()
{
	return rotation;
}

/**
 * @brief Set rotation
 * @param newRotation	New rotation
 */
void Pede::setRotation(float newRotation)
{
	rotation = newRotation;
}

/**
 * @brief Get sprite
 * @returnsprite
 */
sf::Sprite Pede::getSprite()
{
	sf::Vector2f position = getPosition();
	sprite.setPosition(position);
	sprite.setRotation(rotation);
	return sprite;
}

/**
 * @brief Check if this pede is a head
 * @return whether it is a head
 */
bool Pede::isHeadPede()
{
	return isHead;
}

/**
 * @brief  Destory the pede
 */
void Pede::destroy()
{
	state = PedeState::DESTROYED;
}

/**
 * @brief  Get the pede state
 * @return state
 */
Pede::PedeState Pede::getState()
{
	return state;
}



