#pragma execution_character_set("utf-8")
#define  _CRT_SECURE_NO_WARNINGS 

#include "Constants.h"
#include "PlaygroundCreating.h"
#include "Utils.h"

#include <conio.h>
#include <locale.h>  
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
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

int inputNewShip(COORD (*ship)[MAX_SIZE_OF_SHIP])
{
	COORD partOfShip;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	partOfShip.X = PLAYER_X + 2;
	partOfShip.Y = HEADER_Y + 2;
	int i = 0;
	char c = 0;
	SetConsoleCursorPosition(hStdout, partOfShip);
	while (c != 13 && i <= MAX_SIZE_OF_SHIP)
	{
		c = _getch();
		switch (c) {
		case 'w':
		case 'W':
			--partOfShip.Y;
			SetConsoleCursorPosition(hStdout, partOfShip);
			break;
		case 's':
		case 'S':
			++partOfShip.Y;
			SetConsoleCursorPosition(hStdout, partOfShip);
			break;
		case 'd':
		case 'D':
			++partOfShip.X;
			SetConsoleCursorPosition(hStdout, partOfShip);
			break;
		case 'a':
		case 'A':
			--partOfShip.X;
			SetConsoleCursorPosition(hStdout, partOfShip);
			break;
		case 32:    // space				
			printf("#");
			(*ship)[i].X = partOfShip.X - PLAYER_X - 2;
			(*ship)[i].Y = partOfShip.Y - HEADER_Y - 2;
			++partOfShip.X;
			++i;
			break;
		case 8:    // backspace
			printf(" ");
			(*ship)[i].X = partOfShip.X - PLAYER_X - 2;
			(*ship)[i].Y = partOfShip.Y - HEADER_Y - 2;
			break;
		}
	}
	return i;
}

bool checkoutPlayerShip(int n, COORD ship[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE])
{
	bool horizontal = true, vertical = true;

	if (n < 0) 
		return false;

	for (int j = 1; j < n && vertical && horizontal; ++j) {
		if (ship[j].Y != ship[0].Y)
			horizontal = false;
		if (ship[j].X != ship[0].X)
			vertical = false;
	}

	if (horizontal)
	{
		sort(n, HORIZONTAL, ship);
		for (int j = 1; j < n; ++j)
			if (ship[j].X - ship[j - 1].X != 1)
				horizontal = false;
	}

	if (vertical)
	{
		sort(n, VERTICAL, ship);
		for (int j = 1; j < n; ++j)
			if (ship[j].Y - ship[j - 1].Y != 1)
				vertical = false;
	}

	return (horizontal || vertical);
}

void createPlayerPlayground(char (*p)[PLAYGROUND_SIZE])
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int typesOfShip[] = { 4, 3, 2, 1 };
	COORD ship[MAX_SIZE_OF_SHIP];

	printPlayground(p, NEW_PLAYER);

	bool done = false;
	while (!done) {
		int n = inputNewShip(&ship);
		
		if (typesOfShip[n - 1] > 0 && checkoutPlayerShip(n, ship, p) && checkoutShip(n, ship, p))
		{
			for (int j = 0; j < n; ++j)
				p[ship[j].X][ship[j].Y] = '#';
			--typesOfShip[n - 1];
			SetConsoleCursorPosition(hStdout, { 0, 0 });
			printf("Добавлен корабль из %d частей!", n);
		}
		else {
			SetConsoleCursorPosition(hStdout, { 0, 0 });
			printf("Некорректный ввод!             ");
			for (int j = 0; j < n; ++j)
			{
				SetConsoleCursorPosition(hStdout, { short(ship[j].X + PLAYER_X + 2), short(ship[j].Y + HEADER_Y + 2) });
				if (p[ship[j].X][ship[j].Y] != '#')
					printf(" ");
			}
		}

		done = true;
		for (int j = 0; j < MAX_SIZE_OF_SHIP; ++j)
			if (typesOfShip[j] != 0)
				done = false;
	}
}
