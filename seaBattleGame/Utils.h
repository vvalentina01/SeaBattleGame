#pragma once
#include "Constants.h"

void savePlayground(char (*p)[PLAYGROUND_SIZE], bool who);
void printPlayground(char (*p)[PLAYGROUND_SIZE], int who);
void loadPlayground(char (*p)[PLAYGROUND_SIZE], int who);
