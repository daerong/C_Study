#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

/*
추가할 것
1. BOARD의 max 값을 업데이트 하는 함수
2. BOARD의 각 돌의 상태를 읽어 라인 별 최대 연속인 점을 업데이트 하는 함수
3. draw_board에서 값을 copy한 뒤 돌의 상태를 ★, ☆로 업데이트 후 뿌려주는 코드 추가
4. ★, ☆ 근처의 type == 0인 점에는 돌을 놓으라는 표시 활성화
*/

#define BOARD_SIZE 19
#define BUF_SIZE 255

#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESCAPE 27
#define OPENBRACKET 91
#define CLOSEBRACKET 93

// 모양 기호 ◐, ● ,○, ★, ☆
// 방향 기호 →, ↓, ↗, ↘
// 격자 기호 ┌─, ┬─, ┐, ├─, ┼─, ┤, └─, ┴─, ┘

typedef struct STONE_AND_MAX {
	int type;
	int max;
} STONE_AND_MAX;

typedef struct LINE_STATUS {
	STONE_AND_MAX col[BOARD_SIZE];	// →
	STONE_AND_MAX row[BOARD_SIZE];	// ↓
	STONE_AND_MAX up[2 * BOARD_SIZE - 1];	// ↗
	STONE_AND_MAX down[2 * BOARD_SIZE - 1];	// ↘
} LINE_STATUS;

typedef struct GAME_BOARD {
	int type;		// ◐ = 0, ● = 1 ,○ = 2, ★ = 3, ☆ = 4
	int col;
	int row;
	int turn;
	int colMax;
	int rowMax;
	int upMax;
	int downMax;
} GAME_BOARD;

const GAME_BOARD RETURN_MENU = { 0, 20, 20, 0, 0 };

void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void add_stone(GAME_BOARD list[][BOARD_SIZE], GAME_BOARD target) {
	list[target.col][target.row].type = target.type;
	list[target.col][target.row].turn = target.turn;
}

char *int_to_stone(int type) {
	if (type == 1) return "●";
	else if (type == 2) return "○";
	else return "◐";
}

