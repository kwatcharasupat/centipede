#pragma once

static int WINDOW_WIDTH = 1024;
static int WINDOW_HEIGHT = 720;

static int TOP_BAR_HEIGHT = 64;
static int BOTTOM_BAR_HEIGHT = 32;
static int MAIN_HEIGHT = 569 - (TOP_BAR_HEIGHT + BOTTOM_BAR_HEIGHT);

static int NUM_MUSHROOMS = 60;

static int GRID_SIZE_PIXELS = 32;

static int NUM_HORIZONTAL_GRID = int(WINDOW_WIDTH / GRID_SIZE_PIXELS);
static int NUM_VERTICAL_GRID = int(MAIN_HEIGHT / GRID_SIZE_PIXELS);

static int RANDOM_SEED = 6122;

static int MAX_STARSHIP_Y_COORDINATE = WINDOW_HEIGHT - 256;
static float STARSHIP_MOVEMENT_DELTA = 5;

static float SPIDER_MOVEMENT_DELTA = 0.1;
static float SPIDER_SECONDS_BEFORE_DIRECTION_CHANGE = 1.0;
static float SPIDER_SECONDS_BEFORE_REVIVAL = 5.0;


static float LASERBLAST_MOVEMENT_DELTA = 0.5;
static int BLAST_WIDTH_PIXELS = 5;
static int BLAST_HEIGHT_PIXELS = 27;
static int BLAST_X_OFFSET = (int)((GRID_SIZE_PIXELS - BLAST_WIDTH_PIXELS) / 2);

static short NUM_LIVES = 3;
static int LIVES_DISPLAY_POSITION_X = 600;
static int LIVES_DISPLAY_POSITION_Y = GRID_SIZE_PIXELS;

static int NUM_CENTIPEDE_SEGMENTS = 30;
static float CENTIPEDE_SECONDS_BEFORE_MOVEMENT = 0.5;

static int MUSHROOM_POINTS = 4;
static int SPIDER_POINTS = 600;
static int CENTIPEDE_BODY_POINTS = 10;
static int CENTIPEDE_HEAD_POINTS = 100;

static int SCORE_Y_OFFSET = 8;