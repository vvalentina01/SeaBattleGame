#pragma once
#include "Constants.h"

bool savePlayground(char (*p)[PLAYGROUND_SIZE], bool who);
bool printPlayground(char (*p)[PLAYGROUND_SIZE], int who);
int loadPlayground(char (*p)[PLAYGROUND_SIZE], int who);
void setCursor(COORD position);
char inputCoordinates(COORD* position, int who);
void printColorSymbol(char symbol);
char menuCursor(COORD position);
bool cleanSavingFiles();
void cleanScreen(int n);
void gameIsFailed(int errorType);