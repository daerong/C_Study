#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define SIZE 30

typedef struct LIST {
	char name[SIZE];
	char phone[SIZE];
	struct LIST *link;
} LIST;

int view_list(void);							// 메뉴 선택
void clear_list(LIST **list, LIST **next);		// 1. 초기화
void add_list(LIST **list, LIST **prev);		// 2. 전화 번호 추가
void search_list(LIST **next, LIST **list);		// 3. 전화 번호 탐색
void delete_list(LIST **next, LIST **list);		// 메모리 해제

int main() {
	LIST *info = NULL;
	LIST *prev = NULL;
	LIST *next = NULL;
	int insert = 0;

	while ((insert = view_list()) != 4)		// 4. 종료
	{
		while (getchar() != '\n');			// 버퍼 비우기, fflush 먹통일 때 사용
		system("cls");
		if (insert == 1) {					// 1. 초기화
			clear_list(&info, &next);
		}
		else if (insert == 2) {				// 2. 전화 번호 추가
			add_list(&info, &prev);
		}
		else if (insert == 3) {				// 3. 전화 번호 탐색
			search_list(&next, &info);
		}
		else {								// 예외 처리

		}
	}

	delete_list(&next, &info);				// 메모리 해제
	return 0;
}

int view_list(void) {
	int choice = 0;

	printf("연결 리스트를 이용한 전화 번호부 메뉴\n");
	printf("----------------------------------\n");
	printf("1. 초기화\n");
	printf("2. 전화 번호 추가\n");
	printf("3. 전화 번호 탐색\n");
	printf("4. 종료\n");
	printf("----------------------------------\n");
	printf("번호를 입력하세요 : ");
	scanf("%d", &choice);

	return choice;
}

void clear_list(LIST **list, LIST **next) {	// 1. 초기화
	printf("1. 초기화\n");

	LIST *data;
	data = *list;							// p는 list를 가지고 있음

	while (data != NULL) {					// 리스트가 비어있지 않으면,
		*next = data->link;						// next에 다음 주소 저장
		free(data);							// 현재 주소 삭제
		data = *next;							// p는 다음 데이터를 참조
	}

	next = NULL;
	printf("초기화가 완료되었습니다.\n");
	Sleep(1000);
	system("cls");
}

void add_list(LIST **list, LIST **prev) {	// 2. 전화 번호 추가
	printf("2. 전화번호부 추가\n");

	LIST *data;									// p는 새로 추가할 데이터
	data = (LIST*)malloc(sizeof(LIST));			// 동적메모리 할당

	printf("이름: ");
	gets_s(data->name, sizeof(char)*SIZE);
	printf("번호: ");
	gets_s(data->phone, sizeof(char)*SIZE);
	if (*list == NULL) {						// list가 초기값이면,
		*list = data;								// list가 가리키는 주소에 p를 대입, list는 처음 데이터
	}
	else {										// list에 값이 있으면,
		(*prev)->link = data;						// prev.link에 현주소 대입
	}
	data->link = NULL;							// 마지막에 해당하므로 NULL
	*prev = data;

	system("cls");
}

void search_list(LIST **next, LIST **list) {	// 3. 전화 번호 탐색
	printf("3. 전화 번호 탐색\n");

	LIST *data;									// 순차검색 매개값
	char input[SIZE];
	printf("찾을 이름: ");
	gets_s(input, sizeof(char)*SIZE);
	data = *list;								// 처음을 가져옴

	while (data != NULL) {						// 끝은 항상 NULL					
		if (!(strcmp(data->name, input))) {
			printf("전화 번호는 %s입니다.\n", data->phone);
		}
		*next = data->link;
		data = *next;
	}
	printf("검색을 마쳤습니다.(3초간 확인)\n");
	Sleep(3000);
	system("cls");

	next = NULL;


}

void delete_list(LIST **next, LIST **list) {	// 메모리 해제
	LIST *data;
	data = *list;
	while (data != NULL)						// 초기화와 동일
	{
		*next = data->link;
		free(data);
		data = *next;
	}
}
