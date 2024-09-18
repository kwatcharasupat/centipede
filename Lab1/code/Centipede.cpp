#include "Centipede.h"
#include "constants.h"
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

Centipede::Centipede(int initialNumSegments, sf::Vector2f initialGridPosition, Texture& headTexture_, Texture& bodyTexture)
{
	numSegments = initialNumSegments;

	for (int i = 0; i < numSegments; i++) {
		sf::Vector2f pedeGridPosition(initialGridPosition.x, initialGridPosition.y - (float)i);
		bool isHead = i == 0;
		Pede pede(isHead, pedeGridPosition, 0.0f, isHead ? headTexture_ : bodyTexture);

		pedes.push_back(pede);
	}

	currentDirection = DOWN;
}

Centipede::Centipede(std::list<Pede>& pedes_, MovementDirection currentDirection_, std::list<MovementDirection>& directionQueue_)
{
	numSegments = pedes.size();

	pedes = pedes_;
	currentDirection = currentDirection_;
	directionQueue = directionQueue_;
}

std::list<sf::Sprite> Centipede::getSprites()
{
	std::list<sf::Sprite> sprites;
	for (auto& pede : pedes) {
		sprites.push_back(pede.getSprite());
	}

	return sprites;
}

bool Centipede::checkImminentMushroomHit(Pede& headPede, std::list<Mushroom>& mushrooms) {

	if (currentDirection == DOWN) {
		return false;
	}

	const sf::Vector2f gridPos = headPede.getGridPosition();
	sf::Vector2f futureGridPos;

	switch (currentDirection) {
	case LEFT:
		futureGridPos = sf::Vector2f(gridPos.x - 1.0, gridPos.y);
		break;
	case RIGHT:
		futureGridPos = sf::Vector2f(gridPos.x + 1.0, gridPos.y);
		break;
	}

	headPede.setGridPosition(futureGridPos);

	sf::FloatRect headPedeBounds = headPede.getSprite().getGlobalBounds();
	bool willHit = false;

	for (auto& mushroom : mushrooms) {
		sf::FloatRect mushroomBounds = mushroom.getSprite().getGlobalBounds();
		if (headPedeBounds.intersects(mushroomBounds)) {
			willHit = true;
			break;
		}
	}

	headPede.setGridPosition(gridPos);

	return willHit;

}




void Centipede::refresh(std::list<Mushroom>& mushrooms)
{
	if (directionQueue.size() > 0) {
		currentDirection = directionQueue.front();
		directionQueue.pop_front();
	}

	if (checkImminentMushroomHit(pedes.front(), mushrooms)) {
		directionQueue.push_back(currentDirection == MovementDirection::LEFT ? MovementDirection::RIGHT : MovementDirection::LEFT);
		currentDirection = MovementDirection::DOWN;
	}

	if (pedes.front().getGridPosition().y < TOP_BAR_HEIGHT / GRID_SIZE_PIXELS) {
		currentDirection = MovementDirection::DOWN;
	}

	sf::Vector2f prevGridPos;
	float prevRotation = 0.0;

	for (auto& pede : pedes) {

		sf::Vector2f gridPos = pede.getGridPosition();

		if (pede.isHeadPede()) {

			sf::Vector2f newGridPos;

			switch (currentDirection) {
			case DOWN:
				prevRotation = 90.f;
				newGridPos = sf::Vector2f(gridPos.x, gridPos.y + 1.0f);

				if (newGridPos.x == NUM_HORIZONTAL_GRID - 1) {
					directionQueue.clear();
					directionQueue.push_back(MovementDirection::LEFT);
				}
				else if (newGridPos.x == 0 || directionQueue.empty()) {
					directionQueue.clear();
					directionQueue.push_back(MovementDirection::RIGHT);
				}
				else if (newGridPos.y < TOP_BAR_HEIGHT / GRID_SIZE_PIXELS) {
					directionQueue.clear();
					directionQueue.push_back(MovementDirection::DOWN);
				}


				break;
			case RIGHT:
				prevRotation = 0.0f;
				newGridPos = sf::Vector2f(gridPos.x + 1.0f, gridPos.y);

				if (newGridPos.x == NUM_HORIZONTAL_GRID - 1) {
					directionQueue.clear();
					directionQueue.push_back(MovementDirection::DOWN);
				}

				break;

			case LEFT:
				prevRotation = 180.f;
				newGridPos = sf::Vector2f(gridPos.x - 1.0f, gridPos.y);
				if (newGridPos.x == 0) {
					directionQueue.clear();
					directionQueue.push_back(MovementDirection::DOWN);
				}
				break;
			}

			pede.setGridPosition(newGridPos);
			pede.setRotation(prevRotation);
		}
		else {
			pede.setGridPosition(prevGridPos);
			float originalRotation = pede.getRotation();
			pede.setRotation(prevRotation);
			prevRotation = originalRotation;
		}

		prevGridPos = sf::Vector2f(gridPos);
	}
}

std::tuple<std::list<std::list<Pede>>, DamageType, sf::Vector2f> Centipede::checkDamage(Starship& starship, sf::Texture& headTexture)
{
	starship.removeDestroyedBlasts();

	int index = 0;
	for (auto& laserblast : starship.getLaserblasts()) {

		if (laserblast.getState() == LaserBlast::LaserBlastState::DESTROYED) {
			continue;
		}

		for (auto& pede : pedes) {
			sf::FloatRect lbBounds = laserblast.getSprite().getGlobalBounds();
			sf::FloatRect pedeBounds = pede.getSprite().getGlobalBounds();

			if (lbBounds.intersects(pedeBounds)) {
				starship.destroyLaserblast(index);
				pede.destroy();

				starship.removeDestroyedBlasts();

				return postDamageUpdate(headTexture);
			}
		}

		index++;
	}

	std::list<std::list<Pede>> newPedeList;
	newPedeList.push_back(pedes);

	return std::make_tuple(newPedeList, NO_DAMAGE, sf::Vector2f(-1, -1));
}

std::tuple<std::list<std::list<Pede>>, DamageType, sf::Vector2f> Centipede::postDamageUpdate(sf::Texture& headTexture) {

	std::list<std::list<Pede>> newPedes;

	int index = 0;
	for (auto& pede : pedes) {
		if (pede.getState() == Pede::PedeState::DESTROYED) {
			if (pede.isHeadPede()) {

				if (pedes.size() > 1) {
					pedes.pop_front();
					Pede oldPede = pedes.front();
					Pede newHeadPede = Pede(true, oldPede.getGridPosition(), oldPede.getRotation(), headTexture);
					pedes.pop_front();
					pedes.push_front(newHeadPede);

					newPedes.push_back(pedes);
				}

				return std::make_tuple(newPedes, HEAD_DAMAGED, pede.getGridPosition());
			}
			else if (index + 1 == pedes.size()) {
				pedes.pop_back();
				newPedes.push_back(pedes);
				return std::make_tuple(newPedes, BODY_DAMAGED, sf::Vector2f(-1, -1));
			}
			else {
				std::list<Pede> firstPortion;
				std::list<Pede> secondPortion;

				auto firstEnd = std::next(pedes.begin(), index);
				auto secondStart = std::next(pedes.begin(), index + 1);

				firstPortion.splice(firstPortion.begin(), pedes, pedes.begin(), firstEnd);

				secondPortion.splice(secondPortion.begin(), pedes, secondStart, pedes.end());
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

MovementDirection Centipede::getCurrentDirection()
{
	return currentDirection;
}

std::list<MovementDirection> Centipede::getCurrentDirectionQueue()
{
	return directionQueue;
}

