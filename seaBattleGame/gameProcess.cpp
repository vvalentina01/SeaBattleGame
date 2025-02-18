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
	if (p[position.Y][position.X] == '#') {
		p[position.Y][position.X] = 'x';
		printf("x");
		//реализовать проверку
		return true;
	}
	else {
		p[position.Y][position.X] = 'o';
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
			bool result = shootTrying(p, { (short)(position.X - 2), (short)(position.Y - HEADER_Y - 2) });

			SetConsoleCursorPosition(hStdout, { 0, 3 });
			printf("Player shoots to %c%d\n", ALPHABET_HEADER[position.X - 2], NUMERIC_HEADER[position.Y - HEADER_Y - 2]);
			printf("Result: ");
			if (result) {
				printf("hit\n");
				if (isShipDestroyed({ (short)(position.X - 2), (short)(position.Y - HEADER_Y - 2) }, p, PC))
					printf("Ship is destroyed!\n");
				else
					printf("Ship is not destroyed yet!\n");
			}
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
	for (int i = 0; i < PLAYGROUND_SIZE; ++i) {
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

	if (p[position.Y][position.X] == ' ') {
		p[position.Y][position.X] = 'o';
		printf("o");
		result = 0;
	}

	if (p[position.Y][position.X] == '#') {
		p[position.Y][position.X] = 'x';
		printf("x");
		result = 1;
	}

	SetConsoleCursorPosition(hStdout, { 0, 3 });
	printf("Enemy shoots to %c%d\n", ALPHABET_HEADER[position.X], NUMERIC_HEADER[position.Y]);
	printf("Result: ");
	if (result) {
		printf("hit\n");
		if (isShipDestroyed(position, p, PLAYER))
			printf("Ship is destroyed!\n");
		else
			printf("Ship is not destroyed yet!\n");
	}
	else
		printf("miss\n");
	printf("\tto continue press any key... ");
	_getch();
	return result;
}

bool isShipDestroyed(COORD position, char (*p)[PLAYGROUND_SIZE], int who) {

	bool orientation;
	bool onlyOne = 1;
	
	if (position.Y > 0)
		if (p[position.Y - 1][position.X] == '#' || p[position.Y - 1][position.X] == 'x')
			orientation = VERTICAL, onlyOne = 0;

	if (position.Y < PLAYGROUND_SIZE)
		if (p[position.Y + 1][position.X] == '#' || p[position.Y + 1][position.X] == 'x')
			orientation = VERTICAL, onlyOne = 0;

	if (position.X > 0)
		if (p[position.Y][position.X - 1] == '#' || p[position.Y ][position.X - 1] == 'x')
			orientation = HORIZONTAL, onlyOne = 0;

	if (position.X < PLAYGROUND_SIZE)
		if (p[position.Y][position.X + 1] == '#' || p[position.Y ][position.X + 1] == 'x')
			orientation = HORIZONTAL, onlyOne = 0;

	if (onlyOne)
		return true;

	COORD ship[MAX_SIZE_OF_SHIP];
	int shipSize = 1;
	ship[0] = position;
	
	if (orientation == HORIZONTAL) {

		for (int i = 1; position.X < PLAYGROUND_SIZE && shipSize < MAX_SIZE_OF_SHIP &&
			p[position.Y][position.X + i] != ' ' && p[position.Y][position.X + i] != 'o'; i++)
		{
			ship[shipSize] = { (short)(position.X + i), position.Y };
			++shipSize;
		}

		for (int i = 1; position.X > 0 && shipSize < MAX_SIZE_OF_SHIP &&
			p[position.Y][position.X - i] != ' ' && p[position.Y][position.X - i] != 'o'; i++)
		{
			ship[shipSize] = { (short)(position.X - i), position.Y };
			++shipSize;
		}
	}

	if (orientation == VERTICAL) {

		for (int i = 1; position.Y < PLAYGROUND_SIZE && shipSize < MAX_SIZE_OF_SHIP && 
			p[position.Y + i][position.X] != ' ' && p[position.Y + i][position.X] != 'o'; i++)
		{
			ship[shipSize] = { position.X, (short)(position.Y + i) };
			++shipSize;
		}

		for (int i = 1; position.Y > 0 && shipSize < MAX_SIZE_OF_SHIP && 
			p[position.Y - i][position.X] != ' ' && p[position.Y - i][position.X] != 'o'; i++)
		{
			ship[shipSize] = { position.X, (short)(position.Y - i) };
			++shipSize;
		}
	}

	for (int i = 0; i < shipSize; ++i)
		if (p[ship[i].Y][ship[i].X] == '#')
			return false;

	markAroundAsEmpty(shipSize, orientation, ship, p, who);
	return true;

}

void markAroundAsEmpty(int n, bool orientation, COORD ship[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE], int who)
{
	sortCoordinates(n, orientation, ship);
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int indent = 0;
	if (who == PLAYER)
		indent = PLAYER_X;

	if (orientation == HORIZONTAL) {
		int xStart = 0, xFinish = ship[0].X + n;

		if (ship[0].X > 0) {
			p[ship[0].Y][ship[0].X - 1] = 'o';
			SetConsoleCursorPosition(hStdout, { (short)(ship[0].X - 1 + indent + 2),  (short)(ship[0].Y + HEADER_Y + 2) });
			printf("o");
			--xStart;
		}

		if (ship[n - 1].X < PLAYGROUND_SIZE) {
			p[ship[n - 1].Y][ship[n - 1].X + 1] = 'o';
			SetConsoleCursorPosition(hStdout, { (short)(ship[n - 1].X + 1 + indent + 2), (short)(ship[n - 1].Y + HEADER_Y + 2) });
			printf("o");
			++xFinish;
		}

		if (ship[0].Y > 0)
			for (int i = ship[0].X + xStart; i < xFinish; ++i) {
				p[ship[0].Y - 1][i] = 'o';
				SetConsoleCursorPosition(hStdout, { (short)(i + indent + 2), (short)(ship[0].Y - 1 + HEADER_Y + 2) });
				printf("o");
			}

		if (ship[0].Y < PLAYGROUND_SIZE)
			for (int i = ship[0].X + xStart; i < xFinish; ++i) {
				p[ship[0].Y + 1][i] = 'o';
				SetConsoleCursorPosition(hStdout, { (short)(i + indent + 2) , (short)(ship[0].Y + 1 + HEADER_Y + 2) });
				printf("o");
			}
	}

	if (orientation == VERTICAL) {

		int yStart = 0, yFinish = ship[0].Y + n;

		if (ship[0].Y > 0) {
			p[ship[0].Y - 1][ship[0].X] = 'o';
			SetConsoleCursorPosition(hStdout, { (short)(ship[0].X + indent + 2),  (short)(ship[0].Y - 1 + HEADER_Y + 2) });
			printf("o");
			--yStart;
		}

		if (ship[n - 1].Y < PLAYGROUND_SIZE) {
			p[ship[n - 1].Y + 1][ship[n - 1].X] = 'o';
			SetConsoleCursorPosition(hStdout, { (short)(ship[n - 1].X + indent + 2), (short)(ship[n - 1].Y + 1 + HEADER_Y + 2) });
			printf("o");
			++yFinish;
		}

		if (ship[0].X > 0)
			for (int i = ship[0].Y + yStart; i < yFinish; ++i) {
				p[i][ship[0].X - 1] = 'o';
				SetConsoleCursorPosition(hStdout, { (short)(ship[0].X - 1 + indent + 2), (short)(i + HEADER_Y + 2) });
				printf("o");
			}

		if (ship[0].X < PLAYGROUND_SIZE)
			for (int i = ship[0].Y + yStart; i < yFinish; ++i) {
				p[i][ship[0].X + 1] = 'o';
				SetConsoleCursorPosition(hStdout, { (short)(ship[0].X + 1 + indent + 2) , (short)(i + HEADER_Y + 2) });
				printf("o");
			}
	}

	SetConsoleCursorPosition(hStdout, { 0, 5 });

	SetConsoleCursorPosition(hStdout, { 0, 5 });

}