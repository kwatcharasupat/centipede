/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Header file for the Pede class
*
*/

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
using namespace std;


class Pede
{
public:
	Pede(bool isHead, sf::Vector2f initialGridPosition, float initialRotation, Texture& texture);

	enum PedeState {
		ACTIVE,
		DESTROYED
	};

	sf::Vector2f getGridPosition();
	void setGridPosition(sf::Vector2f);

	sf::Vector2f getPosition();

	float getRotation();
	void setRotation(float newRotation);

	sf::Sprite getSprite();

	bool isHeadPede();

	void destroy();
	PedeState getState();

private:
	bool isHead;
	float rotation;
	sf::Vector2f gridPosition;

	sf::Sprite sprite;

	PedeState state;
};

