/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Header file for the Centipede class
*
*/

#pragma once

#include "Direction.h"
#include "Mushroom.h"
#include "Pede.h"
#include "Starship.h"
#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <tuple>

using namespace sf;
using namespace std;

enum DamageType {
	NO_DAMAGE,
	BODY_DAMAGED,
	HEAD_DAMAGED
};

class Centipede
{
public:
	Centipede(int numSegments, sf::Vector2f initialGridPosition, Texture& headTexture, Texture& bodyTexture);
	Centipede(std::list<Pede>& pedes, Direction currentDirection, std::list<Direction>& directionQueue);

	std::list<sf::Sprite> getSprites();

	void refresh(std::list<Mushroom>& mushrooms);

	std::tuple<std::list<std::list<Pede>>, DamageType, sf::Vector2f> checkDamage(Starship& starship, sf::Texture& headTexture);
	std::tuple<std::list<std::list<Pede>>, DamageType, sf::Vector2f> postDamageUpdate(sf::Texture& headTexture);

	Direction getCurrentDirection();
	std::list<Direction> getCurrentDirectionQueue();

private:
	int numSegments;

	std::list<Pede> pedes;

	Direction currentDirection;
	std::list<Direction> directionQueue;

	bool checkImminentMushroomHit(Pede& headPede, std::list<Mushroom>& mushrooms);
};