void draw_board(GAME_BOARD locate[][BOARD_SIZE], LINE_STATUS *line_stat) {
	system("cls");

	// 바둑판 상단
	printf("        ");
	for (int i = 0; i < BOARD_SIZE; i++) { printf("%2d", line_stat->up[i].max); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < BOARD_SIZE; i++) { printf("%s", int_to_stone(line_stat->up[i].type)); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf("↗");
	}
	printf("\n");


	// 윗줄 격자 생성
	printf("      ┌─");
	for (int j = 0; j < BOARD_SIZE; j++) {
		printf("┬─");
	}
	printf("┐\n");

	// 메인 바둑판
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf("%2d%s→├─", line_stat->col[i].max, int_to_stone(line_stat->col[i].type));
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (locate[i][j].type == 1) { printf("●"); }
			else if (locate[i][j].type == 2) { printf("○"); }
			else {
				if ((i != 0 && (locate[i - 1][j].rowMax == 3 || locate[i - 1][j].rowMax == 4))) { printf("▣"); }
				else if ((i != BOARD_SIZE - 1 && (locate[i + 1][j].rowMax == 3 || locate[i + 1][j].rowMax == 4))) { printf("▣"); }
				else if ((j != BOARD_SIZE - 1 && (locate[i][j - 1].colMax == 3 || locate[i][j - 1].colMax == 4))) { printf("▣"); }
				else if ((i != BOARD_SIZE - 1 && (locate[i][j + 1].colMax == 3 || locate[i][j + 1].colMax == 4))) { printf("▣"); }
				else if (((j != 0 && i != BOARD_SIZE - 1) && (locate[i + 1][j - 1].upMax == 3 || locate[i + 1][j - 1].upMax == 4))) { printf("▣"); }
				else if (((i != 0 && j != BOARD_SIZE - 1) && (locate[i - 1][j + 1].upMax == 3 || locate[i - 1][j + 1].upMax == 4))) { printf("▣"); }

				else if (((j != 0  && i != 0) && (locate[i - 1][j - 1].downMax == 3 || locate[i - 1][j - 1].downMax == 4))) { printf("▣"); }
				else if (((i != BOARD_SIZE - 1 && i != BOARD_SIZE - 1)&& (locate[i + 1][j + 1].downMax == 3 || locate[i][j + 1].downMax == 4))) { printf("▣"); }
				else { printf("┼─"); }
			}
		}
		printf("┤↗%s%2d↘%s%2d\n", int_to_stone(line_stat->up[BOARD_SIZE - 1 + i].type), line_stat->up[BOARD_SIZE - 1 + i].max, int_to_stone(line_stat->down[2 * BOARD_SIZE - 2 - i].type), line_stat->down[2 * BOARD_SIZE - 2 - i].max);
	}

	// 아래줄 격자 생성
	printf("      └─");
	for (int j = 0; j < BOARD_SIZE; j++) {
		printf("┴─");
	}
	printf("┘\n");

	// 바둑판 하단

	printf("        ");
	for (int i = 0; i < BOARD_SIZE; i++) { printf("↘"); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < BOARD_SIZE; i++) { printf("%s", int_to_stone(line_stat->down[i].type)); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < BOARD_SIZE; i++) { printf("%2d", line_stat->down[i].max); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < BOARD_SIZE; i++) { printf("↓"); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < BOARD_SIZE; i++) { printf("%s", int_to_stone(line_stat->row[i].type)); }
	printf("\n");

	printf("        ");
	for (int i = 0; i < BOARD_SIZE; i++) { printf("%2d", line_stat->row[i].max); }
	printf("\n");

}
GAME_BOARD get_position(GAME_BOARD board[][BOARD_SIZE], int *turn) {
	GAME_BOARD took_stone;
	int end = 1;
	int x = 9, y = 9;					// 좌표
	int cursor_x = 27, cursor_y = 13;	// 화면에 보이는 위치
	do {
		int z = _getch(); // char c 변수에 문자를 입력 받는다

		switch (z) {
		case RIGHT:
			++x, cursor_x += 2;
			if (x >= BOARD_SIZE) --x, cursor_x -= 2;	// 만약 오목판을 넘어선다면 입력이 무시가 됩니다. 
			gotoxy(cursor_x, cursor_y); // 아니라면 커서를 입력한 좌표로 이동합니다.
			break; // 그리고 다시 입력을 받기 위해 swtich문을 빠져 나가며 다시 루트가 됩니다.

		case LEFT:
			--x, cursor_x -= 2;
			if (x < 0) ++x, cursor_x += 2;
			gotoxy(cursor_x, cursor_y);
			break;

		case UP:
			--y, --cursor_y;
			if (y < 0) ++y, ++cursor_y;
			gotoxy(cursor_x, cursor_y);
			break;

		case DOWN:
			++y, ++cursor_y;
			if (y >= BOARD_SIZE) --y, --cursor_y;
			gotoxy(cursor_x, cursor_y);
			break;

		case ENTER:					//ENTER가 입력되면 현재 위치를 오목 배열에 저장
			if (board[y][x].type == 0) {
				if (*turn % 2) {
					board[y][x].type = 2;				// status[HEIGHT][WIDTH]에 대입
				}
				else {
					board[y][x].type = 1;
				}
				board[y][x].turn = *turn;
				(*turn)++;
				took_stone = board[y][x];
				end = 0;					// 무한루프를 벗어납니다.
			}
			break;
		}
	} while (end);

	return took_stone;
}

void list_setting(GAME_BOARD list[][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			list[i][j].type = 0;
			list[i][j].col = i;
			list[i][j].row = j;
			list[i][j].turn = 0;
			list[i][j].colMax = 0;
			list[i][j].rowMax = 0;
			list[i][j].upMax = 0;
			list[i][j].downMax = 0;
		}
	}
}

void line_setting(LINE_STATUS *line_stat) {
	for (int i = 0; i < BOARD_SIZE; i++) {		// 0~18
		line_stat->col[i].max = 0;
		line_stat->col[i].type = 0;
	}
	for (int i = 0; i < BOARD_SIZE; i++) {
		line_stat->row[i].max = 0;
		line_stat->row[i].type = 0;
	}
	for (int i = 0; i < 2 * BOARD_SIZE; i++) {		// 0~37
		line_stat->up[i].max = 0;
		line_stat->up[i].type = 0;
	}
	for (int i = 0; i < 2 * BOARD_SIZE; i++) {
		line_stat->down[i].max = 0;
		line_stat->down[i].type = 0;
	}
}

