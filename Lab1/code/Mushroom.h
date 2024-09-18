#pragma once

#include <SFML/Graphics.hpp>

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

	void damage();
	void destroy();

	sf::Sprite getSprite();

	Mushroom::MushroomState getState();

private:
	sf::Vector2f position;
	Mushroom::MushroomState state;

	sf::Texture undamagedTexture;
	sf::Texture damagedTexture;

	sf::Sprite sprite;
};

