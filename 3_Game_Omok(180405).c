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
#define ENTER 13

typedef enum target { WHITE = -1, EMPTY = 0, BLACK = 1 } TARGET;
typedef enum game { WIN = 1, DRAW = 0, LOSE = -1 } GAME;				// white 입장의 승패

typedef unsigned char shortchar;
typedef struct arrow {					// H9 와 같은 방법으로 입력받기 위한 구조체
	int col, row;
} ARROR;

typedef struct LINEINFO {
	int B, W;
} LINEINFO;

typedef struct LINEARINFO {
	int number;
	int color;
} LINEARINFO;

void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

char *return_stone(char stone);
void draw_board(TARGET locate[][WIDTH], LINEINFO colInfo[], LINEINFO rowInfo[]);		// 바둑판 그리는 함수
int took_stone(TARGET locate[][WIDTH], ARROR pointLocation, shortchar turn, LINEINFO colInfo[], LINEINFO rowInfo[]);
void find_checkmate(TARGET locate[][WIDTH], GAME *pResult);
void game_result(GAME result);
ARROR get_position();								// 이동키로 위치를 입력받을 함수
void turn_empty(LINEINFO target[], int limit);
void linear_empty(LINEARINFO target[], int limit);

int main() {

	shortchar turn = 1;								// 턴 정보
	ARROR pointLocation;							// 위치 입력
	GAME result = DRAW;								// 게임 결과
	GAME *pResult = &result;
	TARGET status[HEIGHT][WIDTH] = { EMPTY };		// 바둑판 상황 ROW, COLS
	LINEINFO colInfo[HEIGHT];
	turn_empty(colInfo, HEIGHT);
	LINEINFO rowInfo[WIDTH];
	turn_empty(rowInfo, WIDTH);
	LINEARINFO u[WIDTH + HEIGHT - 1], d[WIDTH + HEIGHT - 1], c[WIDTH], r[HEIGHT];
	linear_empty(u, WIDTH + HEIGHT - 1);
	linear_empty(d, WIDTH + HEIGHT - 1);
	linear_empty(c, WIDTH);
	linear_empty(r, HEIGHT);


	do {
		draw_board(status, colInfo, rowInfo);							// 바둑판 그리기

		if (turn % 2) {								// 턴정보 알려줌
			printf("%d번째 턴, 백돌 : %d, 흑돌 : %d\n", turn, (turn - 1) / 2, (turn - 1) / 2);
		}
		else {
			printf("%d번째 턴, 백돌 : %d, 흑돌 : %d\n", turn, turn / 2, turn / 2 - 1);
		}

		printf("다음 돌의 위치를 지정하세요\n");

		pointLocation = get_position();

		if (took_stone(status, pointLocation, turn, colInfo, rowInfo)) {
			continue;
		}

		find_checkmate(status, pResult);

		turn++;

	} while (!(result));

	draw_board(status, colInfo, rowInfo);							// 바둑판 그리기
	game_result(result);

	return 0;
}

char *return_stone(char stone) {
	if (stone == 'B') {
		return "●";
	}
	else if (stone == 'W') {
		return "○";
	}
	else {
		return "□";
	}
}

void draw_board(TARGET locate[][WIDTH], LINEINFO colInfo[], LINEINFO rowInfo[]) {
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

	// 메인 바둑판
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
		printf("┤ B:%2d, W:%2d\n", (colInfo + i)->B, (colInfo + i)->W);
	}

	// 아래줄 격자 생성
	printf("  └─");
	for (int j = 0; j < WIDTH; j++) {
		printf("┴─");
	}
	printf("┘\n");
	printf("B: ");
	for (int j = 0; j < WIDTH; j++) {
		printf("%2d", (rowInfo + j)->B);
	}
	printf("\nW: ");
	for (int j = 0; j < WIDTH; j++) {
		printf("%2d", (rowInfo + j)->W);
	}
	printf("\n\n");



}


