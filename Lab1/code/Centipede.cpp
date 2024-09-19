/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Class for handling a single centipede
*
*/

#include "Centipede.h"
#include "constants.h"
#include "Direction.h"
#include "LaserBlast.h"
#include "Mushroom.h"
#include "Pede.h"
#include "Starship.h"
#include <list>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <tuple>

using namespace sf;
using namespace std;

/**
 * @brief Constructor for the centipede object
 * @param initialNumSegments	Number of segments in the centipede
 * @param initialGridPosition	Original position of the head
 * @param headTexture_			Reference to the centipede head texture
 * @param bodyTexture			Reference to the centipede body texture
 */
Centipede::Centipede(int initialNumSegments, sf::Vector2f initialGridPosition, Texture& headTexture_, Texture& bodyTexture)
{
	numSegments = initialNumSegments;

	for (int i = 0; i < numSegments; i++) {
		sf::Vector2f pedeGridPosition(initialGridPosition.x, initialGridPosition.y - (float)i);
		bool isHead = i == 0;

		// initialize the `pede` to make up the centipede
		Pede pede(isHead, pedeGridPosition, 0.0f, isHead ? headTexture_ : bodyTexture);
		pedes.push_back(pede);
	}

	currentDirection = DOWN;
}

/**
 * @brief Pseudo-copy constructor of the centipede
 * @param pedes_				List of pedes
 * @param currentDirection_		Current direction of travel
 * @param directionQueue_		Direction queue
 */
Centipede::Centipede(std::list<Pede>& pedes_, Direction currentDirection_, std::list<Direction>& directionQueue_)
{
	numSegments = (int)pedes.size();

	pedes = pedes_;
	currentDirection = currentDirection_;
	directionQueue = directionQueue_;
}

/**
 * @brief Get sprites of the centipede
 * @return List of sprites
 */
std::list<sf::Sprite> Centipede::getSprites()
{
	std::list<sf::Sprite> sprites;
	for (auto& pede : pedes) {
		sprites.push_back(pede.getSprite());
	}

	return sprites;
}

/**
 * @brief Check if the centipede is about to hit a mushroom if it does not turn
 * @param headPede		Head pede
 * @param mushrooms		List of mushrooms
 * @return				Whether the centipede will hit if it does not turn
 */
bool Centipede::checkImminentMushroomHit(Pede& headPede, std::list<Mushroom>& mushrooms) {

	// the original gameplay allows the centipede to go thru the mushroom from the top
	if (currentDirection == DOWN) {
		return false;
	}

	// compute future location, in grid unit
	const sf::Vector2f gridPos = headPede.getGridPosition();
	sf::Vector2f futureGridPos;

	switch (currentDirection) {
	case LEFT:
		futureGridPos = sf::Vector2f(gridPos.x - 1.0f, gridPos.y);
		break;
	case RIGHT:
		futureGridPos = sf::Vector2f(gridPos.x + 1.0f, gridPos.y);
		break;
	}


	// conver the grid position to pixel bounding box
	headPede.setGridPosition(futureGridPos);
	sf::FloatRect headPedeBounds = headPede.getSprite().getGlobalBounds();

	bool willHit = false;

	// check for intersection
	for (auto& mushroom : mushrooms) {
		sf::FloatRect mushroomBounds = mushroom.getSprite().getGlobalBounds();
		if (headPedeBounds.intersects(mushroomBounds)) {
			willHit = true;
			break;
		}
	}

	// restore the original position
	headPede.setGridPosition(gridPos);

	return willHit;

}


/**
 * @brief Update the centipede automovement location
 * @param mushrooms Reference to the list of mushrooms
 */
void Centipede::refresh(std::list<Mushroom>& mushrooms)
{
	// grab the next direction in queue, if available
	if (directionQueue.size() > 0) {
		currentDirection = directionQueue.front();
		directionQueue.pop_front();
	}

	// check if the centipede is about to hit the mushroom, and turn if needed
	if (checkImminentMushroomHit(pedes.front(), mushrooms)) {
		directionQueue.push_back(currentDirection == Direction::LEFT ? Direction::RIGHT : Direction::LEFT);
		currentDirection = Direction::DOWN;
	}

	// if the centipede is still coming down from the top (at the start of the game)
	// keep it coming down
	if (pedes.front().getGridPosition().y < TOP_BAR_HEIGHT / GRID_SIZE_PIXELS) {
		currentDirection = Direction::DOWN;
	}

	// initialize variables to save the location and rotation of the previous pede
	sf::Vector2f prevGridPos;
	float prevRotation = 0.0;

	for (auto& pede : pedes) {

		sf::Vector2f gridPos = pede.getGridPosition();

		if (pede.isHeadPede()) {

			// the logic is a little complicated for the head pede

			sf::Vector2f newGridPos;

			switch (currentDirection) {
			case DOWN:
				// if the pede is moving downwards
				prevRotation = 90.f;
				newGridPos = sf::Vector2f(gridPos.x, gridPos.y + 1.0f);

				if (newGridPos.x == NUM_HORIZONTAL_GRID - 1) {
					// turn left if it's at the right edge
					directionQueue.clear();
					directionQueue.push_back(Direction::LEFT);
				}
				else if (newGridPos.x == 0 || directionQueue.empty()) {
					// turn right if it's at the left edge
					directionQueue.clear();
					directionQueue.push_back(Direction::RIGHT);
				}
				else if (newGridPos.y < TOP_BAR_HEIGHT / GRID_SIZE_PIXELS) {
					// keep coming down if it's still in the top portion of the window
					directionQueue.clear();
					directionQueue.push_back(Direction::DOWN);
				}

				break;
			case RIGHT:
				prevRotation = 0.0f;
				newGridPos = sf::Vector2f(gridPos.x + 1.0f, gridPos.y);

				// keep going unless it is at the right edge, then turn down
				if (newGridPos.x == NUM_HORIZONTAL_GRID - 1) {
					directionQueue.clear();
					directionQueue.push_back(Direction::DOWN);
				}

				break;

			case LEFT:
				prevRotation = 180.f;
				newGridPos = sf::Vector2f(gridPos.x - 1.0f, gridPos.y);

				// keep going unless it is at the left edge, then turn down
				if (newGridPos.x == 0) {
					directionQueue.clear();
					directionQueue.push_back(Direction::DOWN);
				}
				break;
			}

			pede.setGridPosition(newGridPos);
			pede.setRotation(prevRotation);
		}
		else {
			// for body pedes, just copy the preceding pede
			pede.setGridPosition(prevGridPos);
			float originalRotation = pede.getRotation();
			pede.setRotation(prevRotation);
			prevRotation = originalRotation;
		}

		// save the position of the previous pede
		prevGridPos = sf::Vector2f(gridPos);
	}
}

