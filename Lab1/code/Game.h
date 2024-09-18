#pragma once
#include "Centipedes.h"
#include "LivesDisplay.h"
#include "Mushroom.h"
#include "Spider.h"
#include "Starship.h"
#include <list>
#include <SFML/Graphics.hpp>
class Game
{
public:

	Game();
	void initializeObjects();

	void startupSequence();
	void gameOverSequence(bool isWinning);

	void run();

private:
	Starship starship;
	Spider spider;
	std::list<Mushroom> mushrooms;
	Centipedes centipedes;
	sf::Text scoreDisplay;
	LivesDisplay livesDisplay;
	sf::RectangleShape bloodScreen;
	int score;
	int bloodLevel;

	VideoMode vm;
	RenderWindow window;
};