int took_stone(TARGET locate[][WIDTH], ARROR pointLocation, shortchar turn, LINEINFO colInfo[], LINEINFO rowInfo[]) {
	int c = pointLocation.col - 1;
	int r = pointLocation.row - 1;

	if (locate[r][c] != 0) {
		return 1;								// 해당 위치에 돌이 있는 경우
	}
	else {

		if (turn % 2) {
			(colInfo + r)->W += 1;
			(rowInfo + c)->W += 1;
			locate[r][c] = WHITE;				// status[HEIGHT][WIDTH]에 대입
		}
		else {
			(colInfo + r)->B += 1;
			(rowInfo + c)->B += 1;
			locate[r][c] = BLACK;
		}
	}
	return 0;
}
void find_checkmate(TARGET locate[][WIDTH], GAME *pResult) {

	for (int i = 0; i < HEIGHT; i++) {
		if (*pResult) {
			break;
		}
		for (int j = 0; j < WIDTH; j++) {
			if (locate[i][j] != 0) {                        // 뭔가 돌이 있으면
				if (i >= 2 && i <= HEIGHT - 3 && j >= 2 && j <= WIDTH - 3) {
					if (locate[i - 1][j - 1] == locate[i][j] && locate[i][j] == locate[i + 1][j + 1]) {            // ↘방향
						if (locate[i - 2][j - 2] == locate[i][j] && locate[i][j] == locate[i + 2][j + 2]) {
							*pResult = locate[i][j];
						}
						else {
							continue;
						}
					}
					else if (locate[i + 1][j - 1] == locate[i][j] && locate[i][j] == locate[i - 1][j + 1]) {    // ↗방향
						if (locate[i + 2][j - 2] == locate[i][j] && locate[i][j] == locate[i - 2][j + 2]) {
							*pResult = locate[i][j];
							break;
						}
						else {
							continue;
						}
					}
				}
				else if (i >= 2 && i <= HEIGHT - 3) {
					if (locate[i - 1][j] == locate[i][j] && locate[i][j] == locate[i + 1][j]) {                    // ↑방향
						if (locate[i - 2][j] == locate[i][j] && locate[i][j] == locate[i + 2][j]) {
							*pResult = locate[i][j];
							break;
						}
						else {
							continue;
						}
					}
				}
				else if (j >= 2 && j <= WIDTH - 3) {
					if (locate[i][j - 1] == locate[i][j] && locate[i][j] == locate[i][j + 1]) {                    // →방향
						if (locate[i][j - 2] == locate[i][j] && locate[i][j] == locate[i][j + 2]) {
							*pResult = locate[i][j];
							break;
						}
						else {
							continue;
						}
					}
				}
				else {
					continue;
				}
			}
		}
	}
}

void game_result(GAME result) {
	switch (result) {
	case -1:
		printf("백돌이 이겼습니다.\n");
		break;
	case 1:
		printf("흑돌이 이겼습니다.\n");
		break;
	case 0:
		printf("무승부입니다.\n");
		break;
	}
}

ARROR get_position() {

	ARROR instance;
	int k = 1;
	int x = 10, y = 10;
	int cursor_x = 23, cursor_y = 11;
	do {
		int z = _getch(); // char c 변수에 문자를 입력 받는다

		switch (z) {
		case RIGHT:
			++x, cursor_x += 2;
			if (x > WIDTH) {
				--x, cursor_x -= 2; // 만약 오목판을 넘어선다면 입력이 무시가 됩니다. 
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

		case ENTER:  //ENTER가 입력되면 현재 위치를 오목 배열에 저장
			instance.col = x;
			instance.row = y;
			k = 0; // 입력을 하였으니 순서가 바뀌어야겠죠? z에 0을 대입함으로써 위 반복이 거짓이 되므로
				   // 무한루프를 벗어납니다.
		}
	} while (k);

	return instance;
}

void turn_empty(LINEINFO target[], int limit) {
	for (int i = 0; i < limit; i++) {
		(target + i)->B = 0;
		(target + i)->W = 0;
	}
}

void linear_empty(LINEARINFO target[], int limit) {
	for (int i = 0; i < limit; i++) {
		(target + i)->number = 0;
		(target + i)->color = 0;
	}
}

void row_linear(TARGET locate[][WIDTH], LINEARINFO r[], int limit) {
	for (int i = 0; i < limit; i++) {
		int sum = 0;
		for (int j = 0; j < WIDTH; j++) {

		}
	}

}