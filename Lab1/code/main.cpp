/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Entrypoint for the game
*
*/

#include "CentipedeGame.h"

using namespace sf;
using namespace std;

/**
 * @brief	Main entrypoint function
 * @return	status code
 */
int main() {

	// offload all game logic into a class
	CentipedeGame game;
	game.run();

	return 0;
}
