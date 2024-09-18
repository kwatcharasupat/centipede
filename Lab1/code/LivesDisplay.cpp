#include "LivesDisplay.h"

LivesDisplay::LivesDisplay(int numLives, sf::Vector2f initPosition)
{
	currentLives = numLives;

	position = initPosition;
	texture.loadFromFile("graphics/StarShip.png");

	for (int i = 0; i < currentLives; i++) {
		sf::Sprite liveSprite(texture);
		liveSprite.setPosition(sf::Vector2f(position.x + i * GRID_SIZE_PIXELS, position.y));
		sprites.push_back(liveSprite);
	}
}

int LivesDisplay::getCurrentLives()
{
	return currentLives;
}

void LivesDisplay::die()
{
	currentLives--;
	sprites.pop_back();
}

std::list<sf::Sprite> LivesDisplay::getSprites()
{
	return sprites;
}

