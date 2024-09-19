/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Class for handling the starship
*
*/

#include "constants.h"
#include "Direction.h"
#include "LaserBlast.h"
#include "Starship.h"
#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <utility>

using namespace sf;
using namespace std;


/**
 * @brief Constructor
 * @param initPosition	Starting position 
 */
Starship::Starship(sf::Vector2f initPosition)
{
	position = initPosition;

	texture.loadFromFile("graphics/StarShip.png");
	sprite.setTexture(texture);
	sprite.setPosition(position);

}

/**
 * @brief Move the starship in direction
 * @param direction		Direction to move
 */
void Starship::move(Direction direction)
{
	switch (direction) {
	case UP:
		moveUp();
		break;
	case DOWN:
		moveDown();
		break;
	case LEFT:
		moveLeft();
		break;
	case RIGHT:
		moveRight();
		break;
	}
}


/**
 * @brief Undo moving the starship
 * @param direction		Direction to undo
 */
void Starship::undoMove(Direction direction)
{
	switch (direction) {
	case UP:
		moveDown();
		break;
	case DOWN:
		moveUp();
		break;
	case LEFT:
		moveRight();
		break;
	case RIGHT:
		moveLeft();
		break;
	}
}


/**
 * @brief Move starship to the left
 */
void Starship::moveLeft()
{
	position.x = std::max(0.f, position.x - movementDelta);
}


/**
 * @brief Move starship to the right
 */
void Starship::moveRight()
{
	position.x = std::min((float)WINDOW_WIDTH, position.x + movementDelta);
}


/**
 * @brief Move starship up
 */
void Starship::moveUp()
{
	position.y = std::max((float)maxVerticalPosition, position.y - movementDelta);
}



/**
 * @brief Move starship down
 */
void Starship::moveDown()
{
	position.y = std::min((float)(WINDOW_HEIGHT - GRID_SIZE_PIXELS), position.y + movementDelta);
}


/**
 * @brief Make a laserblast
 */
void Starship::fire()
{
	LaserBlast laserblast(position);

	laserblasts.push_back(laserblast);
}

/**
 * @brief Get starship position
 * @return position
 */
sf::Vector2f Starship::getPosition()
{
	return position;
}

/**
 * @brief Update laserblast locations
 */
void Starship::refresh()
{

	for (auto& laserblast : laserblasts) {
		laserblast.refresh();
	}

}

/**
 * @brief  Clear out destroyed laser blasts
 */
void Starship::removeDestroyedBlasts() {
	laserblasts.remove_if(
		[](LaserBlast& lb) { return lb.getState() == LaserBlast::LaserBlastState::DESTROYED; }
	);
}

/**
 * @brief  Get sprite
 * @return sprite
 */
sf::Sprite Starship::getSprite()
{

	sprite.setPosition(position);
	return sprite;
}

/**
 * @brief Get laserblasts
 * @return List of laserblasts
 */
std::list<LaserBlast> Starship::getLaserblasts()
{
	return laserblasts;
}

/**
 * @brief Remove all laserblasts
 */
void Starship::resetLaserblasts() {
	laserblasts.clear();
}

/**
 * @brief Destroy a specific laserblast
 * @param index		Index of the laserblast to be destroyed
 */
void Starship::destroyLaserblast(int index)
{
	auto it = std::next(laserblasts.begin(), index);
	it->destroy();
}

/**
 * @brief Set starship position
 * @param newPosition	New position
 */
void Starship::setPosition(sf::Vector2f newPosition) {

	position = newPosition;
}