#pragma once
#include <SFML/Graphics.hpp>
#include <list>

#include "constants.h"

class LaserBlast
{

public:
	LaserBlast(sf::Vector2f initPosition);


	enum LaserBlastState{
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

