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

void init_setting(BOARD **sample, int row, int col);				// �� �����
void start_infection(BOARD **sample, int row, int col);				// ���̷��� ����
int next_time(BOARD **sample, int row, int col, int time);			// ���̷��� ����


int main() {

	int n, m;					// n = ��(row), m = ��(col)
	BOARD *sample;

	do {
		system("cls");
		scanf("%d", &n);
		scanf("%d", &m);
	} while (n < 5 || n > 100 || m < 5 || m > 100);

	while (getchar() != '\n');				// �Է¹��� ���� ��ġ

	init_setting(&sample, n, m);				// �� �����
	start_infection(&sample, n, m);				// ���̷��� ����

	printf("%d", next_time(&sample, n, m, 0));
	

	return 0;
}

void init_setting(BOARD **sample, int row, int col) {

	BOARD *data;

	data = (BOARD*)malloc(sizeof(BOARD)*col*row);			// �����޸� �Ҵ�
	*sample = data;

	for (int i = 0; i < row*col; i++) {
		if (i < col) {										// ù ��
			(data + i)->u_link = NULL;
			(data + i)->d_link = (data + i + col);
		}
		else if (i >= (row - 1)*col) {						// ������ ��
			(data + i)->u_link = (data + i - col);
			(data + i)->d_link = NULL;
		}
		else {
			(data + i)->u_link = (data + i - col);
			(data + i)->d_link = (data + i + col);
		}
		if (!(i%col)) {										// ù ��
			(data + i)->l_link = NULL;
			(data + i)->r_link = (data + i + 1);
		}
		else if ((i%col) == (col - 1)) {					// ������ ��
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

	int clear = 1;			// ġ�� �Ϸ� 0 = F, 1 = T

	data = (BOARD*)malloc(sizeof(BOARD)*col*row);			// �����޸� �Ҵ�
	memcpy(data, *sample, sizeof(BOARD)*col*row);

	for (int i = 0; i < row*col; i++) {
		if ((*sample + i)->virus == 1) {
			clear = 0;
			sum = 0;

			if (i < col) {										// ù ��	
				if (((*sample + i)->d_link)->virus == 1) { sum += 1; }
			}
			else if (i >= (row - 1)*col) {						// ������ ��
				if (((*sample + i)->u_link)->virus == 1) { sum += 1; }
			}
			else {
				if (((*sample + i)->d_link)->virus == 1) { sum += 1; }
				if (((*sample + i)->u_link)->virus == 1) { sum += 1; }
			}

			if (!(i%col)) {										// ù ��
				if (((*sample + i)->l_link)->virus == 1) { sum += 1; }
			}
			else if ((i%col) == (col - 1)) {					// ������ ��
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