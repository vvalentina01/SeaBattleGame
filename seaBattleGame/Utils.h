#pragma once
#include "Constants.h"

bool savePlayground(char (*p)[PLAYGROUND_SIZE], bool who);
void printPlayground(char (*p)[PLAYGROUND_SIZE], int who);
bool loadPlayground(char (*p)[PLAYGROUND_SIZE], int who);
void setCursor(COORD position);
char inputCoordinates(COORD* position, int who);
void printColorSymbol(char symbol);
