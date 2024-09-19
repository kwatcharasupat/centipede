/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Class for handling a laserblast
*
*/

#include "LaserBlast.h"

#include "constants.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;

/**
 * @brief Constructor
 * @param initPosition Position where the laserblast was fired 
 */
LaserBlast::LaserBlast(sf::Vector2f initPosition)
{
	// Set position and state
	position = sf::Vector2f(initPosition.x + BLAST_X_OFFSET, initPosition.y);
	state = LaserBlastState::TRAVELLING;

	// Set sprite config
	blastSprite.setSize(sf::Vector2f((float)BLAST_WIDTH_PIXELS, (float)BLAST_HEIGHT_PIXELS));
	blastSprite.setFillColor(sf::Color(255, 0, 0, 128));
	blastSprite.setPosition(position);

}

/**
 * @brief Get the current location
 * @return position
 */
sf::Vector2f LaserBlast::getPosition()
{
	return position;
}

/**
 * @brief Get the current state
 * @return state
 */
LaserBlast::LaserBlastState LaserBlast::getState()
{
	return state;
}

/**
 * @brief Update the position and state
 */
void LaserBlast::refresh()
{
	// leave destroyed laser alone
	if (state != LaserBlastState::TRAVELLING) {
		return;
	}

	// move the laser up
	position.y -= movementDelta;
	blastSprite.setPosition(position);

	// if it leaves the screen, destroy
	if (position.y <= 0) {
		state = LaserBlastState::DESTROYED;
	}
}

/**
 * @brief Get the sprite
 * @return sprite
 */
sf::RectangleShape LaserBlast::getSprite()
{
	return blastSprite;
}

/**
 * @brief Set the state to destroyed
 */
void LaserBlast::destroy()
{
	state = LaserBlastState::DESTROYED;
}




