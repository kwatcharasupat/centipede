#include "constants.h"
#include "LaserBlast.h"
#include "Starship.h"
#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <utility>

using namespace sf;
using namespace std;

Starship::Starship(sf::Vector2f initPosition)
{
	position = initPosition;

	texture.loadFromFile("graphics/StarShip.png");
	sprite.setTexture(texture);
	sprite.setPosition(position);

}

void Starship::moveLeft()
{
	position.x = std::max(0.f, position.x - movementDelta);
}

void Starship::moveRight()
{
	position.x = std::min((float)WINDOW_WIDTH, position.x + movementDelta);
}

void Starship::moveUp()
{
	position.y = std::max((float)maxVerticalPosition, position.y - movementDelta);
}

void Starship::moveDown()
{
	position.y = std::min((float)(WINDOW_HEIGHT - GRID_SIZE_PIXELS), position.y + movementDelta);
}

void Starship::fire()
{
	LaserBlast laserblast(position);

	laserblasts.push_back(laserblast);
}

sf::Vector2f Starship::getPosition()
{
	return position;
}


void Starship::refresh()
{

	for (auto& laserblast : laserblasts) {
		laserblast.refresh();
	}

}

void Starship::removeDestroyedBlasts() {
	laserblasts.remove_if(
		[](LaserBlast& lb) { return lb.getState() == LaserBlast::LaserBlastState::DESTROYED; }
	);
}

sf::Sprite Starship::getSprite()
{

	sprite.setPosition(position);
	return sprite;
}

std::list<LaserBlast> Starship::getLaserblasts()
{
	return laserblasts;
}

void Starship::destroyLaserblast(int index)
{
	auto it = std::next(laserblasts.begin(), index);
	it->destroy();
}


void Starship::setPosition(sf::Vector2f newPosition) {

	position = newPosition;
}