#include <stdio.h>
#include <stdlib.h>

typedef struct LIST {
	int num;
	struct LIST *link;
} LIST;

LIST *add_list(LIST **list, LIST **prev, int input);	// 데이터 추가
void read_list(LIST **lsit, LIST **next);				// 데이터 참조
void delete_list(LIST **list, LIST **next);				// 메모리 해제

int main() {
	LIST *list = NULL;
	LIST *prev = NULL;
	LIST *next = NULL;
	int input;

	do {
		printf("양의 정수를 입력하세요(종료: -1) : ");
		scanf("%d", &input);
		if (input == -1) { break; }
		add_list(&list, &prev, input);
		//while (getchar() != '\n');			// 버퍼 비우기, fflush 먹통일 때 사용
	} while (1);

	read_list(&list, &next);					// 데이터 참조

	delete_list(&list, &next);					// 메모리 해제
	return 0;
}

LIST *add_list(LIST **list, LIST **prev, int input) {

	LIST *data;									// data는 새로 추가할 데이터
	data = (LIST*)malloc(sizeof(LIST));			// 동적메모리 할당

	data->num = input;
	if (*list == NULL) {						// list가 초기값이면,
		*list = data;								// list가 가리키는 주소에 data를 대입, list는 처음 데이터
	}
	else {										// list에 값이 있으면,
		(*prev)->link = data;						// prev.link에 현주소 대입
	}
	data->link = NULL;							// 마지막에 해당하므로 NULL
	*prev = data;
}

void read_list(LIST **list, LIST **next) {		// 데이터 참조
	LIST *data;
	data = *list;								// 처음을 가져옴

	while (data != NULL) {						// 끝은 항상 NULL					
		printf("%d->", data->num);
		*next = data->link;						// 다음 참조를 넘김
		data = *next;
	}

	printf("NULL\n");

	next = NULL;
}

void delete_list(LIST **list, LIST **next) {	// 메모리 해제
	LIST *data;
	data = *list;
	while (data != NULL)						// 초기화와 동일
	{
		*next = data->link;
		free(data);
		data = *next;
	}
}
