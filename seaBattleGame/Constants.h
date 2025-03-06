#pragma once

#include "Windows.h"

const int PLAYGROUND_SIZE = 10;
const char ALPHABET_HEADER[] = "ABCDEFGHIJ";
const int NUMERIC_HEADER[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
const int MAX_SIZE_OF_SHIP = 4;
const int BESIDES_NUMBER = 9;

const int PC = 0;
const int PLAYER = 1;
const int NEW_PLAYER = 2;
const bool HORIZONTAL = 0;
const bool VERTICAL = 1;

const char DELETE_SYMBOL[] = "\b  ";

const short HEADER_Y = 12;
const short PLAYER_X = 30;

const char PATH_PLAYER[] = "C:/study/projects/seaBattle 2.0/save/player.txt";
const char PATH_PC[] = "C:/study/projects/seaBattle 2.0/save/pc.txt";
const char HEADER_PLAYER[] = "  PLAYER  ";
const char HEADER_PC[] = "   ENEMY   ";
const char EMPTY_STRING[] = "                                                    ";
const int BORDERS = 2;

const char NEW_GAME = '1';
const char CONTINUE_LAST_GAME = '2';
const char SAVE = '1';

const int WIN = 1;
const int LOSE = 0;
const int NOT_OVER = -1;

const char HIT = 'x';
const char MISS = 'o';
const char PART_OF_SHIP = '#';
const char EMPTY_SPACE = ' ';

const int RED_ON_WHITE = 4 + 7 * 16;
const int GREEN_ON_WHITE = 2 + 7 * 16;
const int CLASSIC = 7 * 16;
const int LIGHT_YELLOW = 6 + 6 * 16;
const char BLACK_TEXT_ON_WHITE_BACKGROUND[] = "Color 70";

const int ENTER = 13;
const int SPACE = 32;
const int BACKSPACE = 8;
const int ESCAPE = 27;

const int STOP_GAME = -1;

struct notDestroyedShip {
	bool exists;
	COORD ship[MAX_SIZE_OF_SHIP];
	int shipSize;
	bool orientation;
	COORD variations[MAX_SIZE_OF_SHIP];
	int varCount;
	COORD nextMove;
};

