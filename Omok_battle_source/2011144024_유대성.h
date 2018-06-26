#include <random>

#define BOARD_SIZE 19
#define BLACK -1
#define WHITE 1

typedef struct BOARD_NODE_2011144024_rev01 {
	int color;		// �� -1, �� 1
	int point;
	int xMax;
	int yMax;
	int uMax;
	int dMax;
} GAME_BOARD_2011144024_rev01;

const GAME_BOARD_2011144024_rev01 BOARD_NULL_2011144024_rev01 = { 0, 0, 20, 20, 20, 20 };

GAME_BOARD_2011144024_rev01 game_board_2011144024_rev01[BOARD_SIZE][BOARD_SIZE];

void xClear_2011144024_rev01(int x, int y) {
	game_board_2011144024_rev01[y][x].xMax = 0;
	if (x != BOARD_SIZE - 1 && game_board_2011144024_rev01[y][x].color == game_board_2011144024_rev01[y][x + 1].color && game_board_2011144024_rev01[y][x + 1].xMax != 0) { xClear_2011144024_rev01(x + 1, y); }
	if (x != 0 && game_board_2011144024_rev01[y][x].color == game_board_2011144024_rev01[y][x - 1].color && game_board_2011144024_rev01[y][x - 1].xMax != 0) { xClear_2011144024_rev01(x - 1, y); }
}

void yClear_2011144024_rev01(int x, int y) {
	game_board_2011144024_rev01[y][x].yMax = 0;
	if (y != BOARD_SIZE - 1 && game_board_2011144024_rev01[y][x].color == game_board_2011144024_rev01[y + 1][x].color && game_board_2011144024_rev01[y + 1][x].yMax != 0) { yClear_2011144024_rev01(x, y + 1); }
	if (y != 0 && game_board_2011144024_rev01[y][x].color == game_board_2011144024_rev01[y - 1][x].color && game_board_2011144024_rev01[y - 1][x].yMax != 0) { yClear_2011144024_rev01(x, y - 1); }
}

void uClear_2011144024_rev01(int x, int y) {
	game_board_2011144024_rev01[y][x].uMax = 0;
	if (y != BOARD_SIZE - 1 && x != 0 && game_board_2011144024_rev01[y][x].color == game_board_2011144024_rev01[y + 1][x - 1].color && game_board_2011144024_rev01[y + 1][x - 1].uMax != 0) { uClear_2011144024_rev01(x - 1, y + 1); }
	if (y != 0 && x != BOARD_SIZE - 1 && game_board_2011144024_rev01[y][x].color == game_board_2011144024_rev01[y - 1][x + 1].color && game_board_2011144024_rev01[y - 1][x + 1].uMax != 0) { uClear_2011144024_rev01(x + 1, y - 1); }
}

void dClear_2011144024_rev01(int x, int y) {
	game_board_2011144024_rev01[y][x].dMax = 0;
	if (y != BOARD_SIZE - 1 && x != BOARD_SIZE - 1 && game_board_2011144024_rev01[y][x].color == game_board_2011144024_rev01[y + 1][x + 1].color && game_board_2011144024_rev01[y + 1][x + 1].dMax != 0) { dClear_2011144024_rev01(x + 1, y + 1); }
	if (y != 0 && x != 0 && game_board_2011144024_rev01[y][x].color == game_board_2011144024_rev01[y - 1][x - 1].color && game_board_2011144024_rev01[y - 1][x - 1].dMax != 0) { dClear_2011144024_rev01(x - 1, y - 1); }
}

