#include "Centipedes.h"

Centipedes::Centipedes(int numSegments, sf::Vector2f initialGridPosition)
{

	headTexture.loadFromFile("graphics/CentipedeHead.png");
	bodyTexture.loadFromFile("graphics/CentipedeBody.png");

	centipedes.push_back(Centipede(numSegments, initialGridPosition, headTexture, bodyTexture));

	clock.restart();
	timeOfLastMovement = clock.getElapsedTime();
}

std::list<Centipede> Centipedes::getCentipedes()
{
	return centipedes;
}


std::tuple<int, std::list <sf::Vector2f>> Centipedes::checkDamage(Starship& starship) {



	std::list<Centipede> newCentipedes;
	int totalScoreChange = 0;
	std::list <sf::Vector2f> newMushroomGridPosList;

	bool anyDamage = false;

	for (auto& centipede : centipedes) {

		MovementDirection originalDirection = centipede.getCurrentDirection();
		std::list<MovementDirection> originalDirectionQueue = centipede.getCurrentDirectionQueue();

		std::tuple<std::list<std::list<Pede>>, DamageType, sf::Vector2f> damageCheckReturn = centipede.checkDamage(starship, headTexture);

		auto [pedesList, damageType, newMushroomGridPos] = damageCheckReturn;

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

	return std::make_tuple(totalScoreChange, newMushroomGridPosList);
}


std::tuple<int, std::list <sf::Vector2f>> Centipedes::refresh(std::list<Mushroom>& mushrooms, Starship& starship)
{
	starship.removeDestroyedBlasts();

	auto [scoreChange, newMushroomGridPosList] = checkDamage(starship);

	if ((clock.getElapsedTime() - timeOfLastMovement).asSeconds() > timeBeforeMovement) {
		for (auto& centipede : centipedes) {
			centipede.refresh(mushrooms);
		}

		timeOfLastMovement = clock.getElapsedTime();

	}
	return std::make_tuple(scoreChange, newMushroomGridPosList);

}
