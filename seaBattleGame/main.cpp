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
	cleanScreen(SCREEN_SIZE);
	setCursor({ 0,0 });
	printf("***** Welcome to Sea Battle *****\n");
	printf("\t* - New Game\n");
	printf("\t* - Continue Last Game\n");
	printf("\t* - Exit\n");
	printf("\n");
	printf("use W and S to move\n");
	printf("use ENTER to choose\n");
	return menuCursor({ 8, 1 });
}

char saveGame() {
	setCursor({ 0,0 });
	printf("***** Do you want to save the game? *****\n");
	printf("\t* - yes\n");
	printf("\t* - no\n");
	printf("\n");
	printf("use W and S to move\n");
	printf("use ENTER to choose\n");
	return menuCursor({ 8, 1 });
}

void printResults(int gameStatus, char (*player)[PLAYGROUND_SIZE], char (*pc)[PLAYGROUND_SIZE]) {
	switch (gameStatus) {
	case NOT_OVER:
	{
		cleanScreen(SCREEN_SIZE);
		char s = saveGame();
		cleanScreen(SCREEN_SIZE);
		setCursor({ 0,0 });
		if (s == SAVE) {

			if (savePlayground(player, PLAYER) && savePlayground(pc, PC))
				printf("Game is saved!\n");
			else
				printf("Error!\n");
		}
		break;
	}
	case WIN:
		cleanScreen(HEADER_Y);
		setCursor({ 0,0 });
		printf("Congratulations! You win!\n");
		break;
	case LOSE:
		cleanScreen(HEADER_Y);
		setCursor({ 0,0 });
		printf("Oh no! You lose! Maybe you'll win next time?\n");
		break;
	}
}

int main()
{
	system(BLACK_TEXT_ON_WHITE_BACKGROUND);
	setlocale(LC_ALL, "Ru");
	srand(time(NULL));

	while (true) {

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

		if (isNewGame == EXIT)
			return 0;

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
			int loadingResult = loadPlayground(playerPlayground, PLAYER);
			if (loadingResult != SUCCESS_LOAD) {
				gameIsFailed(loadingResult);
				continue;
			}
			loadingResult = loadPlayground(pcPlayground, PC);
			if (loadingResult != SUCCESS_LOAD) {
				gameIsFailed(loadingResult);
				continue;
			}
		}

		cleanScreen(SCREEN_SIZE);
		if (!printPlayground(pcPlayground, PC) || !printPlayground(playerPlayground, PLAYER)) {
			gameIsFailed(OUT_OF_MEMORY);
			continue;
		}

		setCursor({ 0, 0 });
		printf("\tGame is started\t");

		int roundCounter = 1;
		int gameStatus = NOT_OVER;
		int varSize = PLAYGROUND_SIZE * PLAYGROUND_SIZE;
		COORD* variations = (COORD*)malloc(varSize * sizeof(COORD));
		if (variations == NULL) {
			gameIsFailed(OUT_OF_MEMORY);
			continue;
		}
		notDestroyedShip nds{};
		COORD currentPosition = { 2, HEADER_Y + 2 };
		for (short i = 0; i < PLAYGROUND_SIZE; ++i)
			for (short j = 0; j < PLAYGROUND_SIZE; ++j)
				variations[i * PLAYGROUND_SIZE + j] = { i, j };

		while (gameStatus == NOT_OVER) {
			setCursor({ 0, 1 });
			printf("Round %d: ", roundCounter);
			setCursor({ 0, 2 });
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_ON_WHITE);
			printf("PLAYER MOVE");

			int playerMove = CONTINUE_GAME;
			while (playerMove == CONTINUE_GAME) {
				playerMove = playerShoot(pcPlayground, currentPosition);
				for (int i = 3; i < HEADER_Y; ++i) {
					setCursor({ 0, (short)i });
					printf(EMPTY_STRING);
				}
			}
			if (playerMove == STOP_GAME)
				break;
			gameStatus = isGameOver(playerPlayground, pcPlayground);
			if (playerMove == STOP_GAME)
				break;
			if (gameStatus == NOT_OVER) {
				setCursor({ 0, 2 });
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED_ON_WHITE);
				printf(EMPTY_STRING);
				setCursor({ 0, 2 });
				printf("PC MOVE");
				int pcMove = CONTINUE_GAME;
				while (pcMove == CONTINUE_GAME) {
					pcMove = pcShoot(playerPlayground, variations, varSize, nds);
					for (int i = 3; i < HEADER_Y; ++i) {
						setCursor({ 0, (short)i });
						printf(EMPTY_STRING);
					}
				}
				gameStatus = isGameOver(playerPlayground, pcPlayground);
				if (pcMove == STOP_GAME)
					break;
			}
			++roundCounter;
		}
		printResults(gameStatus, playerPlayground, pcPlayground);
		if (gameStatus != NOT_OVER)
			cleanSavingFiles();
		printf("\tpress any key... ");
		_getch();
		cleanScreen(30);
	}
}
