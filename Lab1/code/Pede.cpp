#include "constants.h"
#include "Pede.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

Pede::Pede(bool isHead_, sf::Vector2f initialGridPosition, float initialRotation, Texture& texture)
{
	isHead = isHead_;
	gridPosition = initialGridPosition;
	rotation = initialRotation;

	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(GRID_SIZE_PIXELS / 2, GRID_SIZE_PIXELS / 2));

	state = PedeState::ACTIVE;
}

sf::Vector2f Pede::getGridPosition()
{
	return gridPosition;
}

void Pede::setGridPosition(sf::Vector2f newGridPosition)
{
	gridPosition = newGridPosition;
}

sf::Vector2f Pede::getPosition()
{
	return sf::Vector2f(
		(gridPosition.x + 0.5) * (float)GRID_SIZE_PIXELS,
		(gridPosition.y + 0.5) * (float)GRID_SIZE_PIXELS + (float)TOP_BAR_HEIGHT);
}

float Pede::getRotation()
{
	return rotation;
}

void Pede::setRotation(float newRotation)
{
	rotation = newRotation;
}

sf::Sprite Pede::getSprite()
{
	sf::Vector2f position = getPosition();
	sprite.setPosition(position);
	sprite.setRotation(rotation);
	return sprite;
}

bool Pede::isHeadPede()
{
	return isHead;
}

void Pede::destroy()
{
	state = PedeState::DESTROYED;
}


Pede::PedeState Pede::getState()
{
	return state;
}



