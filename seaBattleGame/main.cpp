// морской бой
// 1. создать свое поле (расставить корабли)
// 1.1.0 создавать пр€мо на экране поле
// 1.1.1. загрузить из файла (возможно и сохран€ть в файл)
// 1.2. ѕри создании пол€, сразу считать количество "кусков" кораблей
// 2. сама игра
// 2.1. отрисовка пол€
// 2.2. ввод куда стрел€ть.
// 2.2.1. ввод с клавиатуры
// 2.2.2. перемещаешь курсор на позицию в которую хочешь выстрелить и нажимаешь какую-нибудь кнопку (н-р пробел)
// ј 1 
//printf("%s\n", field[i]);
//char field[11][12]
// 1234567890 |  1234567890 
//ј 		  | ј 		  
//B #		  | B #	!	  
//...



#define  _CRT_SECURE_NO_WARNINGS 
#include <locale.h>  
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "Windows.h"

#include "Constants.h"
#include "PlaygroundCreating.h"



void startMenu() {

	/*printf("***** Welcome to Sea Battle *****");
	printf("\t1 - New Game");
	printf("\t2 - Continue Last Game");
	char isNewGame = getchar();
	*/

}



void readPlayground(char (*p)[PLAYGROUND_SIZE], int who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen(PATH_PLAYER, "r");
	else
		f = fopen(PATH_PC, "r");

	for (int i = 0; i < PLAYGROUND_SIZE; i++)
	{
		for (int j = 0; j < PLAYGROUND_SIZE; j++)
		{
			fscanf(f, "%c", &p[i][j]);
			if (p[i][j] == '\n')
			{
				j--;
			}
		}
	}
	fclose(f);
}

void printPlayground(char (*p)[PLAYGROUND_SIZE], int who)
{
	FILE* f;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD xy;


	xy.Y = HEADER_Y - 2;
	if (who == PLAYER || who == NEW_PLAYER)
	{
		f = fopen(PATH_PLAYER, "r");
		xy.X = PLAYER_X;
		SetConsoleCursorPosition(hStdout, xy);
		printf(HEADER_PLAYER);
	}
	else
	{
		f = fopen(PATH_PC, "r");
		xy.X = 0;
		SetConsoleCursorPosition(hStdout, xy);
		printf(HEADER_PC);
	}

	xy.Y = HEADER_Y;
	
	SetConsoleCursorPosition(hStdout, xy);
	printf("  ");
	printf(ALPHABET_HEADER);
	++xy.Y;
	SetConsoleCursorPosition(hStdout, xy);
	printf("  ----------");
	++xy.Y;
	SetConsoleCursorPosition(hStdout, xy);
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
		++xy.Y;
		SetConsoleCursorPosition(hStdout, xy);
	}
	printf("  ----------");

	if (f != NULL)
		fclose(f);
}

void savePlayground(char (*p)[PLAYGROUND_SIZE], bool who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen(PATH_PLAYER, "wt");
	else
		f = fopen(PATH_PC, "wt");

	for (int y = 0; y < PLAYGROUND_SIZE; y++)
	{
		for (int x = 0; x < PLAYGROUND_SIZE; x++)
		{
			fprintf(f, "%c", p[x][y]);
		}
		fprintf(f, "\n");
	}
	if (f != NULL)
		fclose(f);
}


int main()
{
	setlocale(LC_ALL, "Ru");
	srand(time(NULL));

	char pcPlayground[PLAYGROUND_SIZE][PLAYGROUND_SIZE];
	char playerPlayground[PLAYGROUND_SIZE][PLAYGROUND_SIZE];
	for (int i = 0; i < PLAYGROUND_SIZE; i++) {
		for (int j = 0; j < PLAYGROUND_SIZE; j++)
		{
			pcPlayground[i][j] = ' ';
			playerPlayground[i][j] = ' ';
		}
	}

	printPlayground(pcPlayground, PC);
	createPlayerPlayground(playerPlayground);
	savePlayground(playerPlayground, PLAYER);



	
}
