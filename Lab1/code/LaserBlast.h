/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Header file for the LaserBlast class
*
*/

#pragma once

#include "constants.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class LaserBlast
{

public:
	LaserBlast(sf::Vector2f initPosition);

	enum LaserBlastState {
		UNINITIALIZED,
		TRAVELLING,
		DESTROYED
	};

	sf::Vector2f getPosition();
	LaserBlastState getState();

	void refresh();
	sf::RectangleShape getSprite();

	void destroy();

private:
	sf::Vector2f position;
	LaserBlastState state;

	unsigned int maxVerticalCoordinate = WINDOW_HEIGHT;
	float movementDelta = LASERBLAST_MOVEMENT_DELTA;

	sf::RectangleShape blastSprite;
};

