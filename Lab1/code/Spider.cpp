
#include "constants.h"
#include "Spider.h"
#include <algorithm>
#include <cmath>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
using namespace std;

Spider::Spider(sf::Vector2f initPosition)
{
	position = initPosition;
	state = SpiderState::ALIVE;

	texture.loadFromFile("graphics/Spider.png");
	sprite.setTexture(texture);

	currentAngle = randomAngleDistribution(rng);

	clock.restart();
}

sf::Vector2f Spider::getPosition()
{
	return position;
}

sf::Sprite Spider::getSprite()
{

	switch (state) {
	case SpiderState::ALIVE:
		sprite.setPosition(position);
		return sprite;
	case SpiderState::DEAD:
		return sf::Sprite();
	}
}

void Spider::refresh() {
	switch (state) {
	case SpiderState::ALIVE:
		roam();
		break;
	case SpiderState::DEAD:
		regenerate();
		break;
	}
}

void Spider::destroy() {
	timeOfLastDeath = clock.getElapsedTime();
	state = SpiderState::DEAD;
}

void Spider::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
}

void Spider::regenerate() {
	if ((clock.getElapsedTime() - timeOfLastDeath).asSeconds() > secondsBeforeRevival) {
		state = SpiderState::ALIVE;
	}
}

void Spider::roam()
{

	if ((clock.getElapsedTime() - timeOfLastDirectionChange).asSeconds() > secondsBeforeDirectionChange) {
		currentAngle = randomAngleDistribution(rng);
		timeOfLastDirectionChange = clock.getElapsedTime();
	}

	sf::Vector2f oldPosition(position.x, position.y);

	position.x = std::clamp(
		position.x + movementDelta * cos(currentAngle),
		0.0f,
		(float)(WINDOW_WIDTH - GRID_SIZE_PIXELS)
	);

	position.y = std::clamp(
		position.y + movementDelta * sin(currentAngle),
		(float)TOP_BAR_HEIGHT,
		(float)(WINDOW_HEIGHT - GRID_SIZE_PIXELS)
	);

	if (oldPosition == position) {
		currentAngle = randomAngleDistribution(rng);
		timeOfLastDirectionChange = clock.getElapsedTime();
	}

}

