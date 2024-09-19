/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Header file for the Spider class
*
*/

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "constants.h"
#include <random>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
using namespace std;

class Spider
{

public:
	Spider(sf::Vector2f);

	enum SpiderState {
		ALIVE,
		DEAD
	};

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPosition);

	void refresh();
	void destroy();

	sf::Sprite getSprite();


private:
	sf::Vector2f position;
	SpiderState state;

	std::mt19937 rng = std::mt19937(RANDOM_SEED);
	std::uniform_real_distribution<float> randomAngleDistribution = std::uniform_real_distribution<float>(0.0f, 2.0f * (float)M_PI);

	float currentAngle;
	float movementDelta = SPIDER_MOVEMENT_DELTA;

	sf::Clock clock;

	float secondsBeforeDirectionChange = SPIDER_SECONDS_BEFORE_DIRECTION_CHANGE;
	sf::Time timeOfLastDirectionChange;

	float secondsBeforeRevival = SPIDER_SECONDS_BEFORE_REVIVAL;
	sf::Time timeOfLastDeath;

	sf::Texture texture;
	sf::Sprite sprite;

	void regenerate();
	void roam();
};

