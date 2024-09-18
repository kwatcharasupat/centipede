#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
#include <list>
#include "Centipede.h"
#include "Mushroom.h"
#include "LaserBlast.h"
#include "Starship.h"

using namespace sf;
using namespace std;
class Centipedes
{
public:
	Centipedes(int numSegments, sf::Vector2f initialPosition);

	std::list<Centipede> getCentipedes();
	std::tuple<int, std::list <sf::Vector2f>> Centipedes::refresh(std::list<Mushroom>& mushrooms, Starship& starship);
	std::tuple<int, std::list <sf::Vector2f>> checkDamage(Starship& starship);

private:
	std::list<Centipede> centipedes;
	sf::Clock clock;
	sf::Time timeOfLastMovement;
	float timeBeforeMovement = CENTIPEDE_SECONDS_BEFORE_MOVEMENT;

	sf::Texture headTexture;
	sf::Texture bodyTexture;
};

