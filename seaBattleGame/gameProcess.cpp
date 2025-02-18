#define  _CRT_SECURE_NO_WARNINGS 
#pragma execution_character_set("utf-8")

#include "Constants.h"
#include "gameProcess.h"
#include "PlaygroundCreating.h"

#include <conio.h>
#include <locale.h>  
#include <stdio.h> 
#include <stdlib.h>
#include "Windows.h"

bool shootTrying(char (*p)[PLAYGROUND_SIZE], COORD position)
{
	if (p[position.Y - HEADER_Y - 2][position.X - 2] == '#') {
		p[position.Y - HEADER_Y - 2][position.X - 2] = 'x';
		printf("x");
		//реализовать проверку
		return true;
	}
	else {
		p[position.Y - HEADER_Y - 2][position.X - 2] = 'o';
		printf("o");
		return false;
	}
}

bool playerShoot(char (*p)[PLAYGROUND_SIZE]) {

	COORD position;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = 2;
	position.Y = HEADER_Y + 2;

	char c = 0;
	SetConsoleCursorPosition(hStdout, position);
	do
	{
		c = _getch();
		switch (c) {
		case 'w':
		case 'W':
			if (position.Y > HEADER_Y + 2)
				--position.Y;
			else
				position.Y += PLAYGROUND_SIZE - 1;
			SetConsoleCursorPosition(hStdout, position);
			break;
		case 's':
		case 'S':
			if (position.Y < HEADER_Y + 2 + PLAYGROUND_SIZE - 1)
				++position.Y;
			else
				position.Y -= PLAYGROUND_SIZE - 1;
			SetConsoleCursorPosition(hStdout, position);
			break;
		case 'd':
		case 'D':
			if (position.X < 2 + PLAYGROUND_SIZE - 1)
				++position.X;
			else
				position.X -= PLAYGROUND_SIZE - 1;
			SetConsoleCursorPosition(hStdout, position);
			break;
		case 'a':
		case 'A':
			if (position.X > 2)
				--position.X;
			else
				position.X += PLAYGROUND_SIZE - 1;
			SetConsoleCursorPosition(hStdout, position);
			break;
		case 32:    // space
			bool result = shootTrying(p, position);

			SetConsoleCursorPosition(hStdout, { 0, 3 });
			printf("Player shoots to %c%d\n", ALPHABET_HEADER[position.X - 2], NUMERIC_HEADER[position.Y - HEADER_Y - 2]);
			printf("Result: ");
			if (result)
				printf("hit\n");
			else
				printf("miss\n");
			printf("\tto continue press any key... ");
			_getch();

			return result;

			
			break;
		}
	}
	while (c != 32);
}

int isGameOver(char (*player)[PLAYGROUND_SIZE], char (*pc)[PLAYGROUND_SIZE]) {
	bool playerIsLoser = 1;
	bool pcIsLoser = 1;
	for (int i = 0; i < PLAYGROUND_SIZE && playerIsLoser && pcIsLoser; ++i) {
		for (int j = 0; j < PLAYGROUND_SIZE; ++j) {
			if (player[i][j] == '#')
				playerIsLoser = 0;
			if (pc[i][j] == '#')
				pcIsLoser = 0;
		}
	}

	if (playerIsLoser)
		return LOSE;

	if (pcIsLoser)
		return WIN;

	return NOT_OVER;
}

bool pcShoot(char (*p)[PLAYGROUND_SIZE]) {

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	bool result = 0;

	do {
		position.X = rand() % PLAYGROUND_SIZE;
		position.Y = rand() % PLAYGROUND_SIZE;
	} while (p[position.X][position.Y] == 'o');

	SetConsoleCursorPosition(hStdout, { (short)(position.X + PLAYER_X + 2), (short)(position.Y + HEADER_Y + 2) });

	if (p[position.X][position.Y] == ' ') {
		p[position.X][position.Y] == 'o';
		printf("o");
		result = 0;
	}

	if (p[position.X][position.Y] == '#') {
		p[position.X][position.Y] == 'x';
		printf("x");
		result = 1;
	}

	SetConsoleCursorPosition(hStdout, { 0, 3 });
	printf("Enemy shoots to %c%d\n", ALPHABET_HEADER[position.X], NUMERIC_HEADER[position.Y]);
	printf("Result: ");
	if (result)
		printf("hit\n");
	else
		printf("miss\n");
	printf("\tto continue press any key... ");
	_getch();
	return result;
}