void xUnder_max_update_2011144024_rev01(int x, int y, int type) {
	if (game_board_2011144024_rev01[y][x - 1].color == type && game_board_2011144024_rev01[y][x - 1].xMax != 0) {
		if (game_board_2011144024_rev01[y][x - 1].xMax >= 1) { game_board_2011144024_rev01[y][x - 1].xMax += 1; if (x - 2 != 0 && game_board_2011144024_rev01[y][x - 2].color != -1 * type) xClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y][x - 1].xMax >= 2) { game_board_2011144024_rev01[y][x - 2].xMax += 1; if (x - 3 != 0 && game_board_2011144024_rev01[y][x - 3].color != -1 * type) xClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y][x - 1].xMax >= 3) { game_board_2011144024_rev01[y][x - 3].xMax += 1; if (x - 4 != 0 && game_board_2011144024_rev01[y][x - 4].color != -1 * type) xClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y][x - 1].xMax >= 4) game_board_2011144024_rev01[y][x - 4].xMax += 1;
		if (game_board_2011144024_rev01[y][x - 1].xMax >= 5) xClear_2011144024_rev01(x, y);		// ���� �̻��� �߻��ϸ� �� �̻� �������� ����
		game_board_2011144024_rev01[y][x].xMax = game_board_2011144024_rev01[y][x - 1].xMax;
	}
}

void xOver_max_update_2011144024_rev01(int x, int y, int type) {
	if (game_board_2011144024_rev01[y][x + 1].color == type && game_board_2011144024_rev01[y][x + 1].xMax != 0) {
		if (game_board_2011144024_rev01[y][x + 1].xMax >= 1) { game_board_2011144024_rev01[y][x + 1].xMax += 1; if (x + 2 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y][x + 2].color != -1 * type) xClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y][x + 1].xMax >= 2) { game_board_2011144024_rev01[y][x + 2].xMax += 1; if (x + 3 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y][x + 3].color != -1 * type) xClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y][x + 1].xMax >= 3) { game_board_2011144024_rev01[y][x + 3].xMax += 1; if (x + 4 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y][x + 4].color != -1 * type) xClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y][x + 1].xMax >= 4) game_board_2011144024_rev01[y][x + 4].xMax += 1;
		if (game_board_2011144024_rev01[y][x + 1].xMax >= 5) xClear_2011144024_rev01(x, y);		// ���� �̻��� �߻��ϸ� �� �̻� �������� ����
		game_board_2011144024_rev01[y][x].xMax = game_board_2011144024_rev01[y][x + 1].xMax;
	}
}

void yUnder_max_update_2011144024_rev01(int x, int y, int type) {
	if (game_board_2011144024_rev01[y - 1][x].color == type && game_board_2011144024_rev01[y - 1][x].yMax != 0) {
		if (game_board_2011144024_rev01[y - 1][x].yMax >= 1) { game_board_2011144024_rev01[y - 1][x].yMax += 1; if (y - 2 != 0 && game_board_2011144024_rev01[y - 2][x].color != -1 * type) yClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y - 1][x].yMax >= 2) { game_board_2011144024_rev01[y - 1][x].yMax += 1; if (y - 3 != 0 && game_board_2011144024_rev01[y - 3][x].color != -1 * type) yClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y - 1][x].yMax >= 3) { game_board_2011144024_rev01[y - 1][x].yMax += 1; if (y - 4 != 0 && game_board_2011144024_rev01[y - 4][x].color != -1 * type) yClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y - 1][x].yMax >= 4) game_board_2011144024_rev01[y - 1][x].yMax += 1;
		if (game_board_2011144024_rev01[y - 1][x].yMax >= 5) yClear_2011144024_rev01(x, y);		// ���� �̻��� �߻��ϸ� �� �̻� �������� ����
		game_board_2011144024_rev01[y][x].yMax = game_board_2011144024_rev01[y - 1][x].yMax;
	}
}

void yOver_max_update_2011144024_rev01(int x, int y, int type) {
	if (game_board_2011144024_rev01[y + 1][x].color == type && game_board_2011144024_rev01[y + 1][x].yMax != 0) {
		if (game_board_2011144024_rev01[y + 1][x].yMax >= 1) { game_board_2011144024_rev01[y + 1][x].yMax += 1; if (y + 2 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y + 2][x].color != -1 * type) yClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y + 1][x].yMax >= 2) { game_board_2011144024_rev01[y + 1][x].yMax += 1; if (y + 3 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y + 3][x].color != -1 * type) yClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y + 1][x].yMax >= 3) { game_board_2011144024_rev01[y + 1][x].yMax += 1; if (y + 4 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y + 4][x].color != -1 * type) yClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y + 1][x].yMax >= 4) game_board_2011144024_rev01[y + 1][x].yMax += 1;
		if (game_board_2011144024_rev01[y + 1][x].yMax >= 5) yClear_2011144024_rev01(x, y);		// ���� �̻��� �߻��ϸ� �� �̻� �������� ����
		game_board_2011144024_rev01[y][x].yMax = game_board_2011144024_rev01[y + 1][x].yMax;
	}
}

