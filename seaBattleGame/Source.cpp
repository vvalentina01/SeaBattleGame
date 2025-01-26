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


const int SIZE = 10;
const char ALPHABET_HEADER[] = "ABCDEFGHIJ";
const int NUMERIC_HEADER[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
const int PLAYER = 1;
const int PC = 0;


/*
void startMenu() {

	printf("***** Welcome to Sea Battle *****");
	printf("\t1 - New Game");
	printf("\t2 - Continue Last Game");
	char isNewGame = getchar();

}*/


void createPCPlayground(FILE* f)
{
	/*рандомное генерирование поля противника*/


};

void readPlayground(char* p, int who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen("C:/study/projects/seaBattle/save/player.txt", "r");
	else
		f = fopen("C:/study/projects/seaBattle/save/pc.txt", "r");

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			fscanf(f, "%c", p + i * SIZE + j);
			if (p[i * SIZE + j] == '\n')
			{
				j--;
			}
		}
	}
	fclose(f);
}

void printPlayground(char* p, int who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen("C:/study/projects/seaBattle/save/player.txt", "r");
	else
		f = fopen("C:/study/projects/seaBattle/save/pc.txt", "r");

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
			printf("%c", p[i * SIZE + j]);
		}
		printf("|\n");
	}
	printf("  ----------");

	fclose(f);
}

void savePlayground(char* p, int who)
{
	FILE* f;

	if (who == PLAYER)
		f = fopen("C:/study/projects/seaBattle/save/player.txt", "w");
	else
		f = fopen("C:/study/projects/seaBattle/save/pc.txt", "w");

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			fprintf(f, "%c", p[i * SIZE + j]);
		}
		fprintf(f, "\n");
	}

	fclose(f);
}


int main()
{
	setlocale(LC_ALL, "Ru");

	//char pcPlayground[SIZE][SIZE];
	char playerPlayground[SIZE * (SIZE + 1)];

	//test

	readPlayground(playerPlayground, PLAYER);
	printPlayground(playerPlayground, PLAYER);
	playerPlayground[1] = 'X'; 
	savePlayground(playerPlayground, PLAYER);

	readPlayground(playerPlayground, PLAYER);
	printPlayground(playerPlayground, PLAYER);

}