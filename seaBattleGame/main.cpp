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


#pragma execution_character_set("utf-8")
#define  _CRT_SECURE_NO_WARNINGS 

#include "Constants.h"
#include "PlaygroundCreating.h"
#include "Utils.h"

#include <locale.h>  
#include <time.h>
#include "Windows.h"




void startMenu() {

	/*printf("***** Welcome to Sea Battle *****");
	printf("\t1 - New Game");
	printf("\t2 - Continue Last Game");
	char isNewGame = getchar();
	*/

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
