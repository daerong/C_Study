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

void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

typedef enum RESULT { BLACKFOUL = -2, WHITEWIN = -1, DRAW = 0, BLACKWIN, WHITEFOUL } RESULT;
typedef unsigned short unshort;

typedef struct LOCATION {
	int col;
	int row;
} LOCATION;

typedef struct LINEINFO {
	char maxColor;			// white = -1, black = 1
	unshort maxLength;
} LINEINFO;

typedef struct STATUS {
	char stone;				// white = -1, black = 1
	LOCATION location;
	LINEINFO colL;			// →
	LINEINFO rowL;			// ↓
	LINEINFO upL;			// ↗
	LINEINFO downL;			// ↘
	struct STATUS *uLink;
	struct STATUS *dLink;
	struct STATUS *lLink;
	struct STATUS *rLink;
} STATUS;

void print_turn(int turn);
void draw_board(STATUS *board, int turn, LINEINFO StraightCol[], LINEINFO StraightRow[], LINEINFO diagonalUp[], LINEINFO diagonalDown[]);
void reset_lineinfo(LINEINFO target[], int limit);
void null_setting(STATUS *target);
STATUS *setting_board(void);
// void print_board(STATUS *target);			// 테스트용 소스
char *change_stone(char stone);
STATUS *get_position(STATUS *board, int turn);
STATUS *board_status(STATUS **target);
void line_update(STATUS *board, STATUS *target, LINEINFO StraightCol[], LINEINFO StraightRow[], LINEINFO diagonalUp[], LINEINFO diagonalDown[]);
void lets_judgment(RESULT result);

RESULT result = DRAW;

int main() {

	STATUS *board = setting_board();
	int turn = 1;

	LINEINFO StraightCol[HEIGHT];
	reset_lineinfo(StraightCol, HEIGHT);
	LINEINFO StraightRow[WIDTH];
	reset_lineinfo(StraightRow, WIDTH);
	LINEINFO diagonalUp[WIDTH + HEIGHT - 1];
	reset_lineinfo(diagonalUp, WIDTH + HEIGHT - 1);
	LINEINFO diagonalDown[WIDTH + HEIGHT - 1];
	reset_lineinfo(diagonalDown, WIDTH + HEIGHT - 1);

	// print_board(board);						// 테스트용 소스

	do {
		draw_board(board, turn, StraightCol, StraightRow, diagonalUp, diagonalDown);
		line_update(board, get_position(board, turn), StraightCol, StraightRow, diagonalUp, diagonalDown);
		turn++;
	} while (!result);

	lets_judgment(result);

	return 0;
}

void print_turn(int turn) {
	if (turn % 2) {
		printf("%3d번째 턴, ● : %3d, ○ : %3d\n", turn, (turn - 1) / 2, (turn - 1) / 2);
	}
	else {
		printf("%3d번째 턴, ● : %3d, ○ : %3d\n", turn, turn / 2, turn / 2 - 1);
	}
}

void draw_board(STATUS *board, int turn, LINEINFO StraightCol[], LINEINFO StraightRow[], LINEINFO diagonalUp[], LINEINFO diagonalDown[]) {
	STATUS *upperline = board;
	STATUS *data = board;
	system("cls");
	int j;
	print_turn(turn);

	// 바둑판 상단
	printf("        ");
	for (int i = 0; i < WIDTH; i++) { printf("%2d", diagonalUp[i].maxLength); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < WIDTH; i++) { printf("%s", change_stone(diagonalUp[i].maxColor)); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < WIDTH; i++) {
		printf("↗");
	}
	printf("\n");

	// 메인 바둑판
	data = board;

	printf("      ┌─");
	for (int i = 0; i < WIDTH; i++) {
		printf("┬─");
	}
	printf("┐\n");

	j = 0;
	while (upperline != NULL) {
		data = upperline;
		printf("%2d%s→├─", StraightCol[j].maxLength, change_stone(StraightCol[j].maxColor));
		while (data != NULL) {
			if (change_stone(data->stone) == "◐") {
				printf("┼─");
			}
			else {
				printf("%s", change_stone(data->stone));
			}

			data = data->rLink;
		}
		printf("┤↗%s%2d↘%s%2d\n", change_stone(diagonalUp[WIDTH - 1 + j].maxColor), diagonalUp[WIDTH - 1 + j].maxLength, change_stone(diagonalDown[WIDTH - 1 + HEIGHT - 1 - j].maxColor), diagonalDown[WIDTH - 1 + HEIGHT - 1 - j].maxLength);
		upperline = upperline->dLink;
		j++;
	}

	printf("      └─");
	for (int i = 0; i < WIDTH; i++) {
		printf("┴─");
	}
	printf("┘\n");

	// 바둑판 하단
	printf("        ");
	for (int i = 0; i < WIDTH; i++) {
		printf("↘");
	}
	printf("\n");

	printf("        ");
	for (int i = 0; i < WIDTH; i++) { printf("%s", change_stone(diagonalDown[i].maxColor)); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < WIDTH; i++) { printf("%2d", diagonalDown[i].maxLength); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < WIDTH; i++) {
		printf("↓");
	}
	printf("\n");

	printf("        ");
	for (int i = 0; i < WIDTH; i++) { printf("%s", change_stone(StraightRow[i].maxColor)); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < WIDTH; i++) { printf("%2d", StraightRow[i].maxLength); }
	printf("\n");

}

