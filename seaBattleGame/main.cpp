#pragma execution_character_set("utf-8")
#define  _CRT_SECURE_NO_WARNINGS 

#include "Constants.h"
#include "gameProcess.h"
#include "PlaygroundCreating.h"
#include "Utils.h"

#include <conio.h>
#include <locale.h>  
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Windows.h"

char startMenu() {
	setCursor({ 0,0 });
	printf("***** Welcome to Sea Battle *****\n");
	printf("\t* - New Game\n");
	printf("\t* - Continue Last Game\n");
	printf("\n");
	printf("use W and S to move\n");
	printf("use ENTER to choose\n");
	return menuCursor({ 8, 1 });
}
}

void cleanScreen(int n)
{
	for (int i = 0; i < n; ++i)
	{
		setCursor({ 0, (short)i });
		printf(EMPTY_STRING);
	}
}

int main()
{
	system(BLACK_TEXT_ON_WHITE_BACKGROUND);
	setlocale(LC_ALL, "Ru");
	srand(time(NULL));

	char pcPlayground[PLAYGROUND_SIZE][PLAYGROUND_SIZE];
	char playerPlayground[PLAYGROUND_SIZE][PLAYGROUND_SIZE];
	for (int i = 0; i < PLAYGROUND_SIZE; i++) {
		for (int j = 0; j < PLAYGROUND_SIZE; j++)
		{
			pcPlayground[i][j] = ' ';
			playerPlayground[i][j] = ' ';
		}
	}

	char isNewGame = startMenu();
	cleanScreen(HEADER_Y);
	if (isNewGame == NEW_GAME) {
		setCursor({ 0, 3 });
		printf("Set your ships:\n");
		printf("\tWASD - move\n");
		printf("\tSPACE - add part of a ship\n");
		printf("\tENTER - finish adding a ship");
		createPlayerPlayground(playerPlayground);
		createPCPlayground(pcPlayground);
	}

	if (isNewGame == CONTINUE_LAST_GAME) {
		loadPlayground(playerPlayground, PLAYER);
		loadPlayground(pcPlayground, PC);
	}
	cleanScreen(25);
	printPlayground(pcPlayground, PC);
	printPlayground(playerPlayground, PLAYER);
	setCursor({ 0, 0 });
	printf("\tGame is started\t");

	int roundCounter = 1;
	int gameStatus = NOT_OVER;
	int varSize = PLAYGROUND_SIZE * PLAYGROUND_SIZE;
	COORD* variations = (COORD*)malloc(varSize * sizeof(COORD));
	if (variations == NULL)
		return 0; // add comment to user
	notDestroyedShip nds{};
	COORD currentPosition = { 2, HEADER_Y + 2 };
	for (short i = 0; i < PLAYGROUND_SIZE; ++i)
		for (short j = 0; j < PLAYGROUND_SIZE; ++j)
			variations[i * PLAYGROUND_SIZE + j] = { i, j };

	while (gameStatus == NOT_OVER) { 
		setCursor({ 0, 1 });
		printf("Round %d: ", roundCounter);
		setCursor({ 0, 2 });
		printf("PLAYER MOVE");

		bool playerMove = true;
		while (playerMove) {
			playerMove = playerShoot(pcPlayground, currentPosition);
			for (int i = 3; i < 7; ++i) {
				setCursor({ 0, (short)i });
				printf(EMPTY_STRING);
			}
		}
		gameStatus = isGameOver(playerPlayground, pcPlayground);
		if (gameStatus == NOT_OVER) {
			setCursor({ 0, 2 });
			printf(EMPTY_STRING);
			setCursor({ 0, 2 });
			printf("PC MOVE");
			bool pcMove = true;
			while (pcMove) {
				pcMove = pcShoot(playerPlayground, variations, varSize, nds);
				for (int i = 3; i < 7; ++i) {
					setCursor({ 0, (short)i });
					printf(EMPTY_STRING);
				}
			}
			gameStatus = isGameOver(playerPlayground, pcPlayground);
		}
		++roundCounter;
	}
}
