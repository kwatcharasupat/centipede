


// Include important C++ libraries here

#include <list>
#include <random>
#include <string>

#include "Centipedes.h"
#include "constants.h"
#include "LivesDisplay.h"
#include "Mushroom.h"
#include "Spider.h"
#include "Starship.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <utility>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

void startupSequence(RenderWindow& window);
void mainSequence(RenderWindow& window);
void gameOverSequence(RenderWindow& window, bool won);
std::list<Mushroom> populateMushrooms(std::list<Mushroom>& mushrooms);
void render(RenderWindow& window,
	Starship& starship,
	Spider& spider,
	std::list<Mushroom>& mushrooms,
	Centipedes& centipedes,
	sf::Text& scoreDisplay,
	LivesDisplay& livesDisplay,
	sf::RectangleShape bloodScreen,
	int score,
	int bloodLevel
);

int main() {
	// Create a video mode object
	VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create and open a window for the game
	RenderWindow window(vm, "Centipede", sf::Style::Default);

	while (window.isOpen()) {
		startupSequence(window);
		mainSequence(window);
	}
	return 0;
}

void startupSequence(RenderWindow& window) {
	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/Startup Screen BackGround.png");

	// Create a sprite
	Sprite spriteBackground(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(sf::Vector2f(0.f, 0.f));
	// Clear everything from the last frame
	window.clear();

	// Draw our game scene here
	window.draw(spriteBackground);

	// Show everything we just drew
	window.display();

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
		}
	}

	return;
}

void mainSequence(RenderWindow& window) {
	srand(RANDOM_SEED); // fixed seed for now


	std::list<Mushroom> mushrooms;
	populateMushrooms(mushrooms);

	sf::Vector2f starshipInitialPosition =
		sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - BOTTOM_BAR_HEIGHT);
	Starship starship(starshipInitialPosition);

	sf::Vector2f spiderInitialPosition =
		sf::Vector2f(WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT);
	Spider spider(spiderInitialPosition);

	Centipedes centipedes(NUM_CENTIPEDE_SEGMENTS,
		sf::Vector2f((int)(NUM_HORIZONTAL_GRID / 2), 0));

	LivesDisplay livesDisplay(NUM_LIVES, sf::Vector2f(LIVES_DISPLAY_POSITION_X,
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

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed ||
				event.type == sf::Event::KeyReleased) {
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					window.close();
				}

				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					starship.fire();
				}

				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					starship.moveLeft();

					sf::FloatRect starshipBounds = starship.getSprite().getGlobalBounds();

					for (auto& mushroom : mushrooms) {
						if (starshipBounds.intersects(
							mushroom.getSprite().getGlobalBounds())) {
							starship.moveRight();
							break;
						}
					}
				}

				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					starship.moveRight();
					sf::FloatRect starshipBounds = starship.getSprite().getGlobalBounds();

					for (auto& mushroom : mushrooms) {
						if (starshipBounds.intersects(
							mushroom.getSprite().getGlobalBounds())) {
							starship.moveLeft();
							break;
						}
					}
				}

				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					starship.moveUp();
					sf::FloatRect starshipBounds = starship.getSprite().getGlobalBounds();

					for (auto& mushroom : mushrooms) {
						if (starshipBounds.intersects(
							mushroom.getSprite().getGlobalBounds())) {
							starship.moveDown();
							break;
						}
					}
				}

				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					starship.moveDown();
					sf::FloatRect starshipBounds = starship.getSprite().getGlobalBounds();

					for (auto& mushroom : mushrooms) {
						if (starshipBounds.intersects(
							mushroom.getSprite().getGlobalBounds())) {
							starship.moveUp();
							break;
						}
					}
				}

				if (Keyboard::isKeyPressed(Keyboard::A)) {
					for (Mushroom& mushroom : mushrooms) {
						if (mushroom.getState() == Mushroom::MushroomState::ACTIVE) {
							mushroom.damage();
							break;
						}
					}
				}

				if (Keyboard::isKeyPressed(Keyboard::B)) {
					for (Mushroom& mushroom : mushrooms) {
						if (mushroom.getState() == Mushroom::MushroomState::DAMAGED) {
							mushroom.damage();
							break;
						}
					}
				}
			}
		}

		starship.refresh();
		spider.refresh();
		auto [scoreChange, newMushroomPosList] =
			centipedes.refresh(mushrooms, starship);
		starship.removeDestroyedBlasts();

		if (centipedes.getCentipedes().size() == 0) {
			return gameOverSequence(window, true);
		}

		score += scoreChange;

		for (auto& mushroomPos : newMushroomPosList) {
			Mushroom mushroom(mushroomPos);
			mushrooms.push_back(mushroom);
		}

		sf::FloatRect starshipBounds = starship.getSprite().getGlobalBounds();
		sf::FloatRect spiderBounds = spider.getSprite().getGlobalBounds();

		if (starshipBounds.intersects(spiderBounds)) {
			populateMushrooms(mushrooms);
			starship.setPosition(starshipInitialPosition);
			spider.setPosition(spiderInitialPosition);

			livesDisplay.die();

			bloodLevel = 255;

			if (livesDisplay.getCurrentLives() <= 0) {
				return gameOverSequence(window, false);
			}
		}

		for (auto& centipede : centipedes.getCentipedes()) {
			for (auto& pedeSprites : centipede.getSprites()) {
				if (starshipBounds.intersects(pedeSprites.getGlobalBounds())) {
					populateMushrooms(mushrooms);
					starship.setPosition(starshipInitialPosition);
					spider.setPosition(spiderInitialPosition);

					livesDisplay.die();

					bloodLevel = 255;

					if (livesDisplay.getCurrentLives() <= 0) {
						return gameOverSequence(window, false);
					}
				}
			}
		}

		// check if a laserblast has hit a mushroom or a spider
		int index = 0;
		for (auto& laserblast : starship.getLaserblasts()) {
			sf::FloatRect lbSpriteBounds = laserblast.getSprite().getGlobalBounds();

			if (lbSpriteBounds.intersects(spiderBounds)) {
				spider.destroy();
				starship.destroyLaserblast(index);
				score += SPIDER_POINTS;
				continue;
			}

			for (auto& mushroom : mushrooms) {
				if (mushroom.getState() == Mushroom::MushroomState::DESTROYED) {
					continue;
				}

				sf::FloatRect mushroomBounds = mushroom.getSprite().getGlobalBounds();

				if (lbSpriteBounds.intersects(mushroomBounds)) {
					mushroom.damage();
					starship.destroyLaserblast(index);

					if (mushroom.getState() == Mushroom::MushroomState::DESTROYED) {
						score += MUSHROOM_POINTS;
					}
					break;
				}
			}

			index++;
		}

		// check if the spider has hit a mushroom
		for (auto& mushroom : mushrooms) {
			if (mushroom.getState() == Mushroom::MushroomState::DESTROYED) {
				continue;
			}
			sf::FloatRect mushroomBounds = mushroom.getSprite().getGlobalBounds();

			if (spiderBounds.intersects(mushroomBounds)) {
				mushroom.destroy();
			}
		}

		starship.removeDestroyedBlasts();
		mushrooms.remove_if([](auto& mushroom) {
			return mushroom.getState() == Mushroom::MushroomState::DESTROYED;
			});

		render(
			window,
			starship,
			spider,
			mushrooms,
			centipedes,
			scoreDisplay,
			livesDisplay,
			bloodScreen,
			score,
			bloodLevel
		);
	}

	return;
}

