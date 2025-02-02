// морской бой
// 1. создать свое поле (расставить корабли)
// 1.1.0 создавать прямо на экране поле
// 1.1.1. загрузить из файла (возможно и сохранять в файл)
// 1.2. При создании поля, сразу считать количество "кусков" кораблей
// 2. сама игра
// 2.1. отрисовка поля
// 2.2. ввод куда стрелять.
// 2.2.1. ввод с клавиатуры
// 2.2.2. перемещаешь курсор на позицию в которую хочешь выстрелить и нажимаешь какую-нибудь кнопку (н-р пробел)
// А 1 
//printf("%s\n", field[i]);
//char field[11][12]
// 1234567890 |  1234567890 
//А 		  | А 		  
//B #		  | B #	!	  
//...


#define  _CRT_SECURE_NO_WARNINGS // игнорируем предупреждения о "небезопасных" функциях из Си
#include <stdio.h> //аналог iostream ??
#include <locale.h>  //в случае с++ включен в iostream, не требуется доп. подключение
#include <stdlib.h>
#include <time.h>
#include "Constants.h"
#include "PCPlaygroundCreating.h"


/*
void startMenu() {

	printf("***** Welcome to Sea Battle *****");
	printf("\t1 - New Game");
	printf("\t2 - Continue Last Game");
	char isNewGame = getchar();

}*/



void createPlayerPlayground()
{
	/*генерирование поля игрока*/
	


};

void readPlayground(char (*p)[SIZE], bool who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen("C:/study/projects/seaBattle 2.0/save/player.txt", "r");
	else
		f = fopen("C:/study/projects/seaBattle 2.0/save/pc.txt", "r");

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			fscanf(f, "%c", p[i][j]);
			if (p[i][j] == '\n')
			{
				j--;
			}
		}
	}
	fclose(f);
}

void printPlayground(char (*p)[SIZE], bool who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen("C:/study/projects/seaBattle 2.0/save/player.txt", "r");
	else
		f = fopen("C:/study/projects/seaBattle 2.0/save/pc.txt", "r");

	printf("  ");
	printf(ALPHABET_HEADER);
	printf("\n");
	printf("  ----------");
	printf("\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d|", NUMERIC_HEADER[i]);
		for (int j = 0; j < SIZE; j++)
		{
			printf("%c", p[i][j]);
		}
		printf("|\n");
	}
	printf("  ----------");

	if (f != NULL)
		fclose(f);
}

void savePlayground(char (*p)[SIZE], bool who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen("C:/study/projects/seaBattle 2.0/save/player.txt", "w");
	else
		f = fopen("C:/study/projects/seaBattle 2.0/save/pc.txt", "w");

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			fprintf(f, "%c", p[i][j]);
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

	char pcPlayground[SIZE][SIZE];
	char playerPlayground[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++)
		{
			pcPlayground[i][j] = ' ';
		}
	}

	//test
	createPCPlayground(pcPlayground);
	savePlayground(pcPlayground, PC);
	printPlayground(pcPlayground, PC);



}