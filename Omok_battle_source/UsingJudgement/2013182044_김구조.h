#include <random>
int board_2013182044[19][19];


#define BLACK -1
#define WHITE 1
void WhiteAttack_2013182044(int*x, int*y)
{
	//���� ������ �� ���� ������ �����ø� �˴ϴ�.
	default_random_engine dre;
	dre.seed(rand());
	uniform_int<> RandomPos(0, 18);


	int xPos = RandomPos(dre);
	int yPos = RandomPos(dre);


	*x = xPos;
	*y = yPos;

	board_2013182044[yPos][xPos] = WHITE;

}
void WhiteDefence_2013182044(int x, int y)
{
	//�� 1
	//������ -1
	board_2013182044[y][x] = BLACK;
}
void AttackBlack_2013182044(int*x, int*y)
{
	//���� ������ �� ���� ������ �����ø� �˴ϴ�.

	default_random_engine dre;
	dre.seed(rand());
	uniform_int<> RandomPos(0, 18);


	int xPos = RandomPos(dre);
	int yPos = RandomPos(dre);


	*x = xPos;
	*y = yPos;

	board_2013182044[yPos][xPos] = BLACK;

}
void DefenceBlack_2013182044(int x, int y)
{
	//�� 1
	//������ -1
	board_2013182044[y][x] = WHITE;
}


