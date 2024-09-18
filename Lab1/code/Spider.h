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

	sf::Vector2f getPosition();
	sf::Sprite getSprite();

	void refresh();
	void destroy();
	void setPosition(sf::Vector2f newPosition);

	enum SpiderState {
		ALIVE,
		DEAD
	};

private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f position;
	SpiderState state;

	std::mt19937 rng = std::mt19937(RANDOM_SEED);
	std::uniform_real_distribution<double> randomAngleDistribution = std::uniform_real_distribution<double>(0.0, 2 * M_PI);

	float currentAngle;
	float movementDelta = SPIDER_MOVEMENT_DELTA;

	sf::Clock clock;

	float secondsBeforeDirectionChange = SPIDER_SECONDS_BEFORE_DIRECTION_CHANGE;
	sf::Time timeOfLastDirectionChange;

	float secondsBeforeRevival = SPIDER_SECONDS_BEFORE_REVIVAL;
	sf::Time timeOfLastDeath;

	void regenerate();
	void roam();
};

