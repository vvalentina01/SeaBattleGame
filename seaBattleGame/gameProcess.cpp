#define  _CRT_SECURE_NO_WARNINGS 
#pragma execution_character_set("utf-8")

#include "Constants.h"
#include "gameProcess.h"
#include "PlaygroundCreating.h"
#include "Utils.h"

#include <conio.h>
#include <locale.h>  
#include <stdio.h> 
#include <stdlib.h>
#include "Windows.h"


bool shootTrying(char (*p)[PLAYGROUND_SIZE], COORD position)
{
	if (p[position.Y][position.X] == PART_OF_SHIP) {
		p[position.Y][position.X] = HIT;
		printColorSymbol(HIT);
		return true;
	}
	else {
		p[position.Y][position.X] = MISS;
		printColorSymbol(MISS);
		return false;
	}
}

int playerShoot(char (*p)[PLAYGROUND_SIZE], COORD& position) {
	char c = 0;
	setCursor(position);
	do
	{
		c = inputCoordinates(&position, PC);
		if (c == SPACE && p[position.Y - HEADER_Y - BORDERS][position.X - BORDERS] != HIT
			&& p[position.Y - HEADER_Y - BORDERS][position.X - BORDERS] != MISS) {
			bool result = shootTrying(p, { (short)(position.X - BORDERS), (short)(position.Y - HEADER_Y - BORDERS) });
			if (!resultOfMove(result, { (short)(position.X - BORDERS), (short)(position.Y - HEADER_Y - BORDERS) }, PLAYER, p))
				return STOP_GAME;
			return result;
		}
		else c = 0;
	}
	while (c != SPACE);
}

int isGameOver(char (*player)[PLAYGROUND_SIZE], char (*pc)[PLAYGROUND_SIZE]) {
	bool playerIsLoser = 1;
	bool pcIsLoser = 1;
	for (int i = 0; i < PLAYGROUND_SIZE; ++i) {
		for (int j = 0; j < PLAYGROUND_SIZE; ++j) {
			if (player[i][j] == PART_OF_SHIP)
				playerIsLoser = 0;
			if (pc[i][j] == PART_OF_SHIP)
				pcIsLoser = 0;
		}
	}
	if (playerIsLoser)
		return LOSE;
	if (pcIsLoser)
		return WIN;
	return NOT_OVER;
}

int pcShoot(char (*p)[PLAYGROUND_SIZE], COORD* variations, int& varSize, notDestroyedShip& nds) {

	COORD position;
	bool result = 0;
		if (nds.exists)
		{
			position = nds.nextMove;
		}
		else {
			int r = 0;
			do {
				if (nds.exists) {
					r = rand() % nds.varCount;
				}
				else
					r = rand() % varSize;
				position = variations[r];
			} while (p[position.Y][position.X] == MISS || p[position.Y][position.X] == HIT);
			variations[r] = variations[varSize - 1];
			--varSize;
		}

	setCursor({ (short)(position.X + PLAYER_X + BORDERS), (short)(position.Y + HEADER_Y + BORDERS) });

	if (p[position.Y][position.X] == EMPTY_SPACE) {
		p[position.Y][position.X] = MISS;
		printColorSymbol(MISS);
		result = 0;
	}
	if (p[position.Y][position.X] == PART_OF_SHIP) {
		p[position.Y][position.X] = HIT;
		printColorSymbol(HIT);
		result = 1;
	}

	if (!resultOfMove(result, position, PC, p))
		return STOP_GAME;
	bool shipStatus = false;
	if (result)
		shipStatus = isShipDestroyed(position, p, PC);
	strategyPC(position, result, shipStatus, p, nds);
	return result;
}

