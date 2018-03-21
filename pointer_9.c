#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#define WIDTH 19
#define HEIGHT 19

#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define SPACE 32
#define ENTER 13

typedef enum target { EMPTY = 0, MAN = 1 } TARGET;

typedef unsigned char shortchar;
typedef struct arrow {
	int col, row;
} ARROR;

void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}


void draw_board(TARGET locate[][WIDTH]);
int took_stone(TARGET locate[][WIDTH], ARROR pointLocation);
ARROR get_position();							// �̵�Ű�� ��ġ�� �Է¹��� �Լ�
int next_generation(TARGET present[][WIDTH]) {
	int count = 0;
	TARGET future[HEIGHT][WIDTH] = { EMPTY };		// ���� ���� ��ȭ�� ���� �ٿ� ������ �ֹǷ� �Ű��� ����
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			int neighbor = 0;
			TARGET *p = &(present[i][j]);
			neighbor += *(p - HEIGHT - 1);
			neighbor += *(p - HEIGHT);
			neighbor += *(p - HEIGHT + 1);
			neighbor += *(p - 1);
			neighbor += *(p + 1);
			neighbor += *(p + HEIGHT - 1);
			neighbor += *(p + HEIGHT);
			neighbor += *(p + HEIGHT + 1);
			if (present[i][j] == EMPTY) {
				if (neighbor == 3) {
					future[i][j] = MAN;
				}
			}
			else if (present[i][j] == MAN) {
				++count;
				if (neighbor == 2 || neighbor == 3) {
					future[i][j] = MAN;
				}
			}
		}
	}
	memcpy(present, future, sizeof(future));
	return count;
}

int main() {

	shortchar generation = 0;						// ���� ����
	ARROR pointLocation;							// ��ġ �Է�
	TARGET status[HEIGHT][WIDTH] = { EMPTY };		// ���� ��Ȳ ROW, COLS
	shortchar gameSetting = 0;						// ���� ���� ��Ȳ

	do {

		draw_board(status);							// ���� �׸���

		printf("������ ��ġ�� �����ϼ���(����Ű�� �̵�, SPACE�� ��ġ, ENTER�� ����)\n");

		pointLocation = get_position();

		if (pointLocation.col == -1 && pointLocation.row == -1) {
			gameSetting = 1;
			continue;
		}
		else if (took_stone(status, pointLocation)) {
			continue;
		}

	} while (!gameSetting);
	do {
		++generation;
		draw_board(status);
		// Sleep(1000); // �ӵ� ����
	} while (next_generation(status));

	printf("���� �����ڰ� �����ϴ�.\n");

	return 0;
}

void draw_board(TARGET locate[][WIDTH]) {
	system("cls");
	for (int i = 64; i <= 64 + WIDTH; i++) {		// X��ǥ�� ���
		if (i == 64) {
			printf("     ");
		}
		else {
			printf("%c ", (char)i);
		}
	}
	printf("\n");
	// ���� ���� ����
	printf("  ����");
	for (int j = 0; j < WIDTH; j++) {
		printf("����");
	}
	printf("��\n");

	// ���� ������
	for (int i = 0; i < HEIGHT; i++) {
		printf("%02d����", i + 1);						// Y��ǥ�� ���
		for (int j = 0; j < WIDTH; j++) {
			if (locate[i][j] == 0) {
				printf("����");
			}
			else if (locate[i][j] == -1) {
				printf("��");
			}
			else {
				printf("��");
			}
		}
		printf("��\n");
	}

	// �Ʒ��� ���� ����
	printf("  ����");
	for (int j = 0; j < WIDTH; j++) {
		printf("����");
	}
	printf("��\n");
}

int took_stone(TARGET locate[][WIDTH], ARROR pointLocation) {
	int c = pointLocation.col - 1;
	int r = pointLocation.row - 1;

	if (locate[r][c] != 0) {
		return 1;						// �ش� ��ġ ������ �ִ� ���
	}
	else {
		locate[r][c] = MAN;				// status[HEIGHT][WIDTH]�� ����
	}
	return 0;
}

ARROR get_position() {

	ARROR instance;
	ARROR end = { -1, -1 };
	int k = 1;
	int x = 1, y = 1;
	int cursor_x = 5, cursor_y = 2;
	do {
		int z = _getch(); // char c ������ ���ڸ� �Է� �޴´�

		switch (z) {
		case RIGHT:
			++x, cursor_x += 2;
			if (x > WIDTH) {
				--x, cursor_x -= 2; // ���� �������� �Ѿ�ٸ� �Է��� ���ð� �˴ϴ�. 
			}
			gotoxy(cursor_x, cursor_y); // �ƴ϶�� Ŀ���� �Է��� ��ǥ�� �̵��մϴ�.
			break; // �׸��� �ٽ� �Է��� �ޱ� ���� swtich���� ���� ������ �ٽ� ��Ʈ�� �˴ϴ�.

		case LEFT:
			--x, cursor_x -= 2;
			if (x <= 0) {
				++x, cursor_x += 2;
			}
			gotoxy(cursor_x, cursor_y);
			break;

		case UP:
			--y, --cursor_y;
			if (y <= 0) {
				++y, ++cursor_y;
			}
			gotoxy(cursor_x, cursor_y);
			break;

		case DOWN:
			++y, ++cursor_y;
			if (y > HEIGHT) {
				--y, --cursor_y;
			}
			gotoxy(cursor_x, cursor_y);
			break;

		case SPACE:		// SPACE�� �ԷµǸ� ���� ��ġ�� �����ǿ� ����
			instance.col = x;
			instance.row = y;
			k = 0;		// ���ѷ����� ����ϴ�.
			break;

		case ENTER:		// ENTER�� �ԷµǸ� life game ����
			instance = end;
			k = 0;		//
		}
	} while (k);

	return instance;
}