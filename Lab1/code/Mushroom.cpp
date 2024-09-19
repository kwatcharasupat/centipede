/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Class for handling a mushroom
*
*/


#include "Mushroom.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>


/**
 * @brief Constructor
 * @param initPosition	Position of the mushroom 
 */
Mushroom::Mushroom(sf::Vector2f& initPosition) {

	position = initPosition;

	state = MushroomState::ACTIVE;

	undamagedTexture.loadFromFile("graphics/Mushroom0.png");
	damagedTexture.loadFromFile("graphics/Mushroom1.png");
}

/**
 * @brief Get the current position
 * @return position
 */
sf::Vector2f Mushroom::getPosition() {
	return position;
}

/**
 * @brief Set the current position
 * @param newPosition New position
 */
void Mushroom::setPosition(sf::Vector2f& newPosition) {
	position = newPosition;
}


/**
 * @brief Damage the mushroom and handle state change
 */
void Mushroom::damage() {

	switch (state) {
	case ACTIVE:
		state = MushroomState::DAMAGED;
		break;
	case DAMAGED:
		state = MushroomState::DESTROYED;
		break;
	}
	return;
}

/**
 * @brief  Destroy the mushroom immediately
 */
void Mushroom::destroy()
{
	state = MushroomState::DESTROYED;
	return;
}

/**
 * @brief Get the sprite
 * @return sprite
 */
sf::Sprite Mushroom::getSprite() {

	sprite.setPosition(position);

	switch (state) {
	case ACTIVE:
		sprite.setTexture(undamagedTexture);
		return sprite;
	case DAMAGED:
		sprite.setTexture(damagedTexture);
		return sprite;
	default:
		return sf::Sprite();
	}

}

/**
 * @brief Get the mushroom state
 * @return state
 */
Mushroom::MushroomState Mushroom::getState() {
	return state;
}