/**
 * @brief Check if there is any damage to the centipede by laserblasts
 * @param starship		Reference to the starship object
 * @param headTexture	Centipede head texture
 * @return List of list of pedes, type of damage incurred, and position of the new mushroom if needed
 */
std::tuple<std::list<std::list<Pede>>, DamageType, sf::Vector2f> Centipede::checkDamage(Starship& starship, sf::Texture& headTexture)
{
	// clean up stray laser blasts (preemptive)
	starship.removeDestroyedBlasts();

	int index = 0;
	for (auto& laserblast : starship.getLaserblasts()) {
		// for each laserblast
		for (auto& pede : pedes) {
			// check if it hits a pede
			sf::FloatRect lbBounds = laserblast.getSprite().getGlobalBounds();
			sf::FloatRect pedeBounds = pede.getSprite().getGlobalBounds();

			if (lbBounds.intersects(pedeBounds)) {

				// destroy the pede and the laserblast
				pede.destroy();
				starship.destroyLaserblast(index);
				starship.removeDestroyedBlasts();

				// if so, handle the damage logic
				return postDamageUpdate(headTexture);
			}
		}

		index++;
	}

	// if there is no damage, just send out the current pedes
	std::list<std::list<Pede>> newPedeList;
	newPedeList.push_back(pedes);

	return std::make_tuple(newPedeList, NO_DAMAGE, sf::Vector2f(-1, -1));
}

/**
 * @brief Handle the damage on the centipede, with either splitting or shortening
 * @param headTexture	Centipede head texture
 * @return List of list of pedes, type of damage incurred, and position of the new mushroom if needed
 */
std::tuple<std::list<std::list<Pede>>, DamageType, sf::Vector2f> Centipede::postDamageUpdate(sf::Texture& headTexture) {

	std::list<std::list<Pede>> newPedes;

	int index = 0;
	for (auto& pede : pedes) {
		// get to the damaged pede
		if (pede.getState() == Pede::PedeState::DESTROYED) {

			if (pede.isHeadPede()) {
				// if the pede is a head pede

				sf::Vector2f oldGridPos = pede.getGridPosition();

				// just shorten the pede if it is not the last one
				if (pedes.size() > 1) {
					pedes.pop_front();
					Pede oldPede = pedes.front();
					Pede newHeadPede = Pede(true, oldPede.getGridPosition(), oldPede.getRotation(), headTexture);
					pedes.pop_front();
					pedes.push_front(newHeadPede);

					newPedes.push_back(pedes);
				}

				// then set the head coordinate to mushroom
				return std::make_tuple(newPedes, HEAD_DAMAGED, oldGridPos);
			}
			else if (index + 1 == pedes.size()) {
				// if the pede is a tail pede, just throw it away; no mushroom

				pedes.pop_back();
				newPedes.push_back(pedes);
				return std::make_tuple(newPedes, BODY_DAMAGED, sf::Vector2f(-1, -1));
			}
			else {
				// if the pede is a middle pede, instantiate two portions

				std::list<Pede> firstPortion;
				std::list<Pede> secondPortion;

				// splice the old centipede into two list of pedes
				auto firstEnd = std::next(pedes.begin(), index);
				auto secondStart = std::next(pedes.begin(), index + 1);

				firstPortion.splice(firstPortion.begin(), pedes, pedes.begin(), firstEnd);
				secondPortion.splice(secondPortion.begin(), pedes, secondStart, pedes.end());

				// switch out the first pede in the second portion into a head
				Pede oldPede = secondPortion.front();
				Pede newHeadPede = Pede(true, oldPede.getGridPosition(), oldPede.getRotation(), headTexture);
				secondPortion.pop_front();
				secondPortion.push_front(newHeadPede);

				newPedes.push_back(firstPortion);
				newPedes.push_back(secondPortion);

				return std::make_tuple(newPedes, BODY_DAMAGED, sf::Vector2f(-1, -1));
			}
		}

		index++;
	}

	// this should not be reached!
	//return std::make_tuple(newPedes, -1);
	throw;
}

/**
 * @brief Get the current direction that the head pede is moving
 * @return direction of the head pede
 */
Direction Centipede::getCurrentDirection()
{
	return currentDirection;
}

/**
 * @brief Get the direction queue
 * @return direction queue
 */
std::list<Direction> Centipede::getCurrentDirectionQueue()
{
	return directionQueue;
}

