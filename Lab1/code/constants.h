/*
*
* Author:			Karn Watcharasupat
* Class:			ECE6122
* Last Modified:	9/18/2024
*
* Description:		Header file for all of the game parameters
*
*/

#pragma once

// Random seed
static bool USE_FIXED_RANDOM_SEED = false;
static int RANDOM_SEED = 6122;

// Window setup
static int WINDOW_WIDTH = 1024;
static int WINDOW_HEIGHT = 720;
static int GRID_SIZE_PIXELS = 32;

// Screen sections
static int TOP_BAR_HEIGHT = 4 * GRID_SIZE_PIXELS;
static int BOTTOM_BAR_HEIGHT = 2 * GRID_SIZE_PIXELS;
static int MAIN_HEIGHT = WINDOW_HEIGHT - (TOP_BAR_HEIGHT + BOTTOM_BAR_HEIGHT);

// Grid setup
static int NUM_HORIZONTAL_GRID = int(WINDOW_WIDTH / GRID_SIZE_PIXELS);
static int NUM_VERTICAL_GRID = int(MAIN_HEIGHT / GRID_SIZE_PIXELS);


// Lives
static short NUM_LIVES = 3;
static int LIVES_DISPLAY_POSITION_X = (WINDOW_WIDTH / 2) + 8 * GRID_SIZE_PIXELS;
static int LIVES_DISPLAY_POSITION_Y = GRID_SIZE_PIXELS;

// Mushroom
static int NUM_MUSHROOMS = 30;

// Starship
static int MAX_STARSHIP_Y_COORDINATE = WINDOW_HEIGHT - 8 * GRID_SIZE_PIXELS;
static float STARSHIP_MOVEMENT_DELTA = 5.f;

// Laserblast
static float LASERBLAST_MOVEMENT_DELTA = 0.5f;
static int BLAST_WIDTH_PIXELS = 5;
static int BLAST_HEIGHT_PIXELS = 16;
static int BLAST_X_OFFSET = (int)((GRID_SIZE_PIXELS - BLAST_WIDTH_PIXELS) / 2);

// Spider
static float SPIDER_MOVEMENT_DELTA = 0.1f;
static float SPIDER_SECONDS_BEFORE_DIRECTION_CHANGE = 2.0f;
static float SPIDER_SECONDS_BEFORE_REVIVAL = 2.0f;

// Centipede
static int NUM_CENTIPEDE_SEGMENTS = 30;
static float CENTIPEDE_SECONDS_BEFORE_MOVEMENT = 0.5f;

// Damage points
static int MUSHROOM_POINTS = 4;
static int SPIDER_POINTS = 600;
static int CENTIPEDE_BODY_POINTS = 10;
static int CENTIPEDE_HEAD_POINTS = 100;

// Text display
static int SCORE_Y_OFFSET = 8;
static unsigned int SCORE_FONTSIZE = 90;
static unsigned int GAMEOVER_FONTSIZE = 90;