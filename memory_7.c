#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define TITLE_SIZE 100

typedef struct MOVIE {
	char title[TITLE_SIZE];
	int premiere;
	struct MOVIE *link;
} MOVIE;

int view_movie(void);								// 메뉴 선택
void add_movie(MOVIE **list, MOVIE **prev);			// 1. 영화 정보 추가
void list_moive(MOVIE **next, MOVIE **list);		// 2. 영화 정보 출력
void delete_movie(MOVIE **next, MOVIE **list);		// 메모리 해제

int main() {
	MOVIE *movie = NULL;
	MOVIE *prev = NULL;			// 연결리스트의 생성에는 '이전' 단계의 링크 값을 바꾸는 과정이 포함된다.
	MOVIE *next = NULL;			// 연결리스트이 순차실행에는 '현'주소를 지우기 전, '다음' 값을 저장해야 한다.
	int choice = 0;

	while ((choice = view_movie()) != 3)		// 3. 종료
	{
		while (getchar() != '\n');				// 버퍼 비우기, fflush 먹통일 때 사용
		system("cls");
		if (choice == 1) {						// 1. 영화 정보 추가
			add_movie(&movie, &prev);
		}
		else if (choice == 2) {					// 2. 영화 정보 출력
			list_moive(&next, &movie);
		}
		else {									// 예외 처리

		}
	}

	delete_movie(&next, &movie);				// 메모리 해제
	return 0;
}

int view_movie(void) {
	int choice = 0;

	printf("연결 리스트를 이용한 전화 번호부 메뉴\n");
	printf("----------------------------------\n");
	printf("1. 영화 정보 추가\n");
	printf("2. 영화 정보 출력\n");
	printf("3. 종료\n");
	printf("----------------------------------\n");
	printf("번호를 선택하시오 : ");
	scanf("%d", &choice);

	return choice;
}

void add_movie(MOVIE **list, MOVIE **prev) {	// 1. 영화 정보 추가
	printf("1. 영화 정보 추가\n");

	MOVIE *data;								// data는 새로 추가할 데이터
	data = (MOVIE*)malloc(sizeof(MOVIE));		// 동적메모리 할당

	printf("영화의 제목을 입력하시오: ");
	gets_s(data->title, sizeof(char)*TITLE_SIZE);
	printf("영화의 개봉 연도를 입력하시오: ");
	scanf("%d", &data->premiere);
	if (*list == NULL) {						// list가 초기상태면,
		*list = data;								// list가 가리키는 주소에 data에 대입, list는 처음 데이터
	}
	else {										// list에 값이 있으면,
		(*prev)->link = data;						// prev.link에 현주소 대입
	}
	data->link = NULL;							// 마지막에 해당하므로 NULL
	*prev = data;

	system("cls");
}

void list_moive(MOVIE **next, MOVIE **list) {	// 2. 영화 정보 출력
	printf("2. 영화 정보 출력\n");

	MOVIE *data;
	data = *list;								// 처음을 가져옴

	while (data != NULL) {						// 끝은 항상 NULL					
		printf("제목 : %s\n", data->title);
		printf("개봉 연도 : %d\n", data->premiere);
		*next = data->link;						// 다음 참조를 넘김
		data = *next;
	}
	printf("검색을 마쳤습니다.(3초간 확인)\n");
	Sleep(3000);
	system("cls");

	next = NULL;


}

void delete_movie(MOVIE **next, MOVIE **list) {	// 메모리 해제
	MOVIE *data;
	data = *list;
	while (data != NULL)
	{
		*next = data->link;
		free(data);
		data = *next;
	}
}