bool isShipDestroyed(COORD position, char (*p)[PLAYGROUND_SIZE], int who) {

	bool orientation = HORIZONTAL;
	bool onlyOne = 1;

	if (position.Y > 0)
		if (p[position.Y - 1][position.X] == PART_OF_SHIP || p[position.Y - 1][position.X] == HIT)
			orientation = VERTICAL, onlyOne = 0;

	if (position.Y + 1 < PLAYGROUND_SIZE)
		if (p[position.Y + 1][position.X] == PART_OF_SHIP || p[position.Y + 1][position.X] == HIT)
			orientation = VERTICAL, onlyOne = 0;

	if (position.X > 0)
		if (p[position.Y][position.X - 1] == PART_OF_SHIP || p[position.Y][position.X - 1] == HIT)
			orientation = HORIZONTAL, onlyOne = 0;

	if (position.X + 1 < PLAYGROUND_SIZE)
		if (p[position.Y][position.X + 1] == PART_OF_SHIP || p[position.Y][position.X + 1] == HIT)
			orientation = HORIZONTAL, onlyOne = 0;

	COORD ship[MAX_SIZE_OF_SHIP];
	int shipSize = 1;
	ship[0] = position;

	if (!onlyOne) {
		if (orientation == HORIZONTAL) {
			for (int i = 1; position.X + 1 < PLAYGROUND_SIZE && shipSize < MAX_SIZE_OF_SHIP &&
				p[position.Y][position.X + i] != EMPTY_SPACE && p[position.Y][position.X + i] != MISS; i++)
			{
				ship[shipSize] = { (short)(position.X + i), position.Y };
				++shipSize;
			}
			for (int i = 1; position.X > 0 && shipSize < MAX_SIZE_OF_SHIP &&
				p[position.Y][position.X - i] != EMPTY_SPACE && p[position.Y][position.X - i] != MISS; i++)
			{
				ship[shipSize] = { (short)(position.X - i), position.Y };
				++shipSize;
			}
		}
		if (orientation == VERTICAL) {

			for (int i = 1; position.Y + 1 < PLAYGROUND_SIZE && shipSize < MAX_SIZE_OF_SHIP &&
				p[position.Y + i][position.X] != EMPTY_SPACE && p[position.Y + i][position.X] != MISS; i++)
			{
				ship[shipSize] = { position.X, (short)(position.Y + i) };
				++shipSize;
			}
			for (int i = 1; position.Y > 0 && shipSize < MAX_SIZE_OF_SHIP &&
				p[position.Y - i][position.X] != EMPTY_SPACE && p[position.Y - i][position.X] != MISS; i++)
			{
				ship[shipSize] = { position.X, (short)(position.Y - i) };
				++shipSize;
			}
		}
		for (int i = 0; i < shipSize; ++i)
			if (p[ship[i].Y][ship[i].X] == PART_OF_SHIP)
				return false;
	}
	markAroundAsEmpty(shipSize, orientation, ship, p, who);
	return true;
}

