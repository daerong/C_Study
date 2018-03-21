#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// strcpy() 등 문자열 처리함수 사용하기 위한 라이브러리

#define NAME_SIZE 12
#define PHONE_SIZE 28

typedef struct book {
	char *name;
	char *phone;
} BOOK;


int main() {

	BOOK *A;		// BOOK 배열 포인터 생성
	int arr_size;

	printf("주소의 개수 : ");
	scanf("%d", &arr_size);

	while (getchar() != '\n');		// fflush(stdin)이 동작하지 않아 이렇게 처리, getchar() 한 개의 문자를 입력받음
	// getchar()을 계속 읽어들여 처음나오는 \n을 찾아 그 다음 문장을 넘김, 엔터 전까지면 모든 버퍼를 비워낼 수 있다.

	if ((A = malloc(arr_size * sizeof(BOOK))) != NULL) {		// int **  = (int *)malloc(sizeof(char *))
		for (int i = 0; i < arr_size; i++) {
			(A + i)->name = (char *)malloc(NAME_SIZE);
			(A + i)->phone = (char *)malloc(PHONE_SIZE);
		}
		printf("%d개의 주소를 저장할 수 있는 공간이 할당되었습니다.\n", arr_size);

	}
	for (int i = 0; i < arr_size; i++) {
		char buffer_name[NAME_SIZE];
		char buffer_phone[PHONE_SIZE];

		printf("이름을 입력하시오 : ");
		gets_s(buffer_name, sizeof(buffer_name));
		strcpy((A + i)->name, buffer_name);

		printf("휴대폰번호를 입력하시오 : ");
		gets_s(buffer_phone, sizeof(buffer_phone));
		strcpy((A + i)->phone, buffer_phone);
	}
	
	for (int i = 0; i < arr_size; i++) {
		printf("이름 : %s\n", (A + i)->name);
		printf("번호 : %s\n", (A + i)->phone);
	}
	
	free(A);

	return 0;
}
