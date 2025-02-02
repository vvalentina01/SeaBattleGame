#include "Constants.h"
#include <locale.h>  
#include <stdlib.h>
#include <time.h>

void createPCPlayground(char (*p)[SIZE]);
void createShip(int n, char (*p)[SIZE]);
bool checkoutShip(int n, COORD sheep[MAX_SIZE_OF_SHIP], char (*p)[SIZE]);
bool checkoutBeside(int x, int y, char (*p)[SIZE]);

void createPCPlayground(char (*p)[SIZE])
{
	/*рандомное генерирование поля противника*/

	for (int i = MAX_SIZE_OF_SHIP; i > 0; --i)
	{
		for (int j = 0; j < MAX_SIZE_OF_SHIP + 1 - i; ++j)
			createShip(i, p);
	}
};

void createShip(int n, char (*p)[SIZE])
{
	COORD sheep[MAX_SIZE_OF_SHIP];

	do {

		int orientation = rand() % 2;

		if (orientation == VERTICAL)
		{
			sheep[0].x = rand() % SIZE;
			sheep[0].y = rand() % (SIZE + 1 - n);
		}
		else if (orientation == HORIZONTAL)
		{
			sheep[0].x = rand() % (SIZE + 1 - n);
			sheep[0].y = rand() % (SIZE);
		}

		for (int i = 1; i < n; i++)
		{
			if (orientation == VERTICAL)
			{
				sheep[i].x = sheep[i - 1].x;
				sheep[i].y = sheep[i - 1].y + 1;
			}
			else if (orientation == HORIZONTAL)
			{
				sheep[i].x = sheep[i - 1].x + 1;
				sheep[i].y = sheep[i - 1].y;
			}
		}
	} while (!checkoutShip(n, sheep, p));

	for (int i = 0; i < n; i++)
	{
		p[sheep[i].x][sheep[i].y] = '#';
	}
}


bool checkoutShip(int n, COORD sheep[MAX_SIZE_OF_SHIP], char (*p)[SIZE])
{
	for (int i = 0; i < n; i++)
	{
		int x = sheep[i].x;
		int y = sheep[i].y;
		if (!checkoutBeside(x, y, p))
			return false;
	}
	return true;
}

bool checkoutBeside(int x, int y, char (*p)[SIZE])
{
	char beside[BESIDES_NUMBER] = {};
	int k = 0;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i >= 0 && i < SIZE && j >= 0 && j < SIZE)
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

