#include <stdio.h>

#define MANY 5
#define EMPTY {" ", " ", " "}

typedef struct man {			// 전화번호부

	char name[20];
	char home_number[12];
	char phone_number[12];

} MAN;

int main() {

	MAN list[MANY];

	for (int i = 0; i < MANY; i++) {
		printf("%d번째 사람의 이름 : ", i + 1);
		scanf_s("%s", list[i].name, sizeof(list[i].name));
		printf("%d번째 사람의 집전화번호 : ", i + 1);
		scanf_s("%s", list[i].home_number, sizeof(list[i].home_number));
		printf("%d번째 사람의 핸드폰번호 : ", i + 1);
		scanf_s("%s", list[i].phone_number, sizeof(list[i].phone_number));
	}

	char search[20];

	printf("이름 검색 : ");
	scanf_s("%s", search, sizeof(search));

	int num = -1;

	for (int i = 0; i < MANY; i++) {
		if (!(strcmp(search, list[i].name))) {
			num = i;
			break;
		}
	}

	if (num == -1) {
		printf("검색 결과가 없습니다.");
	}
	else {
		printf("이름 : %s\n", list[num].name);
		printf("집전화번호 : %s\n", list[num].home_number);
		printf("핸드폰번호 : %s\n", list[num].phone_number);
	}


	return 0;
}