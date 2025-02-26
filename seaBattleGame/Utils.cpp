#define  _CRT_SECURE_NO_WARNINGS 

#include "Constants.h"
#include "PlaygroundCreating.h"

#include <locale.h>  
#include <stdio.h> 
#include <stdlib.h>
#include "Windows.h"

bool loadPlayground(char (*p)[PLAYGROUND_SIZE], int who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen(PATH_PLAYER, "r");
	else
		f = fopen(PATH_PC, "r");

	if (f == NULL)
		return false;

	for (int i = 0; i < PLAYGROUND_SIZE; ++i)
	{
		for (int j = 0; j < PLAYGROUND_SIZE; ++j)
		{
			fscanf(f, "%c", &p[i][j]);
		}
	}
	fclose(f);
	return true;
}

void printPlayground(char (*p)[PLAYGROUND_SIZE], int who)
{
	FILE* f;
	COORD position;


	position.Y = HEADER_Y - 2;
	if (who == PLAYER || who == NEW_PLAYER)
	{
		f = fopen(PATH_PLAYER, "r");
		position.X = PLAYER_X;
		setCursor(position);
		printf("\t%s", HEADER_PLAYER);
	}
	else
	{
		f = fopen(PATH_PC, "r");
		position.X = 0;
		setCursor(position);
		printf("%s", HEADER_PC);
	}

	position.Y = HEADER_Y;

	setCursor(position);
	printf("  ");
	printf(ALPHABET_HEADER);
	++position.Y;
	setCursor(position);
	printf("  ----------");
	++position.Y;
	setCursor(position);
	for (int i = 0; i < PLAYGROUND_SIZE; i++)
	{
		printf("%d|", NUMERIC_HEADER[i]);
		for (int j = 0; j < PLAYGROUND_SIZE; j++)
		{
			if (who == NEW_PLAYER || who == PC && p[i][j] == '#')
				printf(" ");
			else
				printf("%c", p[i][j]);

		}
		printf("|");
		++position.Y;
		setCursor(position);
	}
	printf("  ----------");

	if (f != NULL)
		fclose(f);
}

bool savePlayground(char (*p)[PLAYGROUND_SIZE], bool who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen(PATH_PLAYER, "wt");
	else
		f = fopen(PATH_PC, "wt");

	if (f == NULL)
		return false;
	for (int y = 0; y < PLAYGROUND_SIZE; y++)
	{
		for (int x = 0; x < PLAYGROUND_SIZE; x++)
		{
			fprintf(f, "%c", p[x][y]);
		}
	}

	fclose(f);
	return true;
}

void setCursor(COORD position) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdout, position);
}