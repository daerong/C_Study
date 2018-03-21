#include <stdio.h>

#define ROWS 10
#define COLS 10

typedef unsigned char pixel;

void trun_binary(pixel s[][COLS], int k) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < ROWS; j++) {
			(s[i][j] < k) ? printf("0 ") : printf("1 ");
		}
		printf("\n");
	}
}

void turn_bw(pixel s[][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < ROWS; j++) {
			s[i][j] = 255 - (int)s[i][j];
			printf("%d", s[i][j]);
		}
		printf("\n");
	}
}


int main() {

	int k;										// 임계값

	pixel image[ROWS][COLS] = {					// 10 X 10 샘플
		{ 103, 104, 105, 106, 107, 108, 109, 110, 101, 102 },	// 0
		{ 107, 108, 109, 110, 101, 102, 103, 104, 105, 106 },	// 1
		{ 103, 107, 108, 109, 110, 101, 104, 105, 106, 102 },	// 2
		{ 103, 104, 105, 106, 107, 108, 109, 110, 101, 102 },	// 3
		{ 108, 103, 104, 105, 106, 107, 109, 110, 101, 102 },	// 4
		{ 103, 104, 105, 106, 107, 108, 109, 110, 101, 102 },	// 5
		{ 107, 108, 109, 110, 101, 102, 103, 104, 105, 106 },	// 6
		{ 103, 104, 105, 106, 107, 108, 109, 110, 101, 102 },	// 7
		{ 103, 104, 105, 110, 106, 107, 108, 109, 101, 102 },	// 8
		{ 107, 108, 109, 110, 101, 102, 103, 104, 105, 106 }	// 9
	};
	/*
		pixel image[ROWS][COLS];
	
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			int insert_color;
			printf("%d행 %d열의 명암값을 입력하세요(0~255) : ", i + 1, j + 1);
			scanf("%d", &insert_color);
			image[i][j] = insert_color;
		}
	}

	*/
	printf("임계값을 입력해주세요(1~255) : ");	// 임계값보다 크거나 같은 경우 255, 작은경우 0
	scanf("%d", &k);

	trun_binary(image, k);
	turn_bw(image);
	trun_binary(image, k);

	return 0;
}