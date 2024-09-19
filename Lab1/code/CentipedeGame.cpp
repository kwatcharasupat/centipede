/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Class for handling Centipede game logics
*
*/

#include "CentipedeGame.h"
#include "constants.h"
#include "Direction.h"
#include "Mushroom.h"
#include "TextDisplay.h"
#include <cstdlib>
#include <ctime>
#include <list>
#include <random>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

/**
 * @brief Constructor class for the Centipede game. See header file for initialization.
 */
CentipedeGame::CentipedeGame()
{
	// set random seed and random generator
	srand(USE_FIXED_RANDOM_SEED ? RANDOM_SEED : (unsigned int)time(NULL));
	gen = std::mt19937(USE_FIXED_RANDOM_SEED ? RANDOM_SEED : (unsigned int)time(NULL));
}

/**
 * @brief Main logic loop of the game
 */
void CentipedeGame::run()
{
	// while the window is open
	while (window.isOpen()) {
		// run the startup sequence
		startupSequence();

		// run the main sequence
		mainSequence();

		// and repeat
	}
}

/**
 * @brief Show startup page
 */
void CentipedeGame::startupSequence()
{
	// Set the background
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/Startup Screen BackGround.png");
	Sprite spriteBackground(textureBackground);
	spriteBackground.setPosition(sf::Vector2f(0.f, 0.f));

	// Render
	window.clear();
	window.draw(spriteBackground);
	window.display();

	// Handle user input
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed ||
				event.type == sf::Event::KeyReleased) {
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					window.close();
				}

				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					return;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed ||
				event.type == sf::Event::MouseButtonReleased) {
				return;
			}
		}
	}
}


/**
 * @brief Show the end-of-game sequence
 * @param won	whether the player has won the game
 */
void CentipedeGame::gameOverSequence(bool won)
{
	TextDisplay textDisplay(-1.0f, 30);
	textDisplay.setString(won ? "YOU WON! HIT ENTER TO CONTINUE." : "GAME OVER! HIT ENTER TO CONTINUE.");

	window.clear();
	window.draw(textDisplay.getSprite());
	window.display();

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			return;
		}
	}
}



/**
 * @brief Main gameplay
 */
void CentipedeGame::mainSequence()
{
	// initialize game objects
	initializeMainSequence();

	while (window.isOpen()) {

		// render the window
		render();

		// check for keyboard inputs
		sf::Event event;
		pollAndHandleInputs(event);

		// refresh positions of objects
		bloodScreen.refresh();
		starship.refresh();
		spider.refresh();
		centipedes.refresh(mushrooms);

		// check for fatal collision
		bool hasFatalCollision = checkFatalStarshipCollision();
		if (hasFatalCollision) {
			bool survived = die();

			if (survived) {
				respawn();
			}
			else {
				return gameOverSequence(false);
			}
		}

		// check for laserblast collisions with other objects
		checkLaserblastCollision();

		// check for collision between spider and mushrooms
		checkSpiderMushroomCollision();

		// check if the game should end
		if (centipedes.getCentipedes().size() == 0) {
			// show the winning page
			return gameOverSequence(true);
		}

		// clean up destroyed objects
		starship.removeDestroyedBlasts();
		removeDestroyedMushrooms();
	}
	return;
}


/**
 * @brief Initialize game objects at the start of each game reset
 */
void CentipedeGame::initializeMainSequence() {

	scoreDisplay.setScore(0);
	livesDisplay.reset();

	starship.setPosition(starshipInitialPosition);
	starship.resetLaserblasts();

	spider.setPosition(spiderInitialPosition);

	centipedes.reset();

	mushrooms.clear();
	populateMushrooms();
}



/**
 * @brief Render all the drawings
 */
