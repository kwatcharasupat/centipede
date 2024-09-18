#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "constants.h"

using namespace sf;
using namespace std;

class LivesDisplay
{
public:
	LivesDisplay(int numLives, sf::Vector2f initPosition);

	int getCurrentLives();

	void die();

	std::list<sf::Sprite> getSprites();

private:
	int currentLives;
	sf::Vector2f position;

	sf::Texture texture;
	std::list<sf::Sprite> sprites;
};