void uUnder_max_update_2011144024_rev01(int x, int y, int type) {
	if (game_board_2011144024_rev01[y + 1][x - 1].color == type && game_board_2011144024_rev01[y + 1][x - 1].uMax != 0) {
		if (game_board_2011144024_rev01[y + 1][x - 1].uMax >= 1) { game_board_2011144024_rev01[y + 1][x - 1].uMax += 1; if (x - 2 != 0 && y + 2 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y + 2][x - 2].color != -1 * type) uClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y + 1][x - 1].uMax >= 2) { game_board_2011144024_rev01[y + 1][x - 1].uMax += 1; if (x - 3 != 0 && y + 3 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y + 3][x - 3].color != -1 * type) uClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y + 1][x - 1].uMax >= 3) { game_board_2011144024_rev01[y + 1][x - 1].uMax += 1; if (x - 4 != 0 && y + 4 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y + 4][x - 4].color != -1 * type) uClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y + 1][x - 1].uMax >= 4) game_board_2011144024_rev01[y + 1][x - 1].uMax += 1;
		if (game_board_2011144024_rev01[y + 1][x - 1].uMax >= 5) dClear_2011144024_rev01(x, y);		// ���� �̻��� �߻��ϸ� �� �̻� �������� ����
		game_board_2011144024_rev01[y][x].uMax = game_board_2011144024_rev01[y + 1][x - 1].uMax;
	}
}

void uOver_max_update_2011144024_rev01(int x, int y, int type) {
	if (game_board_2011144024_rev01[y - 1][x + 1].color == type && game_board_2011144024_rev01[y - 1][x + 1].uMax != 0) {
		if (game_board_2011144024_rev01[y - 1][x + 1].uMax >= 1) { game_board_2011144024_rev01[y - 1][x + 1].uMax += 1; if (x + 2 != BOARD_SIZE - 1 && y - 2 != 0 && game_board_2011144024_rev01[y - 2][x + 2].color != -1 * type) uClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y - 1][x + 1].uMax >= 2) { game_board_2011144024_rev01[y - 1][x + 1].uMax += 1; if (x + 3 != BOARD_SIZE - 1 && y - 3 != 0 && game_board_2011144024_rev01[y - 3][x + 3].color != -1 * type) uClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y - 1][x + 1].uMax >= 3) { game_board_2011144024_rev01[y - 1][x + 1].uMax += 1; if (x + 4 != BOARD_SIZE - 1 && y - 4 != 0 && game_board_2011144024_rev01[y - 4][x + 4].color != -1 * type) uClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y - 1][x + 1].uMax >= 4) game_board_2011144024_rev01[y - 1][x + 1].uMax += 1;
		if (game_board_2011144024_rev01[y - 1][x + 1].uMax >= 5) dClear_2011144024_rev01(x, y);		// ���� �̻��� �߻��ϸ� �� �̻� �������� ����
		game_board_2011144024_rev01[y][x].uMax = game_board_2011144024_rev01[y - 1][x + 1].uMax;
	}
}

