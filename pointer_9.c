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
ARROR get_position();							// 이동키로 위치를 입력받을 함수
int next_generation(TARGET present[][WIDTH]) {
	int count = 0;
	TARGET future[HEIGHT][WIDTH] = { EMPTY };		// 현재 줄의 변화가 다음 줄에 영향을 주므로 매개값 생성
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

	shortchar generation = 0;						// 세대 정보
	ARROR pointLocation;							// 위치 입력
	TARGET status[HEIGHT][WIDTH] = { EMPTY };		// 격자 상황 ROW, COLS
	shortchar gameSetting = 0;						// 게임 진행 상황

	do {

		draw_board(status);							// 격자 그리기

		printf("생명의 위치를 지정하세요(방향키로 이동, SPACE로 배치, ENTER로 저장)\n");

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
		// Sleep(1000); // 속도 제어
	} while (next_generation(status));

	printf("남은 생존자가 없습니다.\n");

	return 0;
}

void draw_board(TARGET locate[][WIDTH]) {
	system("cls");
	for (int i = 64; i <= 64 + WIDTH; i++) {		// X좌표계 출력
		if (i == 64) {
			printf("     ");
		}
		else {
			printf("%c ", (char)i);
		}
	}
	printf("\n");
	// 윗줄 격자 생성
	printf("  ┌─");
	for (int j = 0; j < WIDTH; j++) {
		printf("┬─");
	}
	printf("┐\n");

	// 메인 게임판
	for (int i = 0; i < HEIGHT; i++) {
		printf("%02d├─", i + 1);						// Y좌표계 출력
		for (int j = 0; j < WIDTH; j++) {
			if (locate[i][j] == 0) {
				printf("┼─");
			}
			else if (locate[i][j] == -1) {
				printf("○");
			}
			else {
				printf("●");
			}
		}
		printf("┤\n");
	}

	// 아래줄 격자 생성
	printf("  └─");
	for (int j = 0; j < WIDTH; j++) {
		printf("┴─");
	}
	printf("┘\n");
}

int took_stone(TARGET locate[][WIDTH], ARROR pointLocation) {
	int c = pointLocation.col - 1;
	int r = pointLocation.row - 1;

	if (locate[r][c] != 0) {
		return 1;						// 해당 위치 생명이 있는 경우
	}
	else {
		locate[r][c] = MAN;				// status[HEIGHT][WIDTH]에 대입
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
		int z = _getch(); // char c 변수에 문자를 입력 받는다

		switch (z) {
		case RIGHT:
			++x, cursor_x += 2;
			if (x > WIDTH) {
				--x, cursor_x -= 2; // 만약 게임판을 넘어선다면 입력이 무시가 됩니다. 
			}
			gotoxy(cursor_x, cursor_y); // 아니라면 커서를 입력한 좌표로 이동합니다.
			break; // 그리고 다시 입력을 받기 위해 swtich문을 빠져 나가며 다시 루트가 됩니다.

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

		case SPACE:		// SPACE가 입력되면 현재 위치를 게임판에 저장
			instance.col = x;
			instance.row = y;
			k = 0;		// 무한루프를 벗어납니다.
			break;

		case ENTER:		// ENTER가 입력되면 life game 시작
			instance = end;
			k = 0;		//
		}
	} while (k);

	return instance;
}