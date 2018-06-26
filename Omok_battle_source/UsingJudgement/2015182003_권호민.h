#include <random>
#include <time.h>


bool isFirst = false;

int board_2015182003[19][19];
int xPos_2015182003 = rand() % 3 + 8;
int yPos_2015182003 = rand() % 3 + 8;
int count_2015182003 = 0;
int count2_2015182003 = 0;

#define BLACK -1
#define WHITE 1

void WhiteAttack_2015182003(int*x, int*y)
{
	srand((unsigned)time(NULL));
	bool breaking = false;
	bool breaking2 = false;
	//직접 구현한 돌 놓기 로직을 넣으시면 됩니다.

	xPos_2015182003++;
	yPos_2015182003++;

	if (board_2015182003[yPos_2015182003][xPos_2015182003] != 0)
	{
		while (board_2015182003[yPos_2015182003][xPos_2015182003] != 0)
		{
			xPos_2015182003--;
			yPos_2015182003--;
		}
	}

	for (int j = 0; j < 19; j++)
	{
		for (int i = 0; i < 19; i++)
		{
			if (board_2015182003[j][i] == BLACK)
			{
				if (board_2015182003[j][i + 1] == BLACK
					&& board_2015182003[j][i + 2] == BLACK
					&& board_2015182003[j][i + 3] == 0)
				{
					if (i == 0)
					{
						breaking = true;
						break;
					}
					if (board_2015182003[j][i - 1] == WHITE)
					{
						breaking = true;
						break;
					}
					if (board_2015182003[j][i - 1] == 0)
					{
						xPos_2015182003 = i - 1;
						yPos_2015182003 = j;
						breaking = true;
						break;
					}
					else
					{

					}
				}

				if (board_2015182003[j][i + 1] == BLACK
					&& board_2015182003[j][i + 2] == BLACK
					&& board_2015182003[j][i + 3] == BLACK)
				{
					if (i == 0)
					{
						breaking = true;
						break;
					}
					if (board_2015182003[j][i - 1] == WHITE && board_2015182003[j][i + 4] == 0)
					{
						xPos_2015182003 = i + 4;
						yPos_2015182003 = j;
						breaking = true;
						break;
					}
					if (board_2015182003[j][i - 1] == 0 && board_2015182003[j][i + 4] == WHITE)
					{
						xPos_2015182003 = i - 1;
						yPos_2015182003 = j;
						breaking = true;
						break;
					}
					else
					{

					}

				}

				if (board_2015182003[j + 1][i] == BLACK
					&& board_2015182003[j + 2][i] == BLACK
					&& board_2015182003[j + 3][i] == 0)
				{
					if (j == 0)
					{
						breaking = true;
						break;
					}
					if (board_2015182003[j - 1][i] == WHITE)
					{
						breaking = true;
						break;
					}
					else if (board_2015182003[j - 1][i] == 0)
					{
						xPos_2015182003 = i;
						yPos_2015182003 = j - 1;
						breaking = true;
						break;
					}
				}

				if (board_2015182003[j + 1][i] == BLACK
					&& board_2015182003[j + 2][i] == BLACK
					&& board_2015182003[j + 3][i] == BLACK)
				{
					if (j == 0)
					{
						breaking = true;
						break;
					}
					if (board_2015182003[j - 1][i] == WHITE && board_2015182003[j + 4][i] == 0)
					{
						xPos_2015182003 = i;
						yPos_2015182003 = j + 4;
						breaking = true;
						break;
					}
					if (board_2015182003[j - 1][i] == 0 && board_2015182003[j + 4][i] == WHITE)
					{
						xPos_2015182003 = i;
						yPos_2015182003 = j - 1;
						breaking = true;
						break;
					}
					else
					{

					}

				}

				if (board_2015182003[j + 1][i + 1] == BLACK
					&& board_2015182003[j + 2][i + 2] == BLACK
					&& board_2015182003[j + 3][i + 3] == 0)
				{
					if (j == 0 || i == 0)
					{
						breaking = true;
						break;
					}
					if (board_2015182003[j - 1][i - 1] == WHITE)
					{
						breaking = true;
						break;
					}
					else if (board_2015182003[j - 1][i - 1] == 0)
					{
						xPos_2015182003 = i - 1;
						yPos_2015182003 = j - 1;
						breaking = true;
						break;
					}
				}

				if (board_2015182003[j + 1][i + 1] == BLACK
					&& board_2015182003[j + 2][i + 2] == BLACK
					&& board_2015182003[j + 3][i + 3] == BLACK)
				{
					if (j == 0 && i == 0)
					{
						breaking = true;
						break;
					}
					if (board_2015182003[j - 1][i - 1] == WHITE && board_2015182003[j + 4][i + 4] == 0)
					{
						xPos_2015182003 = i + 4;
						yPos_2015182003 = j + 4;
						breaking = true;
						break;
					}
					if (board_2015182003[j][i - 1] == 0 && board_2015182003[j][i + 4] == WHITE)
					{
						xPos_2015182003 = i - 1;
						yPos_2015182003 = j - 1;
						breaking = true;
						break;
					}
					else
					{

					}

				}
			}

		}
		if (breaking == true)
		{
			break;
		}
	}

	for (int j = 0; j < 19; j++)
	{
		for (int i = 0; i < 19; i++)
		{
			if (board_2015182003[j][i] == WHITE)
			{
				if (board_2015182003[j][i + 1] == WHITE
					&& board_2015182003[j][i + 2] == WHITE
					&& board_2015182003[j][i + 3] == 0)
				{
					if (i == 0)
					{
						if (board_2015182003[j][i + 4] != BLACK)
						{
							xPos_2015182003 = i + 3;
							yPos_2015182003 = j;
						}
						breaking2 = true;
						break;
					}
					if (board_2015182003[j][i - 1] == WHITE)
					{
						xPos_2015182003 = i + 3;
						yPos_2015182003 = j;
						breaking2 = true;
						break;
					}
					if (board_2015182003[j][i - 1] == 0)
					{
						xPos_2015182003 = i - 1;
						yPos_2015182003 = j;
						breaking2 = true;
						break;
					}
					else
					{

					}
				}

				if (board_2015182003[j][i + 1] == WHITE
					&& board_2015182003[j][i + 2] == WHITE
					&& board_2015182003[j][i + 3] == WHITE)
				{
					if (i == 0)
					{
						if (board_2015182003[j][i + 4] == 0)
						{
							xPos_2015182003 = i + 4;
							yPos_2015182003 = j;
						}
						breaking2 = true;
						break;
					}
					if (board_2015182003[j][i + 4] == 0)
					{
						xPos_2015182003 = i + 4;
						yPos_2015182003 = j;
						breaking2 = true;
						break;
					}
					if (board_2015182003[j][i - 1] == 0)
					{
						xPos_2015182003 = i - 1;
						yPos_2015182003 = j;
						breaking2 = true;
						break;
					}
					else
					{

					}

				}

				if (board_2015182003[j + 1][i] == WHITE
					&& board_2015182003[j + 2][i] == WHITE
					&& board_2015182003[j + 3][i] == 0)
				{
					if (j == 0)
					{
						if (board_2015182003[j + 4][i] != BLACK)
						{
							xPos_2015182003 = i;
							yPos_2015182003 = j + 3;
						}
						breaking2 = true;
						break;
					}
					if (board_2015182003[j - 1][i] == WHITE)
					{
						xPos_2015182003 = i;
						yPos_2015182003 = j + 3;
						breaking2 = true;
						break;
					}
					else if (board_2015182003[j - 1][i] == 0)
					{
						xPos_2015182003 = i;
						yPos_2015182003 = j - 1;
						breaking2 = true;
						break;
					}
				}

				if (board_2015182003[j + 1][i] == WHITE
					&& board_2015182003[j + 2][i] == WHITE
					&& board_2015182003[j + 3][i] == WHITE)
				{
					if (j == 0)
					{
						if (board_2015182003[j + 4][i] == 0)
						{
							xPos_2015182003 = i;
							yPos_2015182003 = j + 4;
						}
						breaking2 = true;
						break;
					}
					if (board_2015182003[j + 4][i] == 0)
					{
						xPos_2015182003 = i;
						yPos_2015182003 = j + 4;
						breaking2 = true;
						break;
					}
					if (board_2015182003[j - 1][i] == 0)
					{
						xPos_2015182003 = i;
						yPos_2015182003 = j - 1;
						breaking2 = true;
						break;
					}
					else
					{

					}

				}

				if (board_2015182003[j + 1][i + 1] == WHITE
					&& board_2015182003[j + 2][i + 2] == WHITE
					&& board_2015182003[j + 3][i + 3] == 0)
				{
					if (j == 0 || i == 0)
					{
						if (board_2015182003[j + 4][i + 4] != BLACK)
						{
							xPos_2015182003 = i + 3;
							yPos_2015182003 = j + 3;
						}
						breaking2 = true;
						break;
					}
					if (board_2015182003[j - 1][i - 1] == WHITE)
					{
						xPos_2015182003 = i + 3;
						yPos_2015182003 = j + 3;
						breaking2 = true;
						break;
					}
					else if (board_2015182003[j - 1][i - 1] == 0)
					{
						xPos_2015182003 = i - 1;
						yPos_2015182003 = j - 1;
						breaking2 = true;
						break;
					}
				}

				if (board_2015182003[j + 1][i + 1] == WHITE
					&& board_2015182003[j + 2][i + 2] == WHITE
					&& board_2015182003[j + 3][i + 3] == WHITE)
				{
					if (j == 0 && i == 0)
					{
						if (board_2015182003[j + 4][i + 4] == 0)
						{
							xPos_2015182003 = i + 4;
							yPos_2015182003 = j + 4;
						}
						breaking2 = true;
						break;
					}
					if (board_2015182003[j + 4][i + 4] == 0)
					{
						xPos_2015182003 = i + 4;
						yPos_2015182003 = j + 4;
						breaking2 = true;
						break;
					}
					if (board_2015182003[j][i - 1] == 0)
					{
						xPos_2015182003 = i - 1;
						yPos_2015182003 = j - 1;
						breaking2 = true;
						break;
					}
					else
					{

					}

				}
			}

		}
		if (breaking2 == true)
		{
			break;
		}


		if (xPos_2015182003 > 18 || xPos_2015182003 < 0 || yPos_2015182003 > 18 || yPos_2015182003 < 0 || (board_2015182003[yPos_2015182003][xPos_2015182003] != 0))
		{
			while (board_2015182003[yPos_2015182003][xPos_2015182003] != 0)
			{
				xPos_2015182003 = rand() % 19;
				yPos_2015182003 = rand() % 19;
			}
		}


		*x = xPos_2015182003;
		*y = yPos_2015182003;
		board_2015182003[yPos_2015182003][xPos_2015182003] = WHITE;
	}
}

