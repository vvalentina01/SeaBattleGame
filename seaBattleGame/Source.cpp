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


#define  _CRT_SECURE_NO_WARNINGS // игнорируем предупреждени€ о "небезопасных" функци€х из —и
#include <stdio.h> //аналог iostream ??
#include <locale.h>  //в случае с++ включен в iostream, не требуетс€ доп. подключение
#include <stdlib.h>
#include <time.h>


const int SIZE = 10;
const char ALPHABET_HEADER[] = "ABCDEFGHIJ";
const int NUMERIC_HEADER[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
const bool PC = 0;
const bool PLAYER = 1;
const bool HORIZONTAL = 0;
const bool VERTICAL = 1;



/*
void startMenu() {

	printf("***** Welcome to Sea Battle *****");
	printf("\t1 - New Game");
	printf("\t2 - Continue Last Game");
	char isNewGame = getchar();

}*/

bool checkoutShip(int n, int xy[4][2], char (*p)[SIZE]);
bool checkoutBeside(int x, int y, char (*p)[SIZE]);

void createShip(int n, char (*p)[SIZE])
{
	int xy[4][2];

	do {
		srand(time(NULL) + n);
		int orientation = rand() % 2;

		if (orientation == VERTICAL)
		{
			xy[0][0] = rand() % SIZE;
			xy[0][1] = rand() % (SIZE + 1 - n);
		}
		else if (orientation == HORIZONTAL)
		{
			xy[0][0] = rand() % (SIZE + 1 - n);
			xy[0][1] = rand() % (SIZE);
		}

		for (int i = 1; i < n; i++)
		{
			if (orientation == VERTICAL)
			{
				xy[i][0] = xy[i - 1][0];
				xy[i][1] = xy[i - 1][1] + 1;
			}
			else if (orientation == HORIZONTAL)
			{
				xy[i][0] = xy[i - 1][0] + 1;
				xy[i][1] = xy[i - 1][1];
			}
		}
	}
	while (!checkoutShip(n, xy, p));
	
	for (int i = 0; i < n; i++)
	{
		p[xy[i][0]][xy[i][1]] = '#';
	}
}

bool checkoutBeside(int x, int y, char (*p)[SIZE])
{
	char beside[9] = {};
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


bool checkoutShip(int n, int xy[4][2], char (*p)[SIZE])
{
	for (int i = 0; i < n; i++)
	{
		int x = xy[i][0];
		int y = xy[i][1];
		if (!checkoutBeside(x, y, p))
			return false;
	}
	return true;
}


void createPCPlayground(char (*p)[SIZE])
{
	/*рандомное генерирование пол€ противника*/
	
	createShip(4, p);
	createShip(3, p);
	createShip(3, p);
	createShip(2, p);
	createShip(2, p);
	createShip(2, p);
	createShip(1, p);
	createShip(1, p);
	createShip(1, p);
	createShip(1, p);
};

void createPlayerPlayground()
{
	/*генерирование пол€ игрока*/
	


};

void readPlayground(char (*p)[SIZE], bool who)
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
			printf("%c", p[i][j]);
		}
		printf("|\n");
	}
	printf("  ----------");

	fclose(f);
}

void savePlayground(char (*p)[SIZE], bool who)
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
			fprintf(f, "%c", p[i][j]);
		}
		fprintf(f, "\n");
	}

	fclose(f);
}


int main()
{
	setlocale(LC_ALL, "Ru");

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