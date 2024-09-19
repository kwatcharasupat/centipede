/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Header file for the Mushroom class
*
*/


#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>


using namespace sf;

class Mushroom
{
public:

	Mushroom(sf::Vector2f& position);

	enum MushroomState {
		ACTIVE,
		DAMAGED,
		DESTROYED
	};

	void setPosition(sf::Vector2f& position);
	sf::Vector2f getPosition();

	Mushroom::MushroomState getState();

	void damage();
	void destroy();

	sf::Sprite getSprite();

private:
	sf::Vector2f position;
	Mushroom::MushroomState state;

	sf::Texture undamagedTexture;
	sf::Texture damagedTexture;

	sf::Sprite sprite;
};