void markAroundAsEmpty(int shipSize, bool orientation, COORD ship[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE], int who)
{
	if (shipSize > 1)
		sortCoordinates(shipSize, orientation, ship);
	int indent = 0;

	if (who == PC)
		indent = PLAYER_X;

	if (orientation == HORIZONTAL) {
		int xStart = 0, xFinish = ship[0].X + shipSize;
		if (ship[0].X > 0) {
			p[ship[0].Y][ship[0].X - 1] = MISS;
			setCursor({ (short)(ship[0].X - 1 + indent + BORDERS),  (short)(ship[0].Y + HEADER_Y + BORDERS) });
			printColorSymbol(MISS);
			--xStart;
		}
		if (ship[shipSize - 1].X + 1 < PLAYGROUND_SIZE) {
			p[ship[shipSize - 1].Y][ship[shipSize - 1].X + 1] = MISS;
			setCursor({ (short)(ship[shipSize - 1].X + 1 + indent + BORDERS), (short)(ship[shipSize - 1].Y + HEADER_Y + BORDERS) });
			printColorSymbol(MISS);
			++xFinish;
		}

		if (ship[0].Y > 0)
			for (int i = ship[0].X + xStart; i < xFinish; ++i) {
				if (i >= 0 && i < PLAYGROUND_SIZE) {
					p[ship[0].Y - 1][i] = MISS;
					setCursor({ (short)(i + indent + BORDERS), (short)(ship[0].Y - 1 + HEADER_Y + BORDERS) });
					printColorSymbol(MISS);
				}
			}
		if (ship[0].Y + 1 < PLAYGROUND_SIZE)
			for (int i = ship[0].X + xStart; i < xFinish; ++i) {
				if (i >= 0 && i < PLAYGROUND_SIZE) {
					p[ship[0].Y + 1][i] = MISS;
					setCursor({ (short)(i + indent + BORDERS) , (short)(ship[0].Y + 1 + HEADER_Y + BORDERS) });
					printColorSymbol(MISS);
				}
			}
	}

	if (orientation == VERTICAL) {
		int yStart = 0, yFinish = ship[0].Y + shipSize;
		if (ship[0].Y > 0) {
			p[ship[0].Y - 1][ship[0].X] = MISS;
			setCursor({ (short)(ship[0].X + indent + BORDERS),  (short)(ship[0].Y - 1 + HEADER_Y + BORDERS) });
			printColorSymbol(MISS);
			--yStart;
		}
		if (ship[shipSize - 1].Y + 1 < PLAYGROUND_SIZE) {
			p[ship[shipSize - 1].Y + 1][ship[shipSize - 1].X] = MISS;
			setCursor({ (short)(ship[shipSize - 1].X + indent + BORDERS), (short)(ship[shipSize - 1].Y + 1 + HEADER_Y + BORDERS) });
			printColorSymbol(MISS);
			++yFinish;
		}

		if (ship[0].X > 0)
			for (int i = ship[0].Y + yStart; i < yFinish; ++i) {
				if (i >= 0 && i < PLAYGROUND_SIZE) {
					p[i][ship[0].X - 1] = MISS;
					setCursor({ (short)(ship[0].X - 1 + indent + BORDERS), (short)(i + HEADER_Y + BORDERS) });
					printColorSymbol(MISS);
				}
			}
		if (ship[0].X + 1 < PLAYGROUND_SIZE)
			for (int i = ship[0].Y + yStart; i < yFinish; ++i) {
				if (i >= 0 && i < PLAYGROUND_SIZE) {
					p[i][ship[0].X + 1] = MISS;
					setCursor({ (short)(ship[0].X + 1 + indent + BORDERS) , (short)(i + HEADER_Y + BORDERS) });
					printColorSymbol(MISS);
				}
			}
	}
	setCursor({ 0, 5 });
}

bool resultOfMove(bool result, COORD position, int who, char (*p)[PLAYGROUND_SIZE]) {
	int indentX = 0, indentY = 0;
	setCursor({ 0, 3 });
	if (who == PLAYER) 
		printf("Player ");
	else
		printf("Enemy ");
	printf("shoots to %c%d\n", ALPHABET_HEADER[position.X], NUMERIC_HEADER[position.Y]);
	printf("Result: ");
	if (result) {
		printf("hit\n");
		if (isShipDestroyed(position, p, who))
			printf("Ship is destroyed!\n");
		else
			printf("Ship is not destroyed yet!\n");
	}
	else
		printf("miss\n");
	printf("\tto exit game press ESC...\n");
	printf("\tto continue press any key... ");
	if (_getch() == ESCAPE)
		return false;
	return true;
}

