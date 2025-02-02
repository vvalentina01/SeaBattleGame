#pragma once
#include "Constants.h"

void createPCPlayground(char (*p)[SIZE]);
void createShip(int n, char (*p)[SIZE]);
bool checkoutShip(int n, COORD sheep[MAX_SIZE_OF_SHIP], char (*p)[SIZE]);
bool checkoutBeside(int x, int y, char (*p)[SIZE]);;