#include <stdio.h>
#include <Windows.h>    // system() 함수를 사용하기 위한 라이브러리
#include <conio.h>		// _getch()
#include <string.h>		// strtok 함수가 선언된 헤더 파일

#define NUMBER 30
#define NAME_SIZE 10

typedef struct CHECK {
	char *A;
	char *B;
	int check;
} CHECK;

int main()
{
	int insert_num;

	CHECK list[NUMBER];

	do {
		scanf("%d", &insert_num);
	} while (insert_num <= 1 || insert_num > 30);

	while (getchar() != '\n');

	char s1[NAME_SIZE*NUMBER];				// 문자열 받을 버퍼
	char s2[NAME_SIZE*NUMBER];

	fgets(s1, sizeof(s1), stdin);
	s1[strlen(s1) - 1] = '\0';

	char *sArr_1[NUMBER] = { NULL, };			// 크기가 10인 문자열 포인터 배열을 선언하고 NULL로 초기화
	int i = 0;								// 문자열 포인터 배열의 인덱스로 사용할 변수

	char *ptr = strtok(s1, " ");			// 공백 문자열을 기준으로 문자열을 자름

	while (ptr != NULL)						// 자른 문자열이 나오지 않을 때까지 반복
	{
		sArr_1[i] = ptr;						// 문자열을 자른 뒤 메모리 주소를 문자열 포인터 배열에 저장
		i++;								// 인덱스 증가

		ptr = strtok(NULL, " ");   // 다음 문자열을 잘라서 포인터를 반환
	}

	fgets(s2, sizeof(s2), stdin);
	s2[strlen(s2) - 1] = '\0';

	char *sArr_2[NUMBER] = { NULL, };			// 크기가 10인 문자열 포인터 배열을 선언하고 NULL로 초기화
	i = 0;									// 문자열 포인터 배열의 인덱스로 사용할 변수

	ptr = strtok(s2, " ");					// 공백 문자열을 기준으로 문자열을 자름

	while (ptr != NULL)						// 자른 문자열이 나오지 않을 때까지 반복
	{
		sArr_2[i] = ptr;						// 문자열을 자른 뒤 메모리 주소를 문자열 포인터 배열에 저장
		i++;								// 인덱스 증가

		ptr = strtok(NULL, " ");			// 다음 문자열을 잘라서 포인터를 반환
	}


	for (int j = 0; j < insert_num; j++) {
		if (sArr_1[j] == NULL || sArr_2[j] == NULL) {
			break;
		}
		list[j].A = sArr_1[j];		// A 문자열
		list[j].B = sArr_2[j];		// B 문자열
	}

	for (int j = 0; j < insert_num; j++) {
		for (int k = 0; k < insert_num; k++) {
			if (*(list[j].B) == *(list[k].A)) {
				if (*(list[k].B) == *(list[j].A)) {
					list[j].check = 1;
				}
			}
		}
	}

	int result = 1;

	for (int j = 0; j < insert_num; j++) {
		if (list[j].check != 1) {
			result = 0;
		}
	}

	if (result == 1) {
		printf("good\n");
	}
	else if (result == 0) {
		printf("bad\n");
	}


	return 0;
}
