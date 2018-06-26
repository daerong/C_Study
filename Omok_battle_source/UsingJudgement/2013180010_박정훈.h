#pragma once

#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<string.h>
#pragma warning(disable:4996)

void check34();
void BlackAttack_2013180010(int *x,int *y);
void WhiteAttack_2013180010(int *x, int *y);
void BlackDefence_2013180010(int x, int y);
void WhiteDefence_2013180010(int x, int y);

typedef struct aaa {
	int x;
	int y;
	double c;
}aaa;

#define SIZE 19
#define WHITE 2
#define BLACK 1
#define EMPTY 0
aaa AI_value = { 0 };

int Scount = 0, i = 0, j = 0, k = 0;
double value[SIZE][SIZE] = { 0 };
char base[SIZE][SIZE] = { 0 };

void WhiteAttack_2013180010(int *x,int *y) {
	check34();
	for (i = 0; i < SIZE; ++i)//search max vlaue
		for (j = 0; j < SIZE; ++j)
			if (value[i][j]>AI_value.c) {
				AI_value.c = value[i][j];
				AI_value.x = j;
				AI_value.y = i;
			}
	if (Scount == 0) {
		AI_value.x = 9;
		AI_value.y = 9;
		AI_value.c = 1;
	}

	else if (base[AI_value.y][AI_value.x] != WHITE && base[AI_value.y][AI_value.x] != BLACK)
		if (Scount % 2 == 1) {
			base[AI_value.y][AI_value.x] = WHITE;
			*x = AI_value.x;
			*y = AI_value.y;
			++Scount;
		}

	AI_value.y = 0;
	AI_value.x = 0;
	AI_value.c = 0;
}
void BlackAttack_2013180010(int *x, int *y) {
	check34();
	for (i = 0; i < SIZE; ++i)//search max vlaue
		for (j = 0; j < SIZE; ++j)
			if (value[i][j]>AI_value.c) {
				AI_value.c = value[i][j];
				AI_value.x = j;
				AI_value.y = i;
			}
	if (Scount == 0) {
		base[9][9] = BLACK;
		*x = 9;
		*y = 9;
		++Scount;
	}

	else if (base[AI_value.y][AI_value.x] != WHITE && base[AI_value.y][AI_value.x] != BLACK)
		if (Scount % 2 == 0) {


			base[AI_value.y][AI_value.x] = BLACK;
			*x = AI_value.x;
			*y = AI_value.y;
			++Scount;
		}

	/*gotoxy(AI_value.x * 2, AI_value.y);
	printf("『");*/
	AI_value.y = 0;
	AI_value.x = 0;
	AI_value.c = 0;
}
void WhiteDefence_2013180010(int x, int y) {
	base[y][x] = BLACK;
	++Scount;
}
void BlackDefence_2013180010(int x, int y) {
	base[y][x] = WHITE;
	++Scount;
}
void check34() {
	for (i = 0; i < SIZE; ++i)
		for (j = 0; j < SIZE; ++j)
			value[i][j] = 0;
	for (i = 0; i < SIZE; ++i)
		for (j = 0; j < SIZE; ++j) {
			if (base[i][j] == BLACK) {// o
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 0.15;
				if ((j + 1) < SIZE &&base[i][j + 1] == EMPTY)
					value[i][j + 1] += 0.15;
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					value[i - 1][j] += 0.15;
				if ((i + 1) < SIZE &&base[i + 1][j] == EMPTY)
					value[i + 1][j] += 0.15;
				if ((j - 1) > -1 && (i - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					value[i - 1][j - 1] += 0.15;
				if ((j - 1) > -1 && (i + 1) < SIZE && base[i + 1][j - 1] == EMPTY)
					value[i + 1][j - 1] += 0.15;
				if ((j + 1) < SIZE && (i - 1) > -1 && base[i - 1][j + 1] == EMPTY)
					value[i - 1][j + 1] += 0.15;
				if ((j + 1) < SIZE && (i + 1) < SIZE && base[i + 1][j + 1] == EMPTY)
					value[i + 1][j + 1] += 0.15;
			}
			//////亜稽
			if (base[i][j] == BLACK &&base[i][j + 1] == BLACK) {////oo
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 0.5;
				if ((j + 2) < SIZE &&base[i][j + 2] == EMPTY)
					value[i][j + 2] += 0.5;
				//// special
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY && base[i][j + 2] == WHITE)
					value[i][j - 1] -= 0.3;
				if ((j + 2) < SIZE &&base[i][j + 2] == EMPTY && base[i][j - 1] == WHITE)
					value[i][j + 2] -= 0.3;

			}

			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == BLACK) { //ししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((j + 3) < SIZE &&base[i][j + 3] == WHITE)
						value[i][j - 1] -= 0.5;
				}
				if ((j + 3) < SIZE &&base[i][j + 3] == EMPTY) {
					value[i][j + 3] += 1.5;
					if ((j - 1) > -1 && base[i][j - 1] == WHITE)
						value[i][j + 3] -= 0.5;
				}
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == EMPTY && base[i][j + 3] == BLACK) {//ししxし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((j + 4) < SIZE &&base[i][j + 4] == WHITE)
						value[i][j - 1] -= 0.5;
				}
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY) {
					value[i][j + 4] += 1.5;
					if ((j - 1) > -1 && base[i][j - 1] == WHITE)
						value[i][j + 4] -= 0.5;
				}
				value[i][j + 2] += 1.5;
				if (((j + 4) < SIZE &&base[i][j + 4] == WHITE) || ((j - 1) > -1 && base[i][j - 1] == WHITE))
					value[i][j + 2] -= 0.5;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == EMPTY&&base[i][j + 2] == BLACK&&base[i][j + 3] == BLACK) {//しxしし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 1.5;
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY)
					value[i][j + 4] += 1.5;
				value[i][j + 1] += 1.5;
				if (((j + 4) < SIZE &&base[i][j + 4] == WHITE) || ((j - 1) > -1 && base[i][j - 1] == WHITE))
					value[i][j + 1] -= 0.5;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == BLACK&&base[i][j + 3] == BLACK) {//しししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 20;
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY)
					value[i][j + 4] += 20;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == BLACK&&base[i][j + 3] == EMPTY&&base[i][j + 4] == BLACK) {//しししxし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 3] += 20;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == BLACK&&base[i][j + 2] == EMPTY&&base[i][j + 3] == BLACK&&base[i][j + 4] == BLACK) {//ししxしし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 2] += 20;
			}
			if (base[i][j] == BLACK&&base[i][j + 1] == EMPTY&&base[i][j + 2] == BLACK&&base[i][j + 3] == BLACK&&base[i][j + 4] == BLACK) {//しxししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 1] += 20;
			}
			////// 室稽
			if (base[i][j] == BLACK &&base[i + 1][j] == BLACK) {////oo
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 0.5;
					if ((i + 2) < SIZE &&base[i + 2][j] == WHITE)
						value[i - 1][j] -= 0.3;
				}
				if ((i + 2) < SIZE &&base[i + 2][j] == EMPTY) {
					value[i + 2][j] += 0.5;
					if ((i - 1) > -1 && base[i - 1][j] == WHITE)
						value[i + 2][j] -= 0.3;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == BLACK) { //ししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 1.5;
					if ((i + 3) < SIZE &&base[i + 3][j] == WHITE)
						value[i - 1][j] -= 0.5;
				}
				if ((i + 3) < SIZE &&base[i + 3][j] == EMPTY) {
					value[i + 3][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == WHITE)
						value[i + 3][j] -= 0.5;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == EMPTY && base[i + 3][j] == BLACK) {//ししxし

				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 1.5;
					if ((i + 4) < SIZE &&base[i + 4][j] == WHITE)
						value[i - 1][j] -= 0.5;
				}
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY) {
					value[i + 4][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == WHITE)
						value[i + 4][j] -= 0.5;
				}
				value[i + 2][j] += 1.5;
				if ((i + 4) < SIZE &&base[i + 4][j] == WHITE)
					value[i + 2][j] -= 0.7;
				if ((i - 1) > -1 && base[i - 1][j] == WHITE)
					value[i + 2][j] -= 0.7;
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == EMPTY&&base[i + 2][j] == BLACK&&base[i + 3][j] == BLACK) {//しxしし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((i + 4) < SIZE &&base[i + 4][j] == WHITE)
						value[i][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY) {
					value[i + 4][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == WHITE)
						value[i + 4][j] -= 0.5;
				}
				value[i + 1][j] += 1.5;
				if ((i + 4) < SIZE &&base[i + 4][j] == WHITE)
					value[i + 1][j] -= 0.5;
				if ((i - 1) > -1 && base[i - 1][j] == WHITE)
					value[i + 1][j] -= 0.5;

			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == BLACK&&base[i + 3][j] == BLACK) {//しししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					value[i - 1][j] += 20;
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY)
					value[i + 4][j] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == BLACK&&base[i + 3][j] == EMPTY&&base[i + 4][j] == BLACK) {//しししxし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 3][j] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == BLACK&&base[i + 2][j] == EMPTY&&base[i + 3][j] == BLACK&&base[i + 4][j] == BLACK) {//ししxしし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 2][j] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j] == EMPTY&&base[i + 2][j] == BLACK&&base[i + 3][j] == BLACK&&base[i + 4][j] == BLACK) {//しxししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 1][j] += 20;
			}
			//////企唖識 1
			if (base[i][j] == BLACK &&base[i + 1][j + 1] == BLACK) {////oo
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 0.5;
					if ((i + 2) < SIZE && (j + 2) < SIZE && base[i + 2][j + 2] == WHITE)
						value[i - 1][j - 1] -= 0.3;
				}
				if ((i + 2) < SIZE && (j + 2) < SIZE && base[i + 2][j + 2] == EMPTY) {
					value[i + 2][j + 2] += 0.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
						value[i + 2][j + 2] -= 0.3;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == BLACK) { //ししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 3) < SIZE && (j + 3) < SIZE &&base[i + 3][j + 3] == WHITE)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 3) < SIZE && (j + 3) < SIZE &&base[i + 3][j + 3] == EMPTY) {
					value[i + 3][j + 3] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
						value[i + 3][j + 3] -= 0.5;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == EMPTY && base[i + 3][j + 3] == BLACK) {//ししxし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == WHITE)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY) {
					value[i + 4][j + 4] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
						value[i + 4][j + 4] -= 0.5;
				}
				value[i + 2][j + 2] += 1.5;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == WHITE)
					value[i + 2][j + 2] -= 0.7;
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
					value[i + 2][j + 2] -= 0.7;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == EMPTY&&base[i + 2][j + 2] == BLACK&&base[i + 3][j + 3] == BLACK) {//しxしし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == WHITE)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY) {
					value[i + 4][j + 4] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
						value[i + 4][j + 4] -= 0.5;
				}
				value[i + 1][j + 1] += 1.5;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == WHITE)
					value[i + 1][j + 1] -= 0.7;
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == WHITE)
					value[i + 1][j + 1] -= 0.7;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == BLACK&&base[i + 3][j + 3] == BLACK) {//しししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					value[i - 1][j - 1] += 20;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY)
					value[i + 4][j + 4] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == BLACK&&base[i + 3][j + 3] == EMPTY&&base[i + 4][j + 4] == BLACK) {//しししxし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 3][j + 3] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == BLACK&&base[i + 2][j + 2] == EMPTY&&base[i + 3][j + 3] == BLACK&&base[i + 4][j + 4] == BLACK) {//ししxしし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 2][j + 2] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j + 1] == EMPTY&&base[i + 2][j + 2] == BLACK&&base[i + 3][j + 3] == BLACK&&base[i + 4][j + 4] == BLACK) {//しxししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 1][j + 1] += 20;
			}
			//////企唖識 2
			if (base[i][j] == BLACK &&base[i + 1][j - 1] == BLACK) {////oo
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 0.5;
					if ((i + 2) < SIZE && (j - 2) > -1 && base[i + 2][j - 2] == WHITE)
						value[i - 1][j + 1] -= 0.3;
				}
				if ((i + 2) < SIZE && (j - 2) > -1 && base[i + 2][j - 2] == EMPTY) {
					value[i + 2][j - 2] += 0.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
						value[i + 2][j - 2] -= 0.3;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == BLACK) { //ししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 3) < SIZE && (j - 3) > -1 && base[i + 3][j - 3] == WHITE)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 3) < SIZE && (j - 3) > -1 && base[i + 3][j - 3] == EMPTY) {
					value[i + 3][j - 3] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == WHITE)
						value[i + 3][j - 3] -= 0.5;
				}
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == EMPTY && base[i + 3][j - 3] == BLACK) {//ししxし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == WHITE)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY) {
					value[i + 4][j - 4] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == WHITE)
						value[i + 4][j - 4] -= 0.5;
				}
				value[i + 2][j - 2] += 1.5;
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == WHITE)
					value[i + 2][j - 2] -= 0.7;
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == WHITE)
					value[i + 2][j - 2] -= 0.7;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == EMPTY&&base[i + 2][j - 2] == BLACK&&base[i + 3][j - 3] == BLACK) {//しxしし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == WHITE)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY) {
					value[i + 4][j - 4] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == WHITE)
						value[i + 4][j - 4] -= 0.5;
				}
				value[i + 1][j - 1] += 1.5;
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == WHITE)
					value[i + 1][j - 1] -= 0.7;
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == WHITE)
					value[i + 1][j - 1] -= 0.7;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == BLACK&&base[i + 3][j - 3] == BLACK) {//しししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					value[i - 1][j + 1] += 20;
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY)
					value[i + 4][j - 4] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == BLACK&&base[i + 3][j - 3] == EMPTY&&base[i + 4][j - 4] == BLACK) {//しししxし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 3][j - 3] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == BLACK&&base[i + 2][j - 2] == EMPTY&&base[i + 3][j - 3] == BLACK&&base[i + 4][j - 4] == BLACK) {//ししxしし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 2][j - 2] += 20;
			}
			if (base[i][j] == BLACK&&base[i + 1][j - 1] == EMPTY&&base[i + 2][j - 2] == BLACK&&base[i + 3][j - 3] == BLACK&&base[i + 4][j - 4] == BLACK) {//しxししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 1][j - 1] += 20;
			}
		}
	for (i = 0; i < SIZE; ++i)
		for (j = 0; j < SIZE; ++j) {
			if (base[i][j] == WHITE) {// o
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 0.1;
				if ((j + 1) < SIZE &&base[i][j + 1] == EMPTY)
					value[i][j + 1] += 0.1;
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					value[i - 1][j] += 0.1;
				if ((i + 1) < SIZE &&base[i + 1][j] == EMPTY)
					value[i + 1][j] += 0.1;
				if ((j - 1) > -1 && (i - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					value[i - 1][j - 1] += 0.1;
				if ((j - 1) > -1 && (i + 1) < SIZE && base[i + 1][j - 1] == EMPTY)
					value[i + 1][j - 1] += 0.1;
				if ((j + 1) < SIZE && (i - 1) > -1 && base[i - 1][j + 1] == EMPTY)
					value[i - 1][j + 1] += 0.1;
				if ((j + 1) < SIZE && (i + 1) < SIZE && base[i + 1][j + 1] == EMPTY)
					value[i + 1][j + 1] += 0.1;
			}
			//////亜稽
			if (base[i][j] == WHITE &&base[i][j + 1] == WHITE) {////oo
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 0.5;
				if ((j + 2) < SIZE &&base[i][j + 2] == EMPTY)
					value[i][j + 2] += 0.5;
				//// special
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY && base[i][j + 2] == BLACK)
					value[i][j - 1] -= 0.3;
				if ((j + 2) < SIZE &&base[i][j + 2] == EMPTY && base[i][j - 1] == BLACK)
					value[i][j + 2] -= 0.3;

			}

			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == WHITE) { //ししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((j + 3) < SIZE &&base[i][j + 3] == BLACK)
						value[i][j - 1] -= 0.5;
				}
				if ((j + 3) < SIZE &&base[i][j + 3] == EMPTY) {
					value[i][j + 3] += 1.5;
					if ((j - 1) > -1 && base[i][j - 1] == BLACK)
						value[i][j + 3] -= 0.5;
				}
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == EMPTY && base[i][j + 3] == WHITE) {//ししxし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((j + 4) < SIZE &&base[i][j + 4] == BLACK)
						value[i][j - 1] -= 0.5;
				}
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY) {
					value[i][j + 4] += 1.5;
					if ((j - 1) > -1 && base[i][j - 1] == BLACK)
						value[i][j + 4] -= 0.5;
				}
				value[i][j + 2] += 1.5;
				if ((j + 4) < SIZE &&base[i][j + 4] == BLACK)
					value[i][j + 2] -= 0.7;
				if ((j - 1) > -1 && base[i][j - 1] == BLACK)
					value[i][j + 2] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == EMPTY&&base[i][j + 2] == WHITE&&base[i][j + 3] == WHITE) {//しxしし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((j + 4) < SIZE &&base[i][j + 4] == BLACK)
						value[i][j - 1] -= 0.5;
				}
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY) {
					value[i][j + 4] += 1.5;
					if ((j - 1) > -1 && base[i][j - 1] == BLACK)
						value[i][j + 4] -= 0.5;
				}
				value[i][j + 1] += 1.5;
				if ((j + 4) < SIZE &&base[i][j + 4] == BLACK)
					value[i][j + 1] -= 0.7;
				if ((j - 1) > -1 && base[i][j - 1] == BLACK)
					value[i][j + 1] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == WHITE&&base[i][j + 3] == WHITE) {//しししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					value[i][j - 1] += 20;
				if ((j + 4) < SIZE &&base[i][j + 4] == EMPTY)
					value[i][j + 4] += 20;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == WHITE&&base[i][j + 3] == EMPTY&&base[i][j + 4] == WHITE) {//しししxし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 3] += 20;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == WHITE&&base[i][j + 2] == EMPTY&&base[i][j + 3] == WHITE&&base[i][j + 4] == WHITE) {//ししxしし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 2] += 20;
			}
			if (base[i][j] == WHITE&&base[i][j + 1] == EMPTY&&base[i][j + 2] == WHITE&&base[i][j + 3] == WHITE&&base[i][j + 4] == WHITE) {//しxししし
				if ((j - 1) > -1 && base[i][j - 1] == EMPTY)
					--value[i][j - 1];
				if ((j + 5) < SIZE &&base[i][j + 5] == EMPTY)
					--value[i][j + 5];
				value[i][j + 1] += 20;
			}
			////// 室稽
			if (base[i][j] == WHITE &&base[i + 1][j] == WHITE) {////oo
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 0.5;
					if ((i + 2) < SIZE &&base[i + 2][j] == BLACK)
						value[i - 1][j] -= 0.3;
				}
				if ((i + 2) < SIZE &&base[i + 2][j] == EMPTY) {
					value[i + 2][j] += 0.5;
					if ((i - 1) > -1 && base[i - 1][j] == BLACK)
						value[i + 2][j] -= 0.3;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == WHITE) { //ししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 1.5;
					if ((i + 3) < SIZE &&base[i + 3][j] == BLACK)
						value[i - 1][j] -= 0.5;
				}
				if ((i + 3) < SIZE &&base[i + 3][j] == EMPTY) {
					value[i + 3][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == BLACK)
						value[i + 3][j] -= 0.5;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == EMPTY && base[i + 3][j] == WHITE) {//ししxし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i - 1][j] += 1.5;
					if ((i + 4) < SIZE &&base[i + 4][j] == BLACK)
						value[i - 1][j] -= 0.5;
				}
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY) {
					value[i + 4][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == BLACK)
						value[i + 4][j] -= 0.5;
				}
				value[i + 2][j] += 1.5;
				if ((i + 4) < SIZE &&base[i + 4][j] == BLACK)
					value[i + 2][j] -= 0.7;
				if ((i - 1) > -1 && base[i - 1][j] == BLACK)
					value[i + 2][j] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == EMPTY&&base[i + 2][j] == WHITE&&base[i + 3][j] == WHITE) {//しxしし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY) {
					value[i][j - 1] += 1.5;
					if ((i + 4) < SIZE &&base[i + 4][j] == BLACK)
						value[i][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY) {
					value[i + 4][j] += 1.5;
					if ((i - 1) > -1 && base[i - 1][j] == BLACK)
						value[i + 4][j] -= 0.5;
				}
				value[i + 1][j] += 1.5;
				if ((i + 4) < SIZE &&base[i + 4][j] == BLACK)
					value[i + 1][j] -= 0.7;
				if ((i - 1) > -1 && base[i - 1][j] == BLACK)
					value[i + 1][j] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == WHITE&&base[i + 3][j] == WHITE) {//しししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					value[i - 1][j] += 20;
				if ((i + 4) < SIZE &&base[i + 4][j] == EMPTY)
					value[i + 4][j] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == WHITE&&base[i + 3][j] == EMPTY&&base[i + 4][j] == WHITE) {//しししxし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 3][j] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == WHITE&&base[i + 2][j] == EMPTY&&base[i + 3][j] == WHITE&&base[i + 4][j] == WHITE) {//ししxしし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 2][j] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j] == EMPTY&&base[i + 2][j] == WHITE&&base[i + 3][j] == WHITE&&base[i + 4][j] == WHITE) {//しxししし
				if ((i - 1) > -1 && base[i - 1][j] == EMPTY)
					--value[i - 1][j];
				if ((i + 5) < SIZE &&base[i + 5][j] == EMPTY)
					--value[i + 5][j];
				value[i + 1][j] += 20;
			}
			//////企唖識 1
			if (base[i][j] == WHITE &&base[i + 1][j + 1] == WHITE) {////oo
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 0.5;
					if ((i + 2) < SIZE && (j + 2) < SIZE && base[i + 2][j + 2] == BLACK)
						value[i - 1][j - 1] -= 0.3;
				}
				if ((i + 2) < SIZE && (j + 2) < SIZE && base[i + 2][j + 2] == EMPTY) {
					value[i + 2][j + 2] += 0.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
						value[i + 2][j + 2] -= 0.3;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == WHITE) { //ししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 3) < SIZE && (j + 3) < SIZE &&base[i + 3][j + 3] == BLACK)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 3) < SIZE && (j + 3) < SIZE &&base[i + 3][j + 3] == EMPTY) {
					value[i + 3][j + 3] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
						value[i + 3][j + 3] -= 0.5;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == EMPTY && base[i + 3][j + 3] == WHITE) {//ししxし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == BLACK)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY) {
					value[i + 4][j + 4] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
						value[i + 4][j + 4] -= 0.5;
				}
				value[i + 2][j + 2] += 1.5;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == BLACK)
					value[i + 2][j + 2] -= 0.7;
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
					value[i + 2][j + 2] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == EMPTY&&base[i + 2][j + 2] == WHITE&&base[i + 3][j + 3] == WHITE) {//しxしし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY) {
					value[i - 1][j - 1] += 1.5;
					if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == BLACK)
						value[i - 1][j - 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY) {
					value[i + 4][j + 4] += 1.5;
					if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
						value[i + 4][j + 4] -= 0.5;
				}
				value[i + 1][j + 1] += 1.5;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == BLACK)
					value[i + 1][j + 1] -= 0.7;
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == BLACK)
					value[i + 1][j + 1] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == WHITE&&base[i + 3][j + 3] == WHITE) {//しししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					value[i - 1][j - 1] += 20;
				if ((i + 4) < SIZE && (j + 4) < SIZE &&base[i + 4][j + 4] == EMPTY)
					value[i + 4][j + 4] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == WHITE&&base[i + 3][j + 3] == EMPTY&&base[i + 4][j + 4] == WHITE) {//しししxし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 3][j + 3] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == WHITE&&base[i + 2][j + 2] == EMPTY&&base[i + 3][j + 3] == WHITE&&base[i + 4][j + 4] == WHITE) {//ししxしし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 2][j + 2] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j + 1] == EMPTY&&base[i + 2][j + 2] == WHITE&&base[i + 3][j + 3] == WHITE&&base[i + 4][j + 4] == WHITE) {//しxししし
				if ((i - 1) > -1 && (j - 1) > -1 && base[i - 1][j - 1] == EMPTY)
					--value[i - 1][j - 1];
				if ((i + 5) < SIZE && (j + 5) < SIZE &&base[i + 5][j + 5] == EMPTY)
					--value[i + 5][j + 5];
				value[i + 1][j + 1] += 20;
			}
			//////企唖識 2
			if (base[i][j] == WHITE &&base[i + 1][j - 1] == WHITE) {////oo
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 0.5;
					if ((i + 2) < SIZE && (j - 2) > -1 && base[i + 2][j - 2] == BLACK)
						value[i - 1][j + 1] -= 0.3;
				}
				if ((i + 2) < SIZE && (j - 2) > -1 && base[i + 2][j - 2] == EMPTY) {
					value[i + 2][j - 2] += 0.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == BLACK)
						value[i + 2][j - 2] -= 0.3;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == WHITE) { //ししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 3) < SIZE && (j - 3) > -1 && base[i + 3][j - 3] == BLACK)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 3) < SIZE && (j - 3) > -1 && base[i + 3][j - 3] == EMPTY) {
					value[i + 3][j - 3] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == BLACK)
						value[i + 3][j - 3] -= 0.5;
				}
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == EMPTY && base[i + 3][j - 3] == WHITE) {//ししxし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == BLACK)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY) {
					value[i + 4][j - 4] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == BLACK)
						value[i + 4][j - 4] -= 0.5;
				}
				value[i + 2][j - 2] += 1.5;
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == BLACK)
					value[i + 2][j - 2] -= 0.7;
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == BLACK)
					value[i + 2][j - 2] -= 0.7;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == EMPTY&&base[i + 2][j - 2] == WHITE&&base[i + 3][j - 3] == WHITE) {//しxしし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY) {
					value[i - 1][j + 1] += 1.5;
					if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == BLACK)
						value[i - 1][j + 1] -= 0.5;
				}
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY) {
					value[i + 4][j - 4] += 1.5;
					if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == BLACK)
						value[i + 4][j - 4] -= 0.5;
				}
				value[i + 1][j - 1] += 1.5;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == WHITE&&base[i + 3][j - 3] == WHITE) {//しししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					value[i - 1][j + 1] += 20;
				if ((i + 4) < SIZE && (j - 4) > -1 && base[i + 4][j - 4] == EMPTY)
					value[i + 4][j - 4] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == WHITE&&base[i + 3][j - 3] == EMPTY&&base[i + 4][j - 4] == WHITE) {//しししxし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 3][j - 3] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == WHITE&&base[i + 2][j - 2] == EMPTY&&base[i + 3][j - 3] == WHITE&&base[i + 4][j - 4] == WHITE) {//ししxしし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 2][j - 2] += 20;
			}
			if (base[i][j] == WHITE&&base[i + 1][j - 1] == EMPTY&&base[i + 2][j - 2] == WHITE&&base[i + 3][j - 3] == WHITE&&base[i + 4][j - 4] == WHITE) {//しxししし
				if ((i - 1) > -1 && (j + 1) < SIZE && base[i - 1][j + 1] == EMPTY)
					--value[i - 1][j + 1];
				if ((i + 5) < SIZE && (j - 5) > -1 && base[i + 5][j - 5] == EMPTY)
					--value[i + 5][j - 5];
				value[i + 1][j - 1] += 20;
			}
		}
}