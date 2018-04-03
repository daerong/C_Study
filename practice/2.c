#include <stdio.h>
#include <Windows.h>    // system() 함수를 사용하기 위한 라이브러리
#include <conio.h>		// _getch()
#include <string.h>		// strtok 함수가 선언된 헤더 파일

typedef struct TARGET {
	int num;
	struct TARGET *link;
} TARGET;

TARGET *init_sample(TARGET **prev, int K) {						// 기본 샘플 추가
																// name, hp, mp, speed, range, position, link
	TARGET *init = NULL;
	init = (TARGET*)malloc(sizeof(TARGET));
	init->num = 1;
	*prev = init;

	for (int i = 1; i < K; i++) {
		TARGET *data;											// p는 새로 추가할 데이터
		data = (TARGET*)malloc(sizeof(TARGET));					// 동적메모리 할당
		data->num = i + 1;
		(*prev)->link = data;									// prev.link에 현주소 대입
		data->link = NULL;										// 마지막에 해당하므로 NULL
		*prev = data;											// 다음 순환의 마지막이 된다.
	}

	return init;
}

void Delete(TARGET **next, TARGET **list) {

	TARGET *data, *back = NULL;									// 순차검색 매개값, 이전
	int insert = 0;
	scanf("%d", &insert);

	data = *list;													// 처음을 가져옴

	int i = 1;

	while (data != NULL) {									// 비교 대상이 없다면 실행할 필요 없음    
		if (!(i%insert)) {
			if (data == *list) {									// 맨 앞이 삭제될 경우
				*list = data->link;
				free(data);
			}
			else {
				*next = data->link;									// 삭제할 값이 n이면 n+1의 값을 저장함
				back->link = *next;									// n-1의 링크에 n+1을 연결
				free(data);
				data = *next;
			}
		}
		else {
			back = data;
			*next = data->link;
			data = *next;
		}
		i++;
	}

	next = NULL;
}

void PrintAll(TARGET **list, TARGET **next) {
	TARGET *data;
	data = *list;													// 처음을 가져옴

	while (data != NULL) {											// 끝은 항상 NULL        
																	// name, hp, mp, speed, range, position, link
		printf("%d\n", data->num);

		*next = data->link;											// 다음 참조를 넘김
		data = *next;
	}

	char exit = 0;

	do {
		exit = _getch();
	} while (exit != 13);

	system("cls");

	next = NULL;
}

int main() {

	int K, m;
	TARGET *prev = NULL, *next = NULL;

	do {
		scanf("%d", &K);
	} while (K < 1 || K > 100);

	TARGET *list = init_sample(&prev, K);			// 연결리스트의 처음

	while (getchar() != '\n');

	do {
		scanf("%d", &m);
	} while (m < 1 || m > 10);

	while (getchar() != '\n');

	for (int i = 0; i < m; i++) {
		Delete(&next, &list);
	}

	system("cls");
	PrintAll(&list, &next);


	return 0;
}