#pragma execution_character_set("utf-8")
#define  _CRT_SECURE_NO_WARNINGS 

#include "Constants.h"
#include "PlaygroundCreating.h"
#include "Utils.h"

#include <conio.h>
#include <locale.h>  
#include <stdio.h> 
#include <stdlib.h>
#include "Windows.h"


void sortCoordinates(int n, bool orientation, COORD ship[MAX_SIZE_OF_SHIP])
{
	COORD value;
	for (int i = 0; i < n; ++i)
		for (int j = 1; j < n - i; ++j)
		{
			if (orientation == HORIZONTAL)
				if (ship[j].X < ship[j - 1].X) {
					value = ship[j];
					ship[j] = ship[j - 1];
					ship[j - 1] = value;
				}		

			if (orientation == VERTICAL)
				if (ship[j].Y < ship[j - 1].Y) {
					value = ship[j];
					ship[j] = ship[j - 1];
					ship[j - 1] = value;
				}
		}
	}

void createPCPlayground(char (*p)[PLAYGROUND_SIZE])
{

	for (int i = MAX_SIZE_OF_SHIP; i > 0; --i)
	{
		for (int j = 0; j < MAX_SIZE_OF_SHIP + 1 - i; ++j)
			createShip(i, p);
	}
};

void createShip(int n, char (*p)[PLAYGROUND_SIZE])
{
	COORD ship[MAX_SIZE_OF_SHIP];

	do {

		int orientation = rand() % 2;

		if (orientation == VERTICAL)
		{
			ship[0].X = rand() % PLAYGROUND_SIZE;
			ship[0].Y = rand() % (PLAYGROUND_SIZE + 1 - n);
		}
		else if (orientation == HORIZONTAL)
		{
			ship[0].X = rand() % (PLAYGROUND_SIZE + 1 - n);
			ship[0].Y = rand() % (PLAYGROUND_SIZE);
		}

		for (int i = 1; i < n; i++)
		{
			if (orientation == VERTICAL)
			{
				ship[i].X = ship[i - 1].X;
				ship[i].Y = ship[i - 1].Y + 1;
			}
			else if (orientation == HORIZONTAL)
			{
				ship[i].X = ship[i - 1].X + 1;
				ship[i].Y = ship[i - 1].Y;
			}
		}
	} while (!checkoutShip(n, ship, p));

	for (int i = 0; i < n; i++)
	{
		p[ship[i].X][ship[i].Y] = '#';
	}
}

bool checkoutShip(int n, COORD ship[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE])
{
	for (int i = 0; i < n; i++)
	{
		int x = ship[i].X;
		int y = ship[i].Y;
		if (!checkoutBeside(x, y, p))
			return false;
	}
	return true;
}

bool checkoutBeside(int x, int y, char (*p)[PLAYGROUND_SIZE])
{
	char beside[BESIDES_NUMBER] = {};
	int k = 0;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i >= 0 && i < PLAYGROUND_SIZE && j >= 0 && j < PLAYGROUND_SIZE)
			{
				beside[k] = p[i][j];
			}
			if (beside[k] == '#')
			{
				return false;
			}
			k++;
		}
	}
	return true;
}

int inputNewShip(COORD (*ship)[MAX_SIZE_OF_SHIP], COORD &position)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i = 0;
	char c = 0;
	SetConsoleCursorPosition(hStdout, position);
	while (c != 13 && i <= MAX_SIZE_OF_SHIP)
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
			if (position.X < PLAYER_X + 2 + PLAYGROUND_SIZE - 1)
				++position.X;
			else
				position.X -= PLAYGROUND_SIZE - 1;
			SetConsoleCursorPosition(hStdout, position);
			break;
		case 'a':
		case 'A':
			if (position.X > PLAYER_X + 2)
				--position.X;
			else
				position.X += PLAYGROUND_SIZE - 1;
			SetConsoleCursorPosition(hStdout, position);
			break;
		case 32:    // space				
			printf("#");
			(*ship)[i].X = position.X - PLAYER_X - 2;
			(*ship)[i].Y = position.Y - HEADER_Y - 2;
			if (position.X < PLAYER_X + 2 + PLAYGROUND_SIZE - 1)
				++position.X;
			SetConsoleCursorPosition(hStdout, position);
			++i;
			break;
		case 8:    // backspace
			printf(" ");
			(*ship)[i].X = position.X - PLAYER_X - 2;
			(*ship)[i].Y = position.Y - HEADER_Y - 2;
			break;
		}
	}
	return i;
}

