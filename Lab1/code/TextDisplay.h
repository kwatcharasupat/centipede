#pragma once


#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>

using namespace std;
using namespace sf;
class TextDisplay
{
public:
	TextDisplay(float yPosition, unsigned int characterSize);

	void setString(const sf::String& string);
	sf::Text getSprite();

private:
	sf::Font font;
	unsigned int characterSize = 90;
	sf::Color textColor = sf::Color(255, 255, 255);

	sf::Text textSprite;

	float yPosition;
};

class ScoreDisplay :
	public TextDisplay
{
public:
	ScoreDisplay(float yPosition, unsigned int characterSize);
	void updateScore(int scoreDelta);
	void setScore(int score_);
private:
	int score;
};

