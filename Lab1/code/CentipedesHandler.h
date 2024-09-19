/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Header file for CentipedesHandler class
*
*/


#pragma once

#include "Centipede.h"
#include "constants.h"
#include "Mushroom.h"
#include "Starship.h"
#include <list>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <tuple>

using namespace sf;
using namespace std;
class CentipedesHandler
{
public:
	CentipedesHandler(int numSegments, sf::Vector2f initialPosition);

	void reset();

	std::list<Centipede> getCentipedes();

	std::tuple<int, std::list <sf::Vector2f>> checkDamage(Starship& starship);

	void CentipedesHandler::refresh(std::list<Mushroom>& mushrooms);

private:
	int numSegments;
	sf::Vector2f initialGridPosition;

	std::list<Centipede> centipedes;

	sf::Clock clock;
	sf::Time timeOfLastMovement;
	float timeBeforeMovement = CENTIPEDE_SECONDS_BEFORE_MOVEMENT;

	sf::Texture headTexture;
	sf::Texture bodyTexture;

};