void max_update(GAME_BOARD list[BOARD_SIZE][BOARD_SIZE], GAME_BOARD *list_stone, LINE_STATUS *line_stat) {
	int color;
	int iCol = list_stone->col;
	int iRow = list_stone->row;
	int iUp = list_stone->col + list_stone->row;
	int iDown = BOARD_SIZE - list_stone->col + list_stone->row - 1;
	int left, right, arrow, status;		// arrow 비교할 돌, status 중간에 비었는지 체크
	int max;

	// Col check
	max = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (list[iCol][i].type != 0) {
			color = list[iCol][i].type;

			left = 1;
			arrow = i;
			status = 0;
			while (arrow < BOARD_SIZE) {
				arrow++;
				if (list[iCol][arrow].type == color) left++;
				else break;
			}
			arrow = i;
			status = 1;
			while (arrow > 0 && status >= 0) {
				arrow--;
				if (list[iCol][arrow].type == color) left++;
				else if (list[iCol][arrow].type == 0) status--;
				else break;
			}

			right = 1;
			arrow = i;
			status = 0;
			while (arrow > 0) {
				arrow--;
				if (list[iCol][arrow].type == color) right++;
				else break;
			}
			arrow = i;
			status = 1;
			while (arrow < BOARD_SIZE && status >= 0) {
				arrow++;
				if (list[iCol][arrow].type == color) right++;
				else if (list[iCol][arrow].type == 0) status--;
				else break;
			}

			if (left >= right) list[iCol][i].colMax = left;
			else list[iCol][i].colMax = right;
		}
		if (max < list[iCol][i].colMax) {
			max = list[iCol][i].colMax;
		}
	}
	line_stat->col[iCol].max = max;

	// Row check
	max = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (list[i][iRow].type != 0) {
			color = list[i][iRow].type;

			left = 1;
			arrow = i;
			status = 0;
			while (arrow < BOARD_SIZE - 1) {
				arrow++;
				if (list[arrow][iRow].type == color) left++;
				else break;
			}
			arrow = i;
			status = 1;
			while (arrow > 0 && status >= 0) {
				arrow--;
				if (list[arrow][iRow].type == color) left++;
				else if (list[arrow][iRow].type == 0) status--;
				else break;
			}

			right = 1;
			arrow = i;
			status = 0;
			while (arrow > 0) {
				arrow--;
				if (list[arrow][iRow].type == color) right++;
				else break;
			}
			arrow = i;
			status = 1;
			while (arrow < BOARD_SIZE - 1 && status >= 0) {
				arrow++;
				if (list[arrow][iRow].type == color) right++;
				else if (list[arrow][iRow].type == 0) status--;
				else break;
			}

			if (left >= right) list[i][iRow].rowMax = left;
			else list[i][iRow].rowMax = right;

		}
		if (max < list[i][iRow].rowMax) {
			max = list[i][iRow].rowMax;
		}
	}
	line_stat->row[iRow].max = max;

	// Up check
	int CpR = iRow + iCol;		// Up[col+row]
	max = 0;
	if (CpR < BOARD_SIZE) {		// 0 ~ 18	Up[col+row]	
		for (int i = 0; i <= CpR; i++) {
			if (list[CpR - i][i].type != 0) {
				color = list[CpR - i][i].type;

				left = 1;
				arrow = i;
				status = 0;
				while (arrow < CpR) {
					arrow++;
					if (list[CpR - arrow][arrow].type == color) left++;
					else break;
				}
				arrow = i;
				status = 1;
				while (arrow > 0 && status >= 0) {
					arrow--;
					if (list[CpR - arrow][arrow].type == color) left++;
					else if (list[CpR - arrow][arrow].type == 0) status--;
					else break;
				}

				right = 1;
				arrow = i;
				status = 0;
				while (arrow > 0) {
					arrow--;
					if (list[CpR - arrow][arrow].type == color) right++;
					else break;
				}
				arrow = i;
				status = 1;
				while (arrow < CpR && status >= 0) {
					arrow++;
					if (list[CpR - arrow][arrow].type == color) right++;
					else if (list[CpR - arrow][arrow].type == 0) status--;
					else break;
				}

				if (left >= right) list[CpR - i][i].upMax = left;
				else list[CpR - i][i].upMax = right;

			}
			if (max < list[CpR - i][i].upMax) {
				max = list[CpR - i][i].upMax;
			}
		}
		line_stat->up[CpR].max = max;
	}
	else {		// 19 ~ 36	Up[col+row]	
		for (int i = CpR + 1 - BOARD_SIZE; i < BOARD_SIZE; i++) {
			if (list[CpR - i][i].type != 0) {
				color = list[CpR - i][i].type;

				left = 1;
				arrow = i;
				status = 0;
				while (arrow < BOARD_SIZE) {
					arrow++;
					if (list[CpR - arrow][arrow].type == color) left++;
					else break;
				}
				arrow = i;
				status = 1;
				while (arrow > CpR + 1 - BOARD_SIZE && status >= 0) {
					arrow--;
					if (list[CpR - arrow][arrow].type == color) left++;
					else if (list[CpR - arrow][arrow].type == 0) status--;
					else break;
				}

				right = 1;
				arrow = i;
				status = 0;
				while (arrow > CpR + 1 - BOARD_SIZE) {
					arrow--;
					if (list[CpR - arrow][arrow].type == color) right++;
					else break;
				}
				arrow = i;
				status = 1;
				while (arrow < BOARD_SIZE && status >= 0) {
					arrow++;
					if (list[CpR - arrow][arrow].type == color) right++;
					else if (list[CpR - arrow][arrow].type == 0) status--;
					else break;
				}

				if (left >= right) list[CpR - i][i].upMax = left;
				else list[CpR - i][i].upMax = right;

			}
			if (max < list[CpR - i][i].upMax) {
				max = list[CpR - i][i].upMax;
			}
		}
		line_stat->up[CpR].max = max;
	}

	// Down check
	int CmR = iCol - iRow;		// Up[col-row]
	int RmC = iRow - iCol;
	max = 0;
	if (CmR >= 0) {		// 0 ~ 18	Up[col-row]	
		for (int i = 0; i < BOARD_SIZE - CmR; i++) {
			if (list[CmR + i][i].type != 0) {
				color = list[CmR + i][i].type;

				left = 1;
				arrow = i;
				status = 0;
				while (arrow < BOARD_SIZE - 1 - CmR) {
					arrow++;
					if (list[CmR + arrow][arrow].type == color) left++;
					else break;
				}
				arrow = i;
				status = 1;
				while (arrow > 0 && status >= 0) {
					arrow--;
					if (list[CmR + arrow][arrow].type == color) left++;
					else if (list[CmR + arrow][arrow].type == 0) status--;
					else break;
				}

				right = 1;
				arrow = i;
				status = 0;
				while (arrow > 0) {
					arrow--;
					if (list[CmR + arrow][arrow].type == color) right++;
					else break;
				}
				arrow = i;
				status = 1;
				while (arrow < BOARD_SIZE - 1 - CmR && status >= 0) {
					arrow++;
					if (list[CmR + arrow][arrow].type == color) right++;
					else if (list[CmR + arrow][arrow].type == 0) status--;
					else break;
				}

				if (left >= right) list[CmR + i][i].downMax = left;
				else list[CmR + i][i].downMax = right;

			}
			if (max < list[CmR + i][i].downMax) {
				max = list[CmR + i][i].downMax;
			}
		}
		line_stat->down[BOARD_SIZE - 1 - CmR].max = max;
	}
	else {		// 19 ~ 36	Down[col-row]	
		for (int i = RmC; i < BOARD_SIZE; i++) {
			if (list[i - RmC][i].type != 0) {
				color = list[i - RmC][i].type;

				left = 1;
				arrow = i;
				status = 0;
				while (arrow < BOARD_SIZE - 1) {
					arrow++;
					if (list[arrow - RmC][arrow].type == color) left++;
					else break;
				}
				arrow = i;
				status = 1;
				while (arrow > RmC && status >= 0) {
					arrow--;
					if (list[arrow - RmC][arrow].type == color) left++;
					else if (list[arrow - RmC][arrow].type == 0) status--;
					else break;
				}

				right = 1;
				arrow = i;
				status = 0;
				while (arrow > RmC) {
					arrow--;
					if (list[arrow - RmC][arrow].type == color) right++;
					else break;
				}
				arrow = i;
				status = 1;
				while (arrow < BOARD_SIZE - 1 && status >= 0) {
					arrow++;
					if (list[arrow - RmC][arrow].type == color) right++;
					else if (list[arrow - RmC][arrow].type == 0) status--;
					else break;
				}

				if (left >= right) list[i - RmC][i].downMax = left;
				else list[i - RmC][i].downMax = right;

			}
			if (max < list[i - RmC][i].downMax) {
				max = list[i - RmC][i].downMax;
			}
		}
		line_stat->down[BOARD_SIZE - 1 + RmC].max = max;
	}


	// next up, down

}

int main() {
	int choiceMenu = 0;
	int	catchMenu = 0;
	int turn = 1;
	GAME_BOARD list[BOARD_SIZE][BOARD_SIZE];
	GAME_BOARD last_stone;
	LINE_STATUS *line_stat = (LINE_STATUS *)malloc(sizeof(LINE_STATUS));
	list_setting(list);
	line_setting(line_stat);

	do {
		draw_board(list, line_stat);							// 바둑판 그리기
		last_stone = get_position(list, &turn);
		max_update(list, &last_stone, line_stat);
	} while (1);		// !!승리조건으로 갱신하기

	free(line_stat);
	return 0;
}