void dUnder_max_update_2011144024_rev01(int x, int y, int type) {
	if (game_board_2011144024_rev01[y - 1][x - 1].color == type && game_board_2011144024_rev01[y - 1][x - 1].dMax != 0) {
		if (game_board_2011144024_rev01[y - 1][x - 1].dMax >= 1) { game_board_2011144024_rev01[y - 1][x - 1].dMax += 1;  if (x - 2 != 0 && y - 2 != 0 && game_board_2011144024_rev01[y - 2][x - 2].color != -1 * type) dClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y - 1][x - 1].dMax >= 2) { game_board_2011144024_rev01[y - 1][x - 1].dMax += 1;  if (x - 3 != 0 && y - 3 != 0 && game_board_2011144024_rev01[y - 3][x - 3].color != -1 * type) dClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y - 1][x - 1].dMax >= 3) { game_board_2011144024_rev01[y - 1][x - 1].dMax += 1;  if (x - 4 != 0 && y - 4 != 0 && game_board_2011144024_rev01[y - 4][x - 4].color != -1 * type) dClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y - 1][x - 1].dMax >= 4) game_board_2011144024_rev01[y - 1][x - 1].dMax += 1;
		if (game_board_2011144024_rev01[y - 1][x - 1].dMax >= 5) dClear_2011144024_rev01(x, y);		// ���� �̻��� �߻��ϸ� �� �̻� �������� ����
		game_board_2011144024_rev01[y][x].dMax = game_board_2011144024_rev01[y - 1][x - 1].dMax;
	}
}

void dOver_max_update_2011144024_rev01(int x, int y, int type) {
	if (game_board_2011144024_rev01[y + 1][x + 1].color == type && game_board_2011144024_rev01[y + 1][x + 1].dMax != 0) {
		if (game_board_2011144024_rev01[y + 1][x + 1].dMax >= 1) { game_board_2011144024_rev01[y + 1][x + 1].dMax += 1; if (x + 2 != BOARD_SIZE - 1 && y + 2 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y + 2][x + 2].color != -1 * type) dClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y + 1][x + 1].dMax >= 2) { game_board_2011144024_rev01[y + 1][x + 1].dMax += 1; if (x + 3 != BOARD_SIZE - 1 && y + 3 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y + 3][x + 3].color != -1 * type) dClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y + 1][x + 1].dMax >= 3) { game_board_2011144024_rev01[y + 1][x + 1].dMax += 1; if (x + 4 != BOARD_SIZE - 1 && y + 4 != BOARD_SIZE - 1 && game_board_2011144024_rev01[y + 4][x + 4].color != -1 * type) dClear_2011144024_rev01(x, y); }
		if (game_board_2011144024_rev01[y + 1][x + 1].dMax >= 4) game_board_2011144024_rev01[y + 1][x + 1].dMax += 1;
		if (game_board_2011144024_rev01[y + 1][x + 1].dMax >= 5) dClear_2011144024_rev01(x, y);		// ���� �̻��� �߻��ϸ� �� �̻� �������� ����
		game_board_2011144024_rev01[y][x].dMax = game_board_2011144024_rev01[y + 1][x + 1].dMax;
	}
}

