#pragma once
const int SIZE = 10;
const char ALPHABET_HEADER[] = "ABCDEFGHIJ";
const int NUMERIC_HEADER[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
const int MAX_SIZE_OF_SHIP = 4;
const int BESIDES_NUMBER = 9;

const bool PC = 0;
const bool PLAYER = 1;
const bool HORIZONTAL = 0;
const bool VERTICAL = 1;

struct COORD {
	int x;
	int y;
};