void reset_lineinfo(LINEINFO target[], int limit) {
	for (int i = 0; i < limit; i++) {
		target[i].maxColor = 0;
		target[i].maxLength = 0;
	}
}

void null_setting(STATUS *target) {
	target->stone = 0;
	(target->location).col = 0;
	(target->location).row = 0;
	(target->colL).maxColor = 0;
	(target->colL).maxLength = 0;
	(target->rowL).maxColor = 0;
	(target->rowL).maxLength = 0;
	(target->upL).maxColor = 0;
	(target->upL).maxLength = 0;
	(target->downL).maxColor = 0;
	(target->downL).maxLength = 0;
	target->uLink = NULL;
	target->dLink = NULL;
	target->lLink = NULL;
	target->rLink = NULL;
}

STATUS *setting_board(void) {
	STATUS *init;										// (0, 0)셀
	init = (STATUS *)malloc(sizeof(STATUS));
	null_setting(init);
	(init->location).col = HEIGHT - 1;
	(init->location).row = 0;
	STATUS *data;
	STATUS *prev = init;
	STATUS *upperline;
	for (int i = HEIGHT - 2; i >= 0; i--) {				// 1열 생성 ↑
		data = (STATUS *)malloc(sizeof(STATUS));
		null_setting(data);
		prev->uLink = data;
		data->dLink = prev;
		(data->location).col = i;
		(data->location).row = 0;
		prev = data;
	}

	init = data;										// (0, 0)셀 지정
	prev = init;

	for (int j = 1; j < WIDTH; j++) {					// 1행 생성 →
		data = (STATUS *)malloc(sizeof(STATUS));
		null_setting(data);
		prev->rLink = data;
		data->lLink = prev;
		(data->location).col = 0;
		(data->location).row = j;
		prev = data;
	}

	upperline = init;

	for (int i = 1; i < HEIGHT; i++) {
		prev = upperline->dLink;
		for (int j = 1; j < WIDTH; j++) {
			data = (STATUS *)malloc(sizeof(STATUS));
			null_setting(data);
			prev->rLink = data;
			data->lLink = prev;
			(data->location).col = i;
			(data->location).row = j;
			prev = data;
		}
		upperline = upperline->dLink;
	}

	upperline = init;

	for (int j = 1; j < HEIGHT; j++) {
		prev = upperline->rLink;
		data = (upperline->dLink)->rLink;
		for (int i = 1; i < WIDTH; i++) {
			prev->dLink = data;
			data->uLink = prev;
			prev = prev->rLink;
			data = data->rLink;
		}
		upperline = upperline->dLink;
	}
	return init;
}
/*
void print_board(STATUS *target) {			// 테스트용 소스
STATUS *upperline = target;
STATUS *data = target;
while (upperline != NULL) {
data = upperline;
while (data != NULL) {
printf("%02d, %02d, %p, %p, %p, %p\n", (data->location).col, (data->location).row, data->uLink, data->dLink, data->lLink, data->rLink);
data = data->rLink;
}
upperline = upperline->dLink;
}
}
*/

