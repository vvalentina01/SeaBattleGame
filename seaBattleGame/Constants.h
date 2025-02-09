#pragma once

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

const char messagePrintCoord[] = "Введите координаты: ";
const char messageUncorrectCoord[] = "Некорректные координаты!";
const char DELETE_SYMBOL[] = "\b  ";

const short HEADER_Y = 10;
const short PLAYER_X = 30;

const char PATH_PLAYER[] = "C:/study/projects/seaBattle 2.0/save/player.txt";
const char PATH_PC[] = "C:/study/projects/seaBattle 2.0/save/pc.txt";
const char HEADER_PLAYER[] = "Поле игрока";
const char HEADER_PC[] = "Поле противника";