bool checkoutPlayerShip(int n, COORD ship[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE])
{
	bool horizontal = true, vertical = true;

	if (n <= 0) 
		return false;

	for (int j = 1; j < n && vertical && horizontal; ++j) {
		if (ship[j].Y != ship[0].Y)
			horizontal = false;
		if (ship[j].X != ship[0].X)
			vertical = false;
	}

	if (horizontal)
	{
		sortCoordinates(n, HORIZONTAL, ship);
		for (int j = 1; j < n; ++j)
			if (ship[j].X - ship[j - 1].X != 1)
				horizontal = false;
	}

	if (vertical)
	{
		sortCoordinates(n, VERTICAL, ship);
		for (int j = 1; j < n; ++j)
			if (ship[j].Y - ship[j - 1].Y != 1)
				vertical = false;
	}

	return (horizontal || vertical);
}

void createPlayerPlayground(char (*p)[PLAYGROUND_SIZE])
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int numberOfShip[] = { 4, 3, 2, 1 };
	COORD ship[MAX_SIZE_OF_SHIP] = {};
	COORD position = { PLAYER_X + 2 , HEADER_Y + 2 };
	printPlayground(p, NEW_PLAYER);
	printInstructions(-1, -1);

	int n = 1;
	bool done = false;
	while (!done) {
		n = inputNewShip(&ship, position);
		
		if (numberOfShip[n - 1] > 0 && checkoutPlayerShip(n, ship, p) && checkoutShip(n, ship, p))
		{
			for (int j = 0; j < n; ++j)
				p[ship[j].X][ship[j].Y] = '#';
			--numberOfShip[n - 1];
			SetConsoleCursorPosition(hStdout, { 0, 0 });
			printf(EMPTY_STRING);
			SetConsoleCursorPosition(hStdout, { 0, 0 });
			printf("Ship (type-%d) was added!", n);
			printInstructions(n - 1, numberOfShip[n - 1]);
		}
		else {
			SetConsoleCursorPosition(hStdout, { 0, 0 });
			printf(EMPTY_STRING);
			SetConsoleCursorPosition(hStdout, { 0, 0 });
			printf("Uncorrect!                ");
			for (int j = 0; j < n; ++j)
			{
				SetConsoleCursorPosition(hStdout, { short(ship[j].X + PLAYER_X + 2), short(ship[j].Y + HEADER_Y + 2) });
				if (p[ship[j].X][ship[j].Y] != '#')
					printf(" ");
			}
		}

		done = true;
		for (int j = 0; j < MAX_SIZE_OF_SHIP; ++j)
			if (numberOfShip[j] != 0)
				done = false;
	}
}


void printInstructions(short type, int n) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int numberOfShip[] = { 4, 3, 2, 1 };
	char typeOfShips[][MAX_SIZE_OF_SHIP + 1] = {"#\0", "##\0", "###", "####"};

	if (type == -1) {
		SetConsoleCursorPosition(hStdout, { 0, HEADER_Y });
		printf("Available ships:\n");
		for (int i = 0; i < MAX_SIZE_OF_SHIP; ++i)
			printf("\t%s - %d\n", typeOfShips[i], numberOfShip[i]);
	}
	else {
		SetConsoleCursorPosition(hStdout, { 0, (short)(HEADER_Y + type + 1)});
		printf("\t%s - %d\n", typeOfShips[type], n);
	}
}
