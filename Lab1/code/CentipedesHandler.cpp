/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Class for handling multiple centipedes at once.
*
*/


#include "Centipede.h"
#include "CentipedesHandler.h"
#include "constants.h"
#include "Direction.h"
#include "Mushroom.h"
#include "Starship.h"
#include <list>
#include <SFML/System/Vector2.hpp>
#include <tuple>

/**
 * @brief Initialize a centipede handler
 * @param numSegments_			Number of body segment in the initial centipede
 * @param initialGridPosition_	Initial position of the centipede head, in grid unit
 */
CentipedesHandler::CentipedesHandler(int numSegments_, sf::Vector2f initialGridPosition_)
{

	numSegments = numSegments_;
	initialGridPosition = initialGridPosition_;

	headTexture.loadFromFile("graphics/CentipedeHead.png");
	bodyTexture.loadFromFile("graphics/CentipedeBody.png");

	reset(); // slightly misleading name, but this is used to initialize the centipede
}

/**
 * @brief Initialize the original centipede
 */
void CentipedesHandler::reset() {
	centipedes.clear();

	centipedes.push_back(Centipede(numSegments, initialGridPosition, headTexture, bodyTexture));

	clock.restart();
	timeOfLastMovement = clock.getElapsedTime();
}


/**
 * @brief Getter for the list of centipedes
 * @return	List of centipedes
 */
std::list<Centipede> CentipedesHandler::getCentipedes()
{
	return centipedes;
}

/**
 * @brief Check if there is any damage to the centipede from the laserblasts
 * @param starship	Reference to the starship object
 * @return Score change, List of new mushrooms to be created
 */
std::tuple<int, std::list <sf::Vector2f>> CentipedesHandler::checkDamage(Starship& starship) {

	starship.removeDestroyedBlasts();

	std::list<Centipede> newCentipedes;
	int totalScoreChange = 0;
	std::list <sf::Vector2f> newMushroomGridPosList;

	bool anyDamage = false;

	for (auto& centipede : centipedes) {

		Direction originalDirection = centipede.getCurrentDirection();
		std::list<Direction> originalDirectionQueue = centipede.getCurrentDirectionQueue();

		auto [pedesList, damageType, newMushroomGridPos] = centipede.checkDamage(starship, headTexture);

		if (damageType != NO_DAMAGE) {

			anyDamage = true;

			for (auto& pedes : pedesList) {
				newCentipedes.push_back(Centipede(pedes, originalDirection, originalDirectionQueue));
			}

			switch (damageType) {
			case HEAD_DAMAGED:
				totalScoreChange += CENTIPEDE_HEAD_POINTS;
				newMushroomGridPosList.push_back(sf::Vector2f(
					newMushroomGridPos.x * GRID_SIZE_PIXELS,
					newMushroomGridPos.y * GRID_SIZE_PIXELS + TOP_BAR_HEIGHT
				));
				break;
			case BODY_DAMAGED:
				totalScoreChange += CENTIPEDE_BODY_POINTS;
				break;
			}
		}
		else {
			newCentipedes.push_back(centipede);
		}
	}

	if (anyDamage) {
		centipedes = newCentipedes;
	}

	starship.removeDestroyedBlasts();
	return std::make_tuple(totalScoreChange, newMushroomGridPosList);
}

/**
 * @brief Update the centipede automovement location
 * @param mushrooms Reference to the list of mushrooms
 */
void CentipedesHandler::refresh(std::list<Mushroom>& mushrooms)
{
	if ((clock.getElapsedTime() - timeOfLastMovement).asSeconds() > timeBeforeMovement) {
		for (auto& centipede : centipedes) {
			centipede.refresh(mushrooms);
		}

		timeOfLastMovement = clock.getElapsedTime();

	}

}
