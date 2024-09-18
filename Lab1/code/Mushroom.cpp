#include "Mushroom.h"


Mushroom::Mushroom(sf::Vector2f &initPosition) {

	position = initPosition;

	state = MushroomState::ACTIVE;

	undamagedTexture.loadFromFile("graphics/Mushroom0.png");
	damagedTexture.loadFromFile("graphics/Mushroom1.png");
}

sf::Vector2f Mushroom::getPosition() {
	return position;
}

void Mushroom::setPosition(sf::Vector2f &newPosition) {
	position = newPosition;
}


void Mushroom::damage() {

	switch (state) {
	case ACTIVE:
		state = MushroomState::DAMAGED;
		break;
	case DAMAGED:
		state = MushroomState::DESTROYED;
		break;
	}
	return;
}

void Mushroom::destroy()
{
	state = MushroomState::DESTROYED;
	return;
}

sf::Sprite Mushroom::getSprite() {

	sprite.setPosition(position);

	switch (state) {
		case ACTIVE:
			sprite.setTexture(undamagedTexture);
			return sprite;
		case DAMAGED:
			sprite.setTexture(damagedTexture);
			return sprite;
		default:
			return sf::Sprite();
	}

}

Mushroom::MushroomState Mushroom::getState() {
	return state;
}