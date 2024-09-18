#pragma once

#include <SFML/Graphics.hpp>
#include "LaserBlast.h"
#include <list>

using namespace sf;
using namespace std;

class Starship
{

public:
	Starship(sf::Vector2f initPosition);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void fire();

	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getPosition();

	void refresh();

	void removeDestroyedBlasts();

	sf::Sprite getSprite();

	std::list<LaserBlast> getLaserblasts();
	void destroyLaserblast(int index);

private:
	sf::Vector2f position;

	int maxVerticalPosition = MAX_STARSHIP_Y_COORDINATE;
	float movementDelta = STARSHIP_MOVEMENT_DELTA;

	sf::Texture texture;
	sf::Sprite sprite;
	std::list<LaserBlast> laserblasts;
};

