#include "LaserBlast.h"

#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;


LaserBlast::LaserBlast(sf::Vector2f initPosition)
{

	position = sf::Vector2f(initPosition.x + BLAST_X_OFFSET, initPosition.y);
	state = LaserBlastState::TRAVELLING;

	blastSprite.setSize(sf::Vector2f(BLAST_WIDTH_PIXELS, BLAST_HEIGHT_PIXELS));
	blastSprite.setFillColor(sf::Color(255, 0, 0, 128));
	blastSprite.setPosition(position);

}

sf::Vector2f LaserBlast::getPosition()
{
	return position;
}

LaserBlast::LaserBlastState LaserBlast::getState()
{
	return state;
}

void LaserBlast::refresh()
{
	if (state != LaserBlastState::TRAVELLING) {
		return;
	}

	position.y -= movementDelta;
	blastSprite.setPosition(position);

	if (position.y <= 0) {
		state = LaserBlastState::DESTROYED;
	}
}

sf::RectangleShape LaserBlast::getSprite()
{
	return blastSprite;
}

void LaserBlast::destroy()
{
	state = LaserBlastState::DESTROYED;
}




