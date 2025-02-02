#include "Constants.h"

void createPCPlayground(char (*p)[PLAYGROUND_SIZE]);
void createShip(int n, char (*p)[PLAYGROUND_SIZE]);
bool checkoutShip(int n, COORD sheep[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE]);
bool checkoutBeside(int x, int y, char (*p)[PLAYGROUND_SIZE]);

void createPCPlayground(char (*p)[PLAYGROUND_SIZE])
{
	/*рандомное генерирование поля противника*/

	for (int i = MAX_SIZE_OF_SHIP; i > 0; --i)
	{
		for (int j = 0; j < MAX_SIZE_OF_SHIP + 1 - i; ++j)
			createShip(i, p);
	}
};

void createShip(int n, char (*p)[PLAYGROUND_SIZE])
{
	COORD sheep[MAX_SIZE_OF_SHIP];

	do {

		int orientation = rand() % 2;

		if (orientation == VERTICAL)
		{
			sheep[0].X = rand() % PLAYGROUND_SIZE;
			sheep[0].Y = rand() % (PLAYGROUND_SIZE + 1 - n);
		}
		else if (orientation == HORIZONTAL)
		{
			sheep[0].X = rand() % (PLAYGROUND_SIZE + 1 - n);
			sheep[0].Y = rand() % (PLAYGROUND_SIZE);
		}

		for (int i = 1; i < n; i++)
		{
			if (orientation == VERTICAL)
			{
				sheep[i].X = sheep[i - 1].X;
				sheep[i].Y = sheep[i - 1].Y + 1;
			}
			else if (orientation == HORIZONTAL)
			{
				sheep[i].X = sheep[i - 1].X + 1;
				sheep[i].Y = sheep[i - 1].Y;
			}
		}
	} while (!checkoutShip(n, sheep, p));

	for (int i = 0; i < n; i++)
	{
		p[sheep[i].X][sheep[i].Y] = '#';
	}
}


bool checkoutShip(int n, COORD sheep[MAX_SIZE_OF_SHIP], char (*p)[PLAYGROUND_SIZE])
{
	for (int i = 0; i < n; i++)
	{
		int x = sheep[i].X;
		int y = sheep[i].Y;
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

