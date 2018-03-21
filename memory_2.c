#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 100

int main() {

	char **A = NULL;		// char A[][]를 가르키는 문자열 배열 포인터
	int arr_size;

	printf("문자열의 개수 : ");
	scanf("%d", &arr_size);

	if ((A = malloc(arr_size * sizeof(int))) != NULL) {		// int **  = (int *)malloc(sizeof(char *))
													// 
		for (int i = 0; i < arr_size; i++) {
			A[i] = (char *)malloc(STR_SIZE);
		}

		printf("%d개의 문자열을 지정할 수 있는 공간이 할당되었습니다.\n", arr_size);

	}


	A[0] = "Think like a man of action and act like man of thought.";
	A[1] = "Courage is very important.Like a muscle, it is strengthened by use.";
	A[2] = "Life is the art of drawing sufficient conclusions from insufficient premises.";
	A[3] = "By doubting we come at the truth.";
	A[4] = "A man that hath no virtue in himself, ever envieth virtue in others.";
	A[5] = "When money speaks, the truth keeps silent.";
	A[6] = "Better the last smile than the first laughter.";
	A[7] = "In the morning of life, work; in the midday, give counsel; in the evening, pray.";
	A[8] = "Painless poverty is better than embittered wealth.";
	A[9] = "A poet is the painter of the soul.";


	for (int i = 0; i < arr_size; i++) {
		printf("원소의 데이터 크기 : %d, 내용 : %s\n", sizeof(A[i]), (char *)A[i]);
	}

	free(A);

	printf("%d\n", sizeof(A));		// 0xddddddd는 NULL 값을 의미 하지만 NULL 또한 4바이트를 가짐

	return 0;
}
