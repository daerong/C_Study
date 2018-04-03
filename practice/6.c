#include <stdio.h>
#include <malloc.h>			// malloc()
#include <string.h>			// memcpy()
#include <Windows.h>		// system()

typedef struct BOARD {
	int virus;
	struct BOARD *u_link;			// up
	struct BOARD *d_link;			// down
	struct BOARD *l_link;			// left
	struct BOARD *r_link;			// right
} BOARD;

void init_setting(BOARD **sample, int row, int col);				// 판 만들기
void start_infection(BOARD **sample, int row, int col);				// 바이러스 감염
int next_time(BOARD **sample, int row, int col, int time);			// 바이러스 제거


int main() {

	int n, m;					// n = 행(row), m = 열(col)
	BOARD *sample;

	do {
		system("cls");
		scanf("%d", &n);
		scanf("%d", &m);
	} while (n < 5 || n > 100 || m < 5 || m > 100);

	while (getchar() != '\n');				// 입력버퍼 비우는 장치

	init_setting(&sample, n, m);				// 판 만들기
	start_infection(&sample, n, m);				// 바이러스 감염

	printf("%d", next_time(&sample, n, m, 0));
	

	return 0;
}

void init_setting(BOARD **sample, int row, int col) {

	BOARD *data;

	data = (BOARD*)malloc(sizeof(BOARD)*col*row);			// 동적메모리 할당
	*sample = data;

	for (int i = 0; i < row*col; i++) {
		if (i < col) {										// 첫 행
			(data + i)->u_link = NULL;
			(data + i)->d_link = (data + i + col);
		}
		else if (i >= (row - 1)*col) {						// 마지막 행
			(data + i)->u_link = (data + i - col);
			(data + i)->d_link = NULL;
		}
		else {
			(data + i)->u_link = (data + i - col);
			(data + i)->d_link = (data + i + col);
		}
		if (!(i%col)) {										// 첫 열
			(data + i)->l_link = NULL;
			(data + i)->r_link = (data + i + 1);
		}
		else if ((i%col) == (col - 1)) {					// 마지막 열
			(data + i)->l_link = (data + i - 1);
			(data + i)->r_link = NULL;
		}
		else {
			(data + i)->l_link = (data + i - 1);
			(data + i)->r_link = (data + i + 1);
		}
	}
}

void start_infection(BOARD **sample, int row, int col) {

	BOARD *data = *sample;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			scanf("%d", &(data + i*col + j)->virus);
		}
	}
}

int next_time(BOARD **sample, int row, int col, int time) {

	BOARD *data;
	int sum;

	int clear = 1;			// 치료 완료 0 = F, 1 = T

	data = (BOARD*)malloc(sizeof(BOARD)*col*row);			// 동적메모리 할당
	memcpy(data, *sample, sizeof(BOARD)*col*row);

	for (int i = 0; i < row*col; i++) {
		if ((*sample + i)->virus == 1) {
			clear = 0;
			sum = 0;

			if (i < col) {										// 첫 행	
				if (((*sample + i)->d_link)->virus == 1) { sum += 1; }
			}
			else if (i >= (row - 1)*col) {						// 마지막 행
				if (((*sample + i)->u_link)->virus == 1) { sum += 1; }
			}
			else {
				if (((*sample + i)->d_link)->virus == 1) { sum += 1; }
				if (((*sample + i)->u_link)->virus == 1) { sum += 1; }
			}

			if (!(i%col)) {										// 첫 열
				if (((*sample + i)->l_link)->virus == 1) { sum += 1; }
			}
			else if ((i%col) == (col - 1)) {					// 마지막 열
				if (((*sample + i)->r_link)->virus == 1) { sum += 1; }
			}
			else {
				if (((*sample + i)->l_link)->virus == 1) { sum += 1; }
				if (((*sample + i)->r_link)->virus == 1) { sum += 1; }
			}

			if (sum > 2) {
				(data + i)->virus = 1;
			}
			else {
				(data + i)->virus = 0;
			}
		}
		else {
			(data + i)->virus = 0;
		}
	}

	memcpy(*sample, data, sizeof(BOARD)*col*row);

	free(data);
	
	if (clear == 1) {
		return time;
	}
	else {
		return next_time(sample, row, col, time + 1);
	}

}