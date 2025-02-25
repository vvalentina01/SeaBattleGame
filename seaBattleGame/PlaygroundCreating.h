#pragma once
#include "Constants.h"

#include "Windows.h"

void createPCPlayground(char (*p)[PLAYGROUND_SIZE]);
void createShip(int n, char (*p)[PLAYGROUND_SIZE]);
bool checkoutShip(int n, COORD sheep[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE]);
bool checkoutBeside(int x, int y, char (*p)[PLAYGROUND_SIZE]);;
void createPlayerPlayground(char (*p)[PLAYGROUND_SIZE]);
bool checkoutShip(int n, COORD ship[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE]);
bool checkoutPlayerShip(int n, COORD ship[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE]);
void sortCoordinates(int n, bool orientation, COORD ship[MAX_SIZE_OF_SHIP]);
int inputNewShip(COORD(*ship)[MAX_SIZE_OF_SHIP]);
void printInstructions(short type, int n);