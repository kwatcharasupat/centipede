#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
#include <list>
#include "Pede.h"
#include "Mushroom.h"
#include "LaserBlast.h"
#include "Starship.h"

using namespace sf;
using namespace std;

enum MovementDirection {
	LEFT,
	RIGHT,
	DOWN
};

enum DamageType {
	NO_DAMAGE,
	BODY_DAMAGED,
	HEAD_DAMAGED
};

class Centipede
{
public:
	Centipede(int numSegments, sf::Vector2f initialGridPosition, Texture& headTexture, Texture& bodyTexture);
	Centipede(std::list<Pede>& pedes, MovementDirection currentDirection, std::list<MovementDirection>& directionQueue);

	std::list<sf::Sprite> getSprites();

	void refresh(std::list<Mushroom>& mushrooms);

	std::tuple<std::list<std::list<Pede>>, DamageType, sf::Vector2f> checkDamage(Starship& starship, sf::Texture& headTexture);
	std::tuple<std::list<std::list<Pede>>, DamageType, sf::Vector2f> postDamageUpdate(sf::Texture& headTexture);

	MovementDirection getCurrentDirection();
	std::list<MovementDirection> getCurrentDirectionQueue();
	
private:
	int numSegments;

	std::list<Pede> pedes;

	std::list<MovementDirection> directionQueue;
	MovementDirection currentDirection;

	//sf::Vector2f getFuturePosition(Pede headPede, MovementDirection direction);
	bool checkImminentMushroomHit(Pede& headPede, std::list<Mushroom>& mushrooms);

};

