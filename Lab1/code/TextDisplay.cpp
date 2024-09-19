/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Classes for handling text and score display
*
*/

#include "constants.h"
#include "TextDisplay.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

/**
 * @brief Class for displaying generic text
 * @param yPosition_		Vertical offset
 * @param characterSize_	Font size
 */
TextDisplay::TextDisplay(float yPosition_, unsigned int characterSize_)
{

	yPosition = yPosition_;
	characterSize = characterSize_;

	font.loadFromFile("fonts/KOMIKAP_.ttf");

	textSprite.setFont(font);
	textSprite.setCharacterSize(characterSize);
	textSprite.setFillColor(textColor);
}

/**
 * @brief Set string and center the sprite
 * @param string	String to be set
 */
void TextDisplay::setString(const sf::String& string)
{

	textSprite.setString(string);

	sf::Vector2f size = textSprite.getGlobalBounds().getSize();

	float xActualPosition = (float)(WINDOW_WIDTH / 2.0f - size.x / 2.0f);
	float yActualPosition = (float)(yPosition < 0 ? WINDOW_HEIGHT / 2.0f - size.y / 2.0 : yPosition);


	textSprite.setPosition(sf::Vector2f(xActualPosition, yActualPosition));
}

/**
 * @brief Get the sprite
 * @return sprite
 */
sf::Text TextDisplay::getSprite()
{
	return textSprite;
}

/**
 * @brief Class for displaying score
 * @param yPosition			Vertical offset
 * @param characterSize		Font size
 */
ScoreDisplay::ScoreDisplay(float yPosition, unsigned int characterSize) : TextDisplay(yPosition, characterSize)
{
	score = 0;
}

/**
 * @brief Update the score by the amount of change
 * @param scoreDelta	Score change
 */
void ScoreDisplay::updateScore(int scoreDelta)
{
	score += scoreDelta;
	setString(std::to_string(score));
}


/**
 * @brief Update the score directly
 * @param score_	New score
 */
void ScoreDisplay::setScore(int score_)
{
	score = score_;
	setString(std::to_string(score));
}