char *change_stone(char stone) {
	if (stone == -1) return "●";
	else if (stone == 1) return "○";
	else return "◐";
}

STATUS *get_position(STATUS *board, int turn) {
	STATUS *data = board;
	STATUS *target = NULL;
	int k = 1;
	int x = 9, y = 9;
	for (int i = 0; i < x; i++) { data = data->rLink; }
	for (int j = 0; j < y; j++) { data = data->dLink; }
	int cursor_x = 27, cursor_y = 14;
	do {

		int z = _getch(); // char c 변수에 문자를 입력 받는다

		switch (z) {
		case RIGHT:
			++x, cursor_x += 2;
			if (x >= WIDTH) {
				--x, cursor_x -= 2;// 만약 오목판을 넘어선다면 입력이 무시가 됩니다. 
			}
			else data = data->rLink;
			gotoxy(cursor_x, cursor_y); // 아니라면 커서를 입력한 좌표로 이동합니다.
			break; // 그리고 다시 입력을 받기 위해 swtich문을 빠져 나가며 다시 루트가 됩니다.

		case LEFT:
			--x, cursor_x -= 2;
			if (x < 0) {
				++x, cursor_x += 2;
			}
			else data = data->lLink;
			gotoxy(cursor_x, cursor_y);
			break;

		case UP:
			--y, --cursor_y;
			if (y < 0) {
				++y, ++cursor_y;
			}
			else data = data->uLink;
			gotoxy(cursor_x, cursor_y);
			break;

		case DOWN:
			++y, ++cursor_y;
			if (y >= HEIGHT) {
				--y, --cursor_y;
			}
			else data = data->dLink;
			gotoxy(cursor_x, cursor_y);
			break;

		case ENTER:					//ENTER가 입력되면 현재 위치를 오목 배열에 저장
			if (data->stone == 0) {
				if (turn % 2) {
					data->stone = -1;				// status[HEIGHT][WIDTH]에 대입
					target = board_status(&data);
				}
				else {
					data->stone = 1;
					target = board_status(&data);
				}
				k = 0;					// 무한루프를 벗어납니다.
			}
		}
	} while (k);

	return target;
}

STATUS *board_status(STATUS **target) {
	int threeRule = 0;
	(*target)->colL.maxColor = (*target)->stone; 			// →
	(*target)->colL.maxLength += 1;				 			// →
	if ((*target)->lLink != NULL && ((*target)->lLink)->stone == (*target)->stone) {
		(*target)->colL.maxLength += ((*target)->lLink)->colL.maxLength;
		((*target)->lLink)->colL.maxLength += 1;
	}
	if ((*target)->rLink != NULL && ((*target)->rLink)->stone == (*target)->stone) {
		(*target)->colL.maxLength += ((*target)->rLink)->colL.maxLength;
		((*target)->rLink)->colL.maxLength += 1;
	}
	(*target)->rowL.maxColor = (*target)->stone;			// ↓
	(*target)->rowL.maxLength += 1;							// ↓
	if ((*target)->uLink != NULL && ((*target)->uLink)->stone == (*target)->stone) {
		(*target)->rowL.maxLength += ((*target)->uLink)->rowL.maxLength;
		((*target)->uLink)->rowL.maxLength += 1;
	}
	if ((*target)->dLink != NULL && ((*target)->dLink)->stone == (*target)->stone) {
		(*target)->rowL.maxLength += ((*target)->dLink)->rowL.maxLength;;
		((*target)->dLink)->rowL.maxLength += 1;
	}
	(*target)->upL.maxColor = (*target)->stone;				// ↗
	(*target)->upL.maxLength += 1;							// ↗
	if ((*target)->uLink != NULL && (*target)->rLink != NULL && (((*target)->uLink)->rLink)->stone == (*target)->stone) {
		(*target)->upL.maxLength += (((*target)->uLink)->rLink)->upL.maxLength;
		(((*target)->uLink)->rLink)->upL.maxLength += 1;
	}
	if ((*target)->dLink != NULL && (*target)->lLink != NULL && (((*target)->dLink)->lLink)->stone == (*target)->stone) {
		(*target)->upL.maxLength += (((*target)->dLink)->lLink)->upL.maxLength;
		(((*target)->dLink)->lLink)->upL.maxLength += 1;
	}
	(*target)->downL.maxColor = (*target)->stone;			// ↘
	(*target)->downL.maxLength += 1;						// ↘
	if ((*target)->dLink != NULL && (*target)->rLink != NULL && (((*target)->dLink)->rLink)->stone == (*target)->stone) {
		(*target)->downL.maxLength += (((*target)->dLink)->rLink)->downL.maxLength;
		(((*target)->dLink)->rLink)->downL.maxLength += 1;
	}
	if ((*target)->uLink != NULL && (*target)->lLink != NULL && (((*target)->uLink)->lLink)->stone == (*target)->stone) {
		(*target)->downL.maxLength += (((*target)->uLink)->lLink)->downL.maxLength;
		(((*target)->uLink)->lLink)->downL.maxLength += 1;
	}

	if ((*target)->colL.maxLength == 3) { threeRule += 1; }
	if ((*target)->rowL.maxLength == 3) { threeRule += 1; }
	if ((*target)->upL.maxLength == 3) { threeRule += 1; }
	if ((*target)->downL.maxLength == 3) { threeRule += 1; }
	if (threeRule > 1) {
		if ((*target)->stone == -1) { result = WHITEFOUL; }
		else { result = BLACKFOUL; }
	}
	if ((*target)->colL.maxLength >= 5 || (*target)->rowL.maxLength >= 5 || (*target)->upL.maxLength >= 5 || (*target)->downL.maxLength >= 5) {
		if ((*target)->stone == -1) { result = WHITEWIN; }
		else { result = BLACKWIN; }
	}

	return *target;
}

