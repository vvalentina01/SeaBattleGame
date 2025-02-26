#pragma once
#define  _CRT_SECURE_NO_WARNINGS 

#include "Constants.h"
#include "Windows.h"

bool shootTrying(char (*p)[PLAYGROUND_SIZE], COORD position);
bool playerShoot(char (*p)[PLAYGROUND_SIZE]);
int isGameOver(char (*player)[PLAYGROUND_SIZE], char (*pc)[PLAYGROUND_SIZE]);
bool pcShoot(char (*p)[PLAYGROUND_SIZE], COORD* variations, int &varSize);
bool isShipDestroyed(COORD position, char (*p)[PLAYGROUND_SIZE], int who);
void markAroundAsEmpty(int n, bool orientation, COORD ship[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE], int who);
void resultOfMove(bool result, COORD position, int who, char (*p)[PLAYGROUND_SIZE]);