void WhiteDefence_2015182003(int x, int y)
{
	srand((unsigned)time(NULL));
	//흰돌 1
	//검은돌 -1
	board_2015182003[y][x] = BLACK;
}
void AttackBlack_2015182003(int*x, int*y)
{
	srand((unsigned)time(NULL));
	bool breaking = false;
	bool breaking2 = false;

	//직접 구현한 돌 놓기 로직을 넣으시면 됩니다.

		xPos_2015182003++;
		yPos_2015182003++;
		count_2015182003++;
		if (board_2015182003[yPos_2015182003][xPos_2015182003] != 0)
		{
			count2_2015182003 = count_2015182003;
			while (board_2015182003[yPos_2015182003][xPos_2015182003] != 0)
			{
				count2_2015182003--;
				xPos_2015182003--;
				yPos_2015182003--;
			}
		}


	
		for (int j = 0; j < 19; j++)
		{
			for (int i = 0; i < 19; i++)
			{
				if (board_2015182003[j][i] == WHITE)
				{
					if (board_2015182003[j][i + 1] == WHITE 
						&& board_2015182003[j][i + 2] == WHITE 
						&& board_2015182003[j][i + 3] == 0)
					{
						if (i == 0)
						{
							breaking = true;
							break;
						}
						if (board_2015182003[j][i - 1] == BLACK)
						{
							breaking = true;
							break;
						}
						if (board_2015182003[j][i - 1] == 0)
						{
							xPos_2015182003 = i - 1;
							yPos_2015182003 = j;
							breaking = true;
							break;
						}
						else
						{

						}
					}

					if (board_2015182003[j][i + 1] == WHITE
						&& board_2015182003[j][i + 2] == WHITE
						&& board_2015182003[j][i + 3] == WHITE)
					{
						if (i == 0)
						{
							breaking = true;
							break;
						}
						if (board_2015182003[j][i - 1] == BLACK && board_2015182003[j][i + 4] == 0)
						{
							xPos_2015182003 = i + 4;
							yPos_2015182003 = j;
							breaking = true;
							break;
						}
						if (board_2015182003[j][i - 1] == 0 && board_2015182003[j][i + 4] == BLACK)
						{
							xPos_2015182003 = i - 1;
							yPos_2015182003 = j;
							breaking = true;
							break;
						}
						else
						{

						}

					}

					if (board_2015182003[j+1][i] == WHITE
						&& board_2015182003[j+2][i] == WHITE
						&& board_2015182003[j+3][i] == 0)
					{
						if (j == 0)
						{
							breaking = true;
							break;
						}
						if (board_2015182003[j - 1][i] == BLACK)
						{
							breaking = true;
							break;
						}
						else if (board_2015182003[j - 1][i] == 0)
						{
							xPos_2015182003 = i;
							yPos_2015182003 = j - 1;
							breaking = true;
							break;
						}
					}

					if (board_2015182003[j + 1][i] == WHITE
						&& board_2015182003[j + 2][i] == WHITE
						&& board_2015182003[j + 3][i] == WHITE)
					{
						if (j == 0)
						{
							breaking = true;
							break;
						}
						if (board_2015182003[j - 1][i] == BLACK && board_2015182003[j + 4][i] == 0)
						{
							xPos_2015182003 = i;
							yPos_2015182003 = j + 4;
							breaking = true;
							break;
						}
						if (board_2015182003[j - 1][i] == 0 && board_2015182003[j + 4][i] == BLACK)
						{
							xPos_2015182003 = i;
							yPos_2015182003 = j - 1;
							breaking = true;
							break;
						}
						else
						{

						}

					}

					if (board_2015182003[j + 1][i + 1] == WHITE
						&& board_2015182003[j + 2][i + 2] == WHITE
						&& board_2015182003[j + 3][i + 3] == 0)
					{
						if (j == 0 || i == 0)
						{
							breaking = true;
							break;
						}
						if (board_2015182003[j - 1][i - 1] == BLACK)
						{
							breaking = true;
							break;
						}
						else if (board_2015182003[j - 1][i - 1] == 0)
						{
							xPos_2015182003 = i - 1;
							yPos_2015182003 = j - 1;
							breaking = true;
							break;
						}
					}

					if (board_2015182003[j + 1][i + 1] == WHITE
						&& board_2015182003[j + 2][i + 2] == WHITE
						&& board_2015182003[j + 3][i + 3] == WHITE)
					{
						if (j == 0 && i == 0)
						{
							breaking = true;
							break;
						}
						if (board_2015182003[j - 1][i - 1] == BLACK && board_2015182003[j + 4][i + 4] == 0)
						{
							xPos_2015182003 = i + 4;
							yPos_2015182003 = j + 4;
							breaking = true;
							break;
						}
						if (board_2015182003[j][i - 1] == 0 && board_2015182003[j][i + 4] == BLACK)
						{
							xPos_2015182003 = i - 1;
							yPos_2015182003 = j - 1;
							breaking = true;
							break;
						}
						else
						{

						}

					}
				}

			}
			if (breaking == true)
			{
				break;
			}
		}


		for (int j = 0; j < 19; j++)
		{
			for (int i = 0; i < 19; i++)
			{
				if (board_2015182003[j][i] == BLACK)
				{
					if (board_2015182003[j][i + 1] == BLACK
						&& board_2015182003[j][i + 2] == BLACK
						&& board_2015182003[j][i + 3] == 0)
					{
						if (i == 0)
						{
							if (board_2015182003[j][i + 4] != WHITE)
							{
								xPos_2015182003 = i + 3;
								yPos_2015182003 = j;
							}
							breaking2 = true;
							break;
						}
						if (board_2015182003[j][i - 1] == BLACK)
						{
							xPos_2015182003 = i + 3;
							yPos_2015182003 = j;
							breaking2 = true;
							break;
						}
						if (board_2015182003[j][i - 1] == 0)
						{
							xPos_2015182003 = i - 1;
							yPos_2015182003 = j;
							breaking2 = true;
							break;
						}
						else
						{

						}
					}

					if (board_2015182003[j][i + 1] == BLACK
						&& board_2015182003[j][i + 2] == BLACK
						&& board_2015182003[j][i + 3] == BLACK)
					{
						if (i == 0)
						{
							if (board_2015182003[j][i + 4] == 0)
							{
								xPos_2015182003 = i + 4;
								yPos_2015182003 = j;
							}
							breaking2 = true;
							break;
						}
						if (board_2015182003[j][i + 4] == 0)
						{
							xPos_2015182003 = i + 4;
							yPos_2015182003 = j;
							breaking2 = true;
							break;
						}
						if (board_2015182003[j][i - 1] == 0)
						{
							xPos_2015182003 = i - 1;
							yPos_2015182003 = j;
							breaking2 = true;
							break;
						}
						else
						{

						}

					}

					if (board_2015182003[j + 1][i] == BLACK
						&& board_2015182003[j + 2][i] == BLACK
						&& board_2015182003[j + 3][i] == 0)
					{
						if (j == 0)
						{
							if (board_2015182003[j + 4][i] != WHITE)
							{
								xPos_2015182003 = i;
								yPos_2015182003 = j + 3;
							}
							breaking2 = true;
							break;
						}
						if (board_2015182003[j - 1][i] == BLACK)
						{
							xPos_2015182003 = i;
							yPos_2015182003 = j + 3;
							breaking2 = true;
							break;
						}
						else if (board_2015182003[j - 1][i] == 0)
						{
							xPos_2015182003 = i;
							yPos_2015182003 = j - 1;
							breaking2 = true;
							break;
						}
					}

					if (board_2015182003[j + 1][i] == BLACK
						&& board_2015182003[j + 2][i] == BLACK
						&& board_2015182003[j + 3][i] == BLACK)
					{
						if (j == 0)
						{
							if (board_2015182003[j + 4][i] == 0)
							{
								xPos_2015182003 = i;
								yPos_2015182003 = j + 4;
							}
							breaking2 = true;
							break;
						}
						if (board_2015182003[j + 4][i] == 0)
						{
							xPos_2015182003 = i;
							yPos_2015182003 = j + 4;
							breaking2 = true;
							break;
						}
						if (board_2015182003[j - 1][i] == 0)
						{
							xPos_2015182003 = i;
							yPos_2015182003 = j - 1;
							breaking2 = true;
							break;
						}
						else
						{

						}

					}

					if (board_2015182003[j + 1][i + 1] == BLACK
						&& board_2015182003[j + 2][i + 2] == BLACK
						&& board_2015182003[j + 3][i + 3] == 0)
					{
						if (j == 0 || i == 0)
						{
							if (board_2015182003[j + 4][i + 4] != WHITE)
							{
								xPos_2015182003 == i + 3;
								yPos_2015182003 == j + 3;
							}
							breaking2 = true;
							break;
						}
						if (board_2015182003[j - 1][i - 1] == BLACK)
						{
							xPos_2015182003 = i + 3;
							yPos_2015182003 = j + 3;
							breaking2 = true;
							break;
						}
						else if (board_2015182003[j - 1][i - 1] == 0)
						{
							xPos_2015182003 = i - 1;
							yPos_2015182003 = j - 1;
							breaking2 = true;
							break;
						}
					}

					if (board_2015182003[j + 1][i + 1] == BLACK
						&& board_2015182003[j + 2][i + 2] == BLACK
						&& board_2015182003[j + 3][i + 3] == BLACK)
					{
						if (j == 0 && i == 0)
						{
							if (board_2015182003[j + 4][i + 4] == 0)
							{
								xPos_2015182003 = i + 4;
								yPos_2015182003 = j + 4;
							}
							breaking2 = true;
							break;
						}
						if (board_2015182003[j + 4][i + 4] == 0)
						{
							xPos_2015182003 = i + 4;
							yPos_2015182003 = j + 4;
							breaking2 = true;
							break;
						}
						if (board_2015182003[j][i - 1] == 0)
						{
							xPos_2015182003 = i - 1;
							yPos_2015182003 = j - 1;
							breaking2 = true;
							break;
						}
						else
						{

						}

					}
				}

			}
			if (breaking2 == true)
			{
				break;
			}
		}


		if (xPos_2015182003 > 18 || xPos_2015182003 < 0 || yPos_2015182003 > 18 || yPos_2015182003 < 0 || (board_2015182003[yPos_2015182003][xPos_2015182003] != 0))
		{
			while (board_2015182003[yPos_2015182003][xPos_2015182003] != 0)
			{
				xPos_2015182003 = rand() % 19;
				yPos_2015182003 = rand() % 19;
			}
		}


	*x = xPos_2015182003;
	*y = yPos_2015182003;

	board_2015182003[yPos_2015182003][xPos_2015182003] = BLACK;


}

void DefenceBlack_2015182003(int x, int y)
{
	srand((unsigned)time(NULL));
	//흰돌 1
	//검은돌 -1
	board_2015182003[y][x] = WHITE;
}