void render(RenderWindow& window,
	Starship& starship,
	Spider& spider,
	std::list<Mushroom>& mushrooms,
	Centipedes& centipedes,
	sf::Text& scoreDisplay,
	LivesDisplay& livesDisplay,
	sf::RectangleShape bloodScreen,
	int score,
	int bloodLevel
) {
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

	scoreDisplay.setString(std::to_string(score));
	scoreDisplay.setPosition(sf::Vector2f(
		WINDOW_WIDTH / 2 - scoreDisplay.getGlobalBounds().getSize().x / 2.0,
		SCORE_Y_OFFSET));
	window.draw(scoreDisplay);

	bloodScreen.setFillColor(sf::Color(255, 0, 0, bloodLevel));
	window.draw(bloodScreen);
	bloodLevel = std::max(bloodLevel - 1, 0);

	window.display();
}

void gameOverSequence(RenderWindow& window, bool won) {
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	sf::Text textDisplay;
	textDisplay.setFont(font);
	textDisplay.setCharacterSize(30);
	textDisplay.setFillColor(sf::Color(255, 255, 255));

	if (won) {
		textDisplay.setString("YOU WON! HIT ENTER TO CONTINUE.");
	}
	else {
		textDisplay.setString("GAME OVER! HIT ENTER TO CONTINUE.");
	}

	sf::Vector2 size = textDisplay.getGlobalBounds().getSize();
	textDisplay.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - size.x / 2.0,
		WINDOW_HEIGHT / 2 - size.y / 2.0));

	window.clear();
	window.draw(textDisplay);
	window.display();

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			return;
		}
	}
}

std::list<Mushroom> populateMushrooms(std::list<Mushroom>& mushrooms) {
	auto currentMushroomCount = mushrooms.size();

	if (currentMushroomCount >= NUM_MUSHROOMS) {
		return mushrooms;
	}

	std::mt19937 gen(RANDOM_SEED);
	std::uniform_int_distribution<int> uniformDistributionHorizontal(
		0, NUM_HORIZONTAL_GRID - 1);
	std::uniform_int_distribution<int> uniformDistributionVertical(
		0, NUM_VERTICAL_GRID - 1);

	bool isOverlapped;

	for (auto i = currentMushroomCount; i < NUM_MUSHROOMS; i++) {
		isOverlapped = true;
		sf::Vector2f mushroomCoordinate;

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

		Mushroom mushroom(mushroomCoordinate);

		mushrooms.push_back(mushroom);
	}

	return mushrooms;
}
