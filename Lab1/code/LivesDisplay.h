/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Header file for the LivesDisplay class
*
*/

#pragma once

#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
using namespace std;

class LivesDisplay
{
public:
	LivesDisplay(int numLives, sf::Vector2f initPosition);

	void initializeSprites();
	void reset();

	int getCurrentLives();

	void die();
	std::list<sf::Sprite> getSprites();

private:
	int currentLives;
	int maxLives;

	sf::Vector2f position;

	sf::Texture texture;
	std::list<sf::Sprite> sprites;
};

