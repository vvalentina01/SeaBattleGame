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
	/*генерирование пол€ игрока*/
	


};

void readPlayground(char (*p)[PLAYGROUND_SIZE], bool who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen("C:/study/projects/seaBattle 2.0/save/player.txt", "r");
	else
		f = fopen("C:/study/projects/seaBattle 2.0/save/pc.txt", "r");

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

void printPlayground(char (*p)[PLAYGROUND_SIZE], bool who)
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
	for (int i = 0; i < PLAYGROUND_SIZE; i++)
	{
		printf("%d|", NUMERIC_HEADER[i]);
		for (int j = 0; j < PLAYGROUND_SIZE; j++)
		{
			if (who == PC && p[i][j] == '#')
				printf(" ");
			else
				printf("%c", p[i][j]);
		}
		printf("|\n");
	}
	printf("  ----------");

	if (f != NULL)
		fclose(f);
}

void savePlayground(char (*p)[PLAYGROUND_SIZE], bool who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen("C:/study/projects/seaBattle 2.0/save/player.txt", "w");
	else
		f = fopen("C:/study/projects/seaBattle 2.0/save/pc.txt", "w");

	for (int i = 0; i < PLAYGROUND_SIZE; i++)
	{
		for (int j = 0; j < PLAYGROUND_SIZE; j++)
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

	char pcPlayground[PLAYGROUND_SIZE][PLAYGROUND_SIZE];
	char playerPlayground[PLAYGROUND_SIZE][PLAYGROUND_SIZE];
	for (int i = 0; i < PLAYGROUND_SIZE; i++) {
		for (int j = 0; j < PLAYGROUND_SIZE; j++)
		{
			pcPlayground[i][j] = ' ';
		}
	}

	//test
	createPCPlayground(pcPlayground);
	savePlayground(pcPlayground, PC);
	printPlayground(pcPlayground, PC);


}