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
		p[ship[i].Y][ship[i].X] = PART_OF_SHIP;
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
				beside[k] = p[j][i];
			}
			if (beside[k] == PART_OF_SHIP)
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
	
	int i = 0;
	char c = 0;
	setCursor(position);
	while (c != ENTER && i <= MAX_SIZE_OF_SHIP)
	{
		c = inputCoordinates(&position, PLAYER);

		if (c == SPACE)
		{
			printColorSymbol(PART_OF_SHIP);
  			(*ship)[i].X = position.X - PLAYER_X - BORDERS;
			(*ship)[i].Y = position.Y - HEADER_Y - BORDERS;
			if (position.X < PLAYER_X + BORDERS + PLAYGROUND_SIZE - 1)
				++position.X;
			setCursor(position);
			++i;
		}

		if (c == BACKSPACE) {
			printColorSymbol(EMPTY_SPACE);
			(*ship)[i].X = position.X - PLAYER_X - BORDERS;
			(*ship)[i].Y = position.Y - HEADER_Y - BORDERS;
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
	int countOfEveryShipTypes[] = { 4, 3, 2, 1 };
	COORD ship[MAX_SIZE_OF_SHIP] = {};
	COORD position = { PLAYER_X + BORDERS , HEADER_Y + BORDERS };
	printPlayground(p, NEW_PLAYER);
	printInstructions(-1, -1);

	int n = 1;
	bool done = false;
	while (!done) {
		n = inputNewShip(&ship, position);
		
		if (countOfEveryShipTypes[n - 1] > 0 && checkoutPlayerShip(n, ship, p) && checkoutShip(n, ship, p))
		{
			for (int j = 0; j < n; ++j)
				p[ship[j].Y][ship[j].X] = '#';
			--countOfEveryShipTypes[n - 1];
			setCursor({ 0, 0 });
			printf(EMPTY_STRING);
			setCursor({ 0, 0 });
			printf("Ship (type-%d) was added!", n);
			printInstructions(n - 1, countOfEveryShipTypes[n - 1]);
		}
		else {
			setCursor({ 0, 0 });
			printf(EMPTY_STRING);
			setCursor({ 0, 0 });
			printf("Uncorrect!                ");
			for (int j = 0; j < n; ++j)
			{
				setCursor({ short(ship[j].X + PLAYER_X + BORDERS), short(ship[j].Y + HEADER_Y + BORDERS) });
				if (p[ship[j].Y][ship[j].X] != '#')
					printf(" ");
			}
		}

		done = true;
		for (int j = 0; j < MAX_SIZE_OF_SHIP; ++j)
			if (countOfEveryShipTypes[j] != 0)
				done = false;
	}
}


void printInstructions(short type, int n) {
	int countOfEveryShipTypes[] = { 4, 3, 2, 1 };
	char typeOfShips[][MAX_SIZE_OF_SHIP + 1] = {"#", "##", "###", "####"};

	if (type == -1) {
		setCursor({ 0, HEADER_Y });
		printf("Available ships:\n");
		for (int i = 0; i < MAX_SIZE_OF_SHIP; ++i)
			printf("\t%s - %d\n", typeOfShips[i], countOfEveryShipTypes[i]);
	}
	else {
		setCursor({ 0, (short)(HEADER_Y + type + 1)});
		printf("\t%s - %d\n", typeOfShips[type], n);
	}
}
