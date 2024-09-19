/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Header file for CentipedeGame class
*
*/

#pragma once
#include "BloodScreen.h"
#include "CentipedesHandler.h"
#include "constants.h"
#include "Direction.h"
#include "LivesDisplay.h"
#include "Mushroom.h"
#include "Spider.h"
#include "Starship.h"
#include "TextDisplay.h"
#include <list>
#include <random>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

using namespace std;
using namespace sf;

class CentipedeGame
{
public:
	CentipedeGame();

	void run();

private:
	// Initialize VideoMode and RenderWindow directly here
	VideoMode vm = VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
	RenderWindow window = RenderWindow(vm, "Centipede", sf::Style::Default);

	// Random number generator
	std::mt19937 gen;

	// Game object initial positions
	sf::Vector2f starshipInitialPosition =
		sf::Vector2f(WINDOW_WIDTH / 2.0f, (float)(WINDOW_HEIGHT - BOTTOM_BAR_HEIGHT));

	sf::Vector2f spiderInitialPosition =
		sf::Vector2f((float)WINDOW_WIDTH, 0.5f * WINDOW_HEIGHT);

	sf::Vector2f centipedesInitialGridPosition = sf::Vector2f((float)(int)(NUM_HORIZONTAL_GRID / 2.0f), 0.0f);

	// Game objects
	std::list<Mushroom> mushrooms;

	Starship starship = Starship(starshipInitialPosition);
	Spider spider = Spider(spiderInitialPosition);
	CentipedesHandler centipedes = CentipedesHandler(NUM_CENTIPEDE_SEGMENTS, centipedesInitialGridPosition);

	// Misc object positions
	sf::Vector2f liveDisplayPosition = sf::Vector2f((float)LIVES_DISPLAY_POSITION_X,
		(float)LIVES_DISPLAY_POSITION_Y);

	// Misc objects
	LivesDisplay livesDisplay = LivesDisplay(NUM_LIVES, liveDisplayPosition);
	BloodScreen bloodScreen = BloodScreen();
	ScoreDisplay scoreDisplay = ScoreDisplay((float)SCORE_Y_OFFSET, SCORE_FONTSIZE);

	// Game sequences
	void startupSequence();
	void mainSequence();
	void gameOverSequence(bool won);

	// Main sequence helpers
	void initializeMainSequence();
	void render();

	// Movement handlers
	void pollAndHandleInputs(sf::Event& event);
	void moveStarshipIfValid(Direction direction);

	// Mushroom handlers
	void populateMushrooms();
	void removeDestroyedMushrooms();

	// Fatal collisions handlers
	bool checkFatalStarshipCollision();
	bool checkStarshipSpiderCollision(sf::FloatRect& starshipBounds);
	bool checkStarshipCentipedeCollision(sf::FloatRect& starshipBounds);
	bool die();
	void respawn();

	// Laserblast collision handlers
	void checkLaserblastCollision();
	void checkLaserblastCentipedeDamage();
	void checkLaserblastMushroomSpiderDamage();

	// Spider collision handler
	void checkSpiderMushroomCollision();

};

