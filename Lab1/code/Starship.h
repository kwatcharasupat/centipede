/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Header file for the Starship class
*
*/

#pragma once

#include "constants.h"
#include "Direction.h"
#include "LaserBlast.h"
#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
using namespace std;

class Starship
{

public:
	Starship(sf::Vector2f initPosition);

	void move(Direction direction);
	void undoMove(Direction direction);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void fire();

	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getPosition();

	void refresh();

	std::list<LaserBlast> getLaserblasts();
	void resetLaserblasts();
	void destroyLaserblast(int index);
	void removeDestroyedBlasts();

	sf::Sprite getSprite();

private:
	sf::Vector2f position;

	std::list<LaserBlast> laserblasts;

	int maxVerticalPosition = MAX_STARSHIP_Y_COORDINATE;
	float movementDelta = STARSHIP_MOVEMENT_DELTA;

	sf::Texture texture;
	sf::Sprite sprite;
};

