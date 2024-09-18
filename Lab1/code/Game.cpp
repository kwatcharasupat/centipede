#include "Game.h"

Game::Game()
{
	srand(RANDOM_SEED);

	VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create and open a window for the game
	RenderWindow window(vm, "Centipede", sf::Style::Default);

	std::list<Mushroom> mushrooms;
	//populateMushrooms(mushrooms);

	sf::Vector2f starshipInitialPosition =
		sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - BOTTOM_BAR_HEIGHT);
	starship = Starship(starshipInitialPosition);

	sf::Vector2f spiderInitialPosition =
		sf::Vector2f(WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT);
	spider = Spider(spiderInitialPosition);

	centipedes = Centipedes(NUM_CENTIPEDE_SEGMENTS,
		sf::Vector2f((int)(NUM_HORIZONTAL_GRID / 2), 0));

	livesDisplay = LivesDisplay(NUM_LIVES, sf::Vector2f(LIVES_DISPLAY_POSITION_X,
		LIVES_DISPLAY_POSITION_Y));

	sf::RectangleShape bloodScreen(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	bloodScreen.setFillColor(sf::Color(255, 0, 0, 0));
	int bloodLevel = 0;

	int score = 0;

	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	sf::Text scoreDisplay;
	scoreDisplay.setFont(font);
	scoreDisplay.setCharacterSize(90);
	scoreDisplay.setFillColor(sf::Color(255, 255, 255));
}