bool strategyPC(COORD position, bool result, bool shipStatus, char (*p)[PLAYGROUND_SIZE], notDestroyedShip& nds)
{
	if (!result && !nds.exists) {
		return false;
	}

	if (!result && nds.exists) {
		for (int i = 0; i < nds.varCount; ++i) {
			if (nds.variations[i].X == position.X && nds.variations[i].Y == position.Y) {
				nds.variations[i] = nds.variations[nds.varCount - 1];
				--nds.varCount;
			}
		}
		if (nds.varCount == 1)
			nds.nextMove = nds.variations[0];
		else
			do
				nds.nextMove = nds.variations[rand() % nds.varCount];
			while (p[nds.nextMove.Y][nds.nextMove.X] == MISS || p[nds.nextMove.Y][nds.nextMove.X] == HIT);
		return true;
	}

	if (result && shipStatus) {
		if (nds.exists) {
			nds.exists = false;
			nds.shipSize = 1;
			nds.varCount = 0;
		}
		return false;
	}

	if (result && !shipStatus)
	{
		if (!nds.exists)
			nds.shipSize = 1;
		nds.ship[nds.shipSize - 1] = position;
		++nds.shipSize;

		if (!nds.exists) {
			nds.exists = true;
			nds.varCount = 0;
			if (position.Y + 1 <= PLAYGROUND_SIZE) {
				nds.variations[nds.varCount] = { position.X, (short)(position.Y + 1) };
				++nds.varCount;
			}
			if (position.Y - 1 >= 0) {
				nds.variations[nds.varCount] = { position.X, (short)(position.Y - 1) };
				++nds.varCount;
			}
			if (position.X + 1 <= PLAYGROUND_SIZE) {
				nds.variations[nds.varCount] = { (short)(position.X + 1), position.Y };
				++nds.varCount;
			}
			if (position.X - 1 >= 0) {
				nds.variations[nds.varCount] = { (short)(position.X - 1), position.Y };
				++nds.varCount;
			}
			do 
				nds.nextMove = nds.variations[rand() % nds.varCount];
			while (p[nds.nextMove.Y][nds.nextMove.X] == MISS || p[nds.nextMove.Y][nds.nextMove.X] == HIT);
		}
		else {
			if (nds.ship[0].Y == nds.ship[1].Y)
				nds.orientation = HORIZONTAL;
			else
				nds.orientation = VERTICAL;

			sortCoordinates(nds.shipSize - 1, nds.orientation, nds.ship);
			nds.varCount = 0;
			int first = 0;
			int last = nds.shipSize - 2;
			if (nds.orientation == HORIZONTAL) {
				if (nds.ship[first].X - 1 >= 0 && p[nds.ship[first].Y][nds.ship[first].X - 1] != HIT
						&& p[nds.ship[first].Y][nds.ship[first].X - 1] != MISS) {
					nds.variations[nds.varCount] = { (short)(nds.ship[first].X - 1), nds.ship[first].Y };
					++nds.varCount;
				}
				if (nds.ship[last].X + 1 <= PLAYGROUND_SIZE && p[nds.ship[last].Y][nds.ship[last].X + 1] != HIT
						&& p[nds.ship[last].Y][nds.ship[last].X + 1] != MISS) {
					nds.variations[nds.varCount] = { (short)(nds.ship[last].X + 1), nds.ship[last].Y };
					++nds.varCount;
				}
			}
			if (nds.orientation == VERTICAL) {
				if (nds.ship[first].Y - 1 >= 0 && p[nds.ship[first].Y - 1][nds.ship[first].X] != HIT
						&& p[nds.ship[first].Y - 1][nds.ship[first].X] != MISS) {
					nds.variations[nds.varCount] = { nds.ship[first].X, (short)(nds.ship[first].Y - 1) };
					++nds.varCount;
				}
				if (nds.ship[last].Y + 1 <= PLAYGROUND_SIZE && p[nds.ship[last].Y + 1][nds.ship[last].X] != HIT
						&& p[nds.ship[last].Y + 1][nds.ship[last].X] != MISS) {
					nds.variations[nds.varCount] = { nds.ship[last].X, (short)(nds.ship[last].Y + 1) };
					++nds.varCount;
				}
			}
			if (nds.varCount == 1)
				nds.nextMove = nds.variations[0];
			else {
				nds.nextMove = nds.variations[rand() % 2];
			}
		}
	}
	return true;
}
