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

	sf::Vector2f getGridPosition();
	void setGridPosition(sf::Vector2f);

	sf::Vector2f getPosition();
	float getRotation();
	void setRotation(float newRotation);
	sf::Sprite getSprite();

	bool isHeadPede();

	enum PedeState {
		ACTIVE,
		DESTROYED
	};

	void destroy();
	PedeState getState();

private:
	bool isHead;
	float rotation;
	sf::Vector2f gridPosition;

	sf::Sprite sprite;

	PedeState state;
};