void max_update_2011144024_rev01(int x, int y, int type) {
	if (x == 0 && y == 0) {
		xOver_max_update_2011144024_rev01(x, y, type);
		yOver_max_update_2011144024_rev01(x, y, type);
		dOver_max_update_2011144024_rev01(x, y, type);
	}
	else if (x == BOARD_SIZE - 1 && y == 0) {
		xUnder_max_update_2011144024_rev01(x, y, type);
		yOver_max_update_2011144024_rev01(x, y, type);
		uUnder_max_update_2011144024_rev01(x, y, type);
	}
	else if (x == BOARD_SIZE - 1 && y == BOARD_SIZE - 1) {
		xUnder_max_update_2011144024_rev01(x, y, type);
		yUnder_max_update_2011144024_rev01(x, y, type);
		dUnder_max_update_2011144024_rev01(x, y, type);
	}
	else if (x == 0 && y == BOARD_SIZE - 1) {
		xOver_max_update_2011144024_rev01(x, y, type);
		yUnder_max_update_2011144024_rev01(x, y, type);
		uOver_max_update_2011144024_rev01(x, y, type);
	}
	else if (y == 0) {
		xOver_max_update_2011144024_rev01(x, y, type);
		xUnder_max_update_2011144024_rev01(x, y, type);
		yOver_max_update_2011144024_rev01(x, y, type);
		dOver_max_update_2011144024_rev01(x, y, type);
		uUnder_max_update_2011144024_rev01(x, y, type);
	}
	else if (y == BOARD_SIZE - 1) {
		xUnder_max_update_2011144024_rev01(x, y, type);
		xOver_max_update_2011144024_rev01(x, y, type);
		yUnder_max_update_2011144024_rev01(x, y, type);
		dUnder_max_update_2011144024_rev01(x, y, type);
		uOver_max_update_2011144024_rev01(x, y, type);
	}
	else if (x == BOARD_SIZE - 1) {
		xUnder_max_update_2011144024_rev01(x, y, type);
		yOver_max_update_2011144024_rev01(x, y, type);
		yUnder_max_update_2011144024_rev01(x, y, type);
		dUnder_max_update_2011144024_rev01(x, y, type);
		uUnder_max_update_2011144024_rev01(x, y, type);
	}
	else if (x == 0) {
		xOver_max_update_2011144024_rev01(x, y, type);
		yOver_max_update_2011144024_rev01(x, y, type);
		yUnder_max_update_2011144024_rev01(x, y, type);
		dOver_max_update_2011144024_rev01(x, y, type);
		uOver_max_update_2011144024_rev01(x, y, type);
	}
	else {
		if (game_board_2011144024_rev01[y][x - 1].color == type && game_board_2011144024_rev01[y][x + 1].color == type) {
			
		}
		else if (game_board_2011144024_rev01[y - 1][x].color == type && game_board_2011144024_rev01[y + 1][x].color == type) {

		}
		else if (game_board_2011144024_rev01[y - 1][x - 1].color == type && game_board_2011144024_rev01[y + 1][x + 1].color == type) {
		
		}
		else if (game_board_2011144024_rev01[y - 1][x + 1].color == type && game_board_2011144024_rev01[y + 1][x - 1].color == type) {
		
		}
		else {
		}
	}
}

void block_check_2011144024_rev01(int x, int y) {

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if(game_board_2011144024_rev01[i][j].color == 0){		// �� ������ ���� �� �� ����
				if (game_board_2011144024_rev01[i][j].xMax == 4) {
					if (game_board_2011144024_rev01[i][j].color == WHITE) {
					}
					else if (game_board_2011144024_rev01[i][j].color == BLACK) {

					}
				}
			}
		}
	}

	// 1. 3����, ��ĭ �� 4������ ������ ĿƮ

	// ������ ������ �򵹿� ��õ -> ���ѹ� ������ Ȯ��


	// 2. �����鼭 ���ݰ��� �� ���� �Ǵ� �����ұ�?
	// 3. ��ĭ ��� �밢�� ������ ����
	// ������ 4x3
	// ������ L��, ȣ����, �� �ﰢ

	// ���� ���, ���� ���� 
	// �� ���� ���޾� 4 > ���� �� 3�� + �� �� �̾���� > ���� �� 3�� > ������ L��, ȣ����, �� �ﰢ > �ΰ� > �Ѱ�

}



void WhiteAttack_2011144024_rev01(int*x, int*y)
{
	// 3x3 ����, 4x4 ����, 6�� �����ϵ� ���� ����x

	int xPos = 1;
	int yPos = 1;

	block_check_2011144024_rev01(xPos, yPos);


	*x = xPos;
	*y = yPos;
	game_board_2011144024_rev01[yPos][xPos].color = WHITE;
}
void WhiteDefence_2011144024_rev01(int x, int y)
{
	//�� 1
	//������ -1
	game_board_2011144024_rev01[y][x].color = BLACK;

	max_update_2011144024_rev01(x, y, BLACK);
}
void AttackBlack_2011144024_rev01(int*x, int*y)
{
	// 3x3, 4x4, 6�� �Ұ�

	int xPos = 1;
	int yPos = 1;


	*x = xPos;
	*y = yPos;
	game_board_2011144024_rev01[yPos][xPos].color = BLACK;

}
void DefenceBlack_2011144024_rev01(int x, int y)
{
	//�� 1
	//������ -1
	game_board_2011144024_rev01[y][x].color = WHITE;

	max_update_2011144024_rev01(x, y, WHITE);
}


