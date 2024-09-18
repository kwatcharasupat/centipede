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
#include <utility>

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

