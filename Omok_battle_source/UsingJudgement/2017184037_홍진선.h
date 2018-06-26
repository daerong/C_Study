#include <random>
#include <time.h>
int board_2017184037[19][19];

#define BLACK -1
#define WHITE 1

void WhiteAttack_2017184037(int*x, int*y)
{
	srand((unsigned)time(NULL));

	default_random_engine dre;
	dre.seed(rand()+rand());
	uniform_int<> RandomPos(0, 18);

	int xPos = RandomPos(dre);
	int yPos = RandomPos(dre);

	while (1) {
		if (board_2017184037[xPos][yPos] == BLACK || board_2017184037[xPos][yPos] == WHITE) {
			xPos = RandomPos(dre);
			yPos = RandomPos(dre);
		}
		if (board_2017184037[xPos][yPos] != BLACK && board_2017184037[xPos][yPos] != WHITE)
			break;
	}

	*x = xPos;
	*y = yPos;

	board_2017184037[xPos][yPos] = WHITE;

}
void WhiteDefence_2017184037(int x, int y)
{
	//흰돌 1
	//검은돌 -1
	board_2017184037[x][y] = BLACK;
}
void AttackBlack_2017184037(int*x, int*y)
{
	//직접 구현한 돌 놓기 로직을 넣으시면 됩니다.

	srand((unsigned)time(NULL));

	default_random_engine dre;
	dre.seed(rand() + rand());
	uniform_int<> RandomPos(0, 18);


	int xPos = RandomPos(dre);
	int yPos = RandomPos(dre);

	while (1) {
		if (board_2017184037[xPos][yPos] == BLACK || board_2017184037[xPos][yPos] == WHITE) {
			xPos = RandomPos(dre);
			yPos = RandomPos(dre);
		}
		if (board_2017184037[xPos][yPos] != BLACK && board_2017184037[xPos][yPos] != WHITE)
			break;
	}

	*x = xPos;
	*y = yPos;

	board_2017184037[xPos][yPos] = BLACK;

}
void DefenceBlack_2017184037(int x, int y)
{
	//흰돌 1
	//검은돌 -1
	board_2017184037[x][y] = WHITE;
}


