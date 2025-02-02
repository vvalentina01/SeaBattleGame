#pragma once
#include "Constants.h"

void createPCPlayground(char (*p)[PLAYGROUND_SIZE]);
void createShip(int n, char (*p)[PLAYGROUND_SIZE]);
bool checkoutShip(int n, COORD sheep[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE]);
bool checkoutBeside(int x, int y, char (*p)[PLAYGROUND_SIZE]);;