void line_update(STATUS *board, STATUS *target, LINEINFO StraightCol[], LINEINFO StraightRow[], LINEINFO diagonalUp[], LINEINFO diagonalDown[]) {
	STATUS *upperline = board;
	STATUS *data = board;
	int col = (target->location).col;
	int row = (target->location).row;
	int up = col + row;					// ↗
	int down = HEIGHT - 1 - col + row;		// ↘

	while (upperline != NULL) {
		data = upperline;
		while (data != NULL) {
			if ((data->location).col == col) {
				if (StraightCol[col].maxLength < (data->colL).maxLength) { StraightCol[col].maxColor = data->stone; StraightCol[col].maxLength = (data->colL).maxLength; }
				else if (StraightCol->maxLength == (data->colL).maxLength) { StraightCol[col].maxColor = 0; }
			}
			if ((data->location).row == row) {
				if (StraightRow[row].maxLength < (data->rowL).maxLength) { StraightRow[row].maxColor = data->stone; StraightRow[row].maxLength = (data->rowL).maxLength; }
				else if (StraightRow->maxLength == (data->rowL).maxLength) { StraightRow[row].maxColor = 0; }
			}
			if ((data->location).col + (data->location).row == up) {
				if (diagonalUp[up].maxLength < (data->upL).maxLength) { diagonalUp[up].maxColor = data->stone; diagonalUp[up].maxLength = (data->upL).maxLength; }
				else if (diagonalUp->maxLength == (data->upL).maxLength) { diagonalUp[up].maxColor = 0; }
			}
			if (HEIGHT - 1 - (data->location).col + (data->location).row == down) {
				if (diagonalDown[down].maxLength < (data->downL).maxLength) { diagonalDown[down].maxColor = data->stone; diagonalDown[down].maxLength = (data->downL).maxLength; }
				else if (diagonalDown->maxLength == (data->downL).maxLength) { diagonalDown[down].maxColor = 0; }
			}
			data = data->rLink;
		}
		upperline = upperline->dLink;
	}
}

void lets_judgment(RESULT result) {
	system("cls");
	if (result == WHITEFOUL) { printf("백돌의 반칙패\n"); }
	else if (result == WHITEWIN) { printf("백돌의 승리\n"); }
	else if (result == BLACKWIN) { printf("흑돌의 승리\n"); }
	else if (result == BLACKFOUL) { printf("흑돌의 반칙패\n"); }
	else { printf("무승부\n"); }
}