void CentipedeGame::render()
{
	window.clear();

	window.draw(starship.getSprite());
	window.draw(spider.getSprite());

	for (auto& mushroom : mushrooms) {
		window.draw(mushroom.getSprite());
	}

	for (auto& blasts : starship.getLaserblasts()) {
		window.draw(blasts.getSprite());
	}

	for (auto& ldSprite : livesDisplay.getSprites()) {
		window.draw(ldSprite);
	}

	for (auto& centipede : centipedes.getCentipedes()) {
		for (auto& pedeSprites : centipede.getSprites()) {
			window.draw(pedeSprites);
		}
	}

	window.draw(scoreDisplay.getSprite());
	window.draw(bloodScreen.getSprite());

	window.display();
}



/**
 * @brief Poll input events
 * @param event
 */
void CentipedeGame::pollAndHandleInputs(sf::Event& event)
{
	while (window.pollEvent(event)) {
		// check if the window is closed
		if (event.type == Event::Closed) {
			window.close();
		}

		// check if any key is pressed
		if (event.type == sf::Event::KeyPressed ||
			event.type == sf::Event::KeyReleased) {

			// check if the window is to bed closed
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}

			// fire the laser beam
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				starship.fire();
			}

			// arrow keys handling
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				moveStarshipIfValid(Direction::LEFT);
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				moveStarshipIfValid(Direction::RIGHT);
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				moveStarshipIfValid(Direction::UP);
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				moveStarshipIfValid(Direction::DOWN);
			}
		}
	}

}



/**
 * @brief Check if the starship can move in the `direction` and do so if valid
 * @param direction		Requested movement direction
 */
void CentipedeGame::moveStarshipIfValid(Direction direction)
{
	// preemptively move the starship first
	starship.move(direction);

	// then check for collision with mushroom if it were to move that way
	sf::FloatRect starshipBounds = starship.getSprite().getGlobalBounds();

	for (auto& mushroom : mushrooms) {
		if (starshipBounds.intersects(
			mushroom.getSprite().getGlobalBounds())) {

			// if there is collision, then undo the move
			starship.undoMove(direction);
			break;
		}
	}

	// otherwise the move persists
}


/**
 * @brief Populate the game with mushrooms
 */
void CentipedeGame::populateMushrooms()
{
	auto currentMushroomCount = mushrooms.size();

	if (currentMushroomCount >= NUM_MUSHROOMS) {
		return;
	}

	// set up the distributions
	std::uniform_int_distribution<int> uniformDistributionHorizontal(
		0, NUM_HORIZONTAL_GRID - 1);
	std::uniform_int_distribution<int> uniformDistributionVertical(
		0, NUM_VERTICAL_GRID - 1);

	bool isOverlapped;

	for (auto i = currentMushroomCount; i < NUM_MUSHROOMS; i++) {
		isOverlapped = true;
		sf::Vector2f mushroomCoordinate;

		// make sure the new mushroom does not overlap with an existing one
		do {
			isOverlapped = false;

			mushroomCoordinate = sf::Vector2f(
				uniformDistributionHorizontal(gen) * float(GRID_SIZE_PIXELS),
				uniformDistributionVertical(gen) * float(GRID_SIZE_PIXELS) +
				TOP_BAR_HEIGHT);

			for (Mushroom& mushroom : mushrooms) {
				if (mushroom.getPosition() == mushroomCoordinate) {
					isOverlapped = true;
					break;
				}
			}

		} while (isOverlapped);

		// add the new mushroom to the list
		mushrooms.push_back(Mushroom(mushroomCoordinate));
	}
}

/**
 * @brief Clean out all the destroyed mushrooms
 */
void CentipedeGame::removeDestroyedMushrooms()
{
	mushrooms.remove_if([](auto& mushroom) {
		return mushroom.getState() == Mushroom::MushroomState::DESTROYED;
		});
}


/**
 * @brief Check if anything has been hit by the laserblasts
 */
void CentipedeGame::checkLaserblastCollision()
{
	checkLaserblastCentipedeDamage();
	checkLaserblastMushroomSpiderDamage();
}

/**
 * @brief	Check if any part of the centipede has been hit by the laserblasts.
 *			If the centipede head has been hit, create mushroom in its place and update the score.
 */
void CentipedeGame::checkLaserblastCentipedeDamage()
{
	auto [scoreChange, newMushroomPosList] = centipedes.checkDamage(starship);

	for (auto& mushroomPos : newMushroomPosList) {
		Mushroom mushroom(mushroomPos);
		mushrooms.push_back(mushroom);
	}

	scoreDisplay.updateScore(scoreChange);

}

/**
 * @brief	Check if the laser hit the spider or a mushroom and update the score.
 */
void CentipedeGame::checkLaserblastMushroomSpiderDamage()
{

	sf::FloatRect spiderBounds = spider.getSprite().getGlobalBounds();

	int index = 0;
	// go thru all the laserblasts
	for (auto& laserblast : starship.getLaserblasts()) {
		sf::FloatRect lbSpriteBounds = laserblast.getSprite().getGlobalBounds();

		// check against the spider
		if (lbSpriteBounds.intersects(spiderBounds)) {
			spider.destroy();
			starship.destroyLaserblast(index);
			scoreDisplay.updateScore(SPIDER_POINTS);
			continue;
		}

		// check thru all the mushrooms
		for (auto& mushroom : mushrooms) {
			if (mushroom.getState() == Mushroom::MushroomState::DESTROYED) {
				continue;
			}

			sf::FloatRect mushroomBounds = mushroom.getSprite().getGlobalBounds();

			if (lbSpriteBounds.intersects(mushroomBounds)) {
				mushroom.damage();
				starship.destroyLaserblast(index);

				if (mushroom.getState() == Mushroom::MushroomState::DESTROYED) {
					scoreDisplay.updateScore(MUSHROOM_POINTS);
				}
				break;
			}
		}

		index++;
	}
}

/**
 * @brief Check if the spider has collided with a mushroom
 */
void CentipedeGame::checkSpiderMushroomCollision()
{
	sf::FloatRect spiderBounds = spider.getSprite().getGlobalBounds();
	for (auto& mushroom : mushrooms) {
		if (mushroom.getState() == Mushroom::MushroomState::DESTROYED) {
			continue;
		}
		sf::FloatRect mushroomBounds = mushroom.getSprite().getGlobalBounds();

		if (spiderBounds.intersects(mushroomBounds)) {
			mushroom.destroy();
		}
	}

}

/**
 * @brief Check if the starship has made any fatal collision with a centipede or the spider
 * @return	whether there was a fatal collision
 */
bool CentipedeGame::checkFatalStarshipCollision()
{
	sf::FloatRect starshipBounds = starship.getSprite().getGlobalBounds();
	return checkStarshipSpiderCollision(starshipBounds) || checkStarshipCentipedeCollision(starshipBounds);
}

/**
 * @brief Check collision between the starship and spider
 * @param starshipBounds	Bounds of the starship
 * @return	whether there was a collision
 */
bool CentipedeGame::checkStarshipSpiderCollision(sf::FloatRect& starshipBounds)
{
	sf::FloatRect spiderBounds = spider.getSprite().getGlobalBounds();
	return starshipBounds.intersects(spiderBounds);
}

/**
 * @brief Check collision between the starship and centipedes
 * @param starshipBounds	Bounds of the starship
 * @return	whether there was a collision
 */
bool CentipedeGame::checkStarshipCentipedeCollision(sf::FloatRect& starshipBounds)
{

	for (auto& centipede : centipedes.getCentipedes()) {
		for (auto& pedeSprites : centipede.getSprites()) {
			if (starshipBounds.intersects(pedeSprites.getGlobalBounds())) {
				return true;
			}
		}
	}

	return false;
}


/**
 * @brief Handle the logic after fatal collision
 * @return whether there is any remaining lives
 */
bool CentipedeGame::die()
{
	livesDisplay.die();	// update the lives display
	bloodScreen.die();	// create a blood screen

	return livesDisplay.getCurrentLives() > 0;
}

/**
 * @brief Respawn the starship, repopulate the mushrooms, and reset the spider position
 */
void CentipedeGame::respawn()
{
	populateMushrooms();
	starship.setPosition(starshipInitialPosition);
	spider.setPosition(spiderInitialPosition);
}
