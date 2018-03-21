#include <stdio.h>

#define MANY 5
#define EMPTY {" ", " ", " "}

typedef struct man {			// ��ȭ��ȣ��

	char name[20];
	char home_number[12];
	char phone_number[12];

} MAN;

int main() {

	MAN list[MANY];

	for (int i = 0; i < MANY; i++) {
		printf("%d��° ����� �̸� : ", i + 1);
		scanf_s("%s", list[i].name, sizeof(list[i].name));
		printf("%d��° ����� ����ȭ��ȣ : ", i + 1);
		scanf_s("%s", list[i].home_number, sizeof(list[i].home_number));
		printf("%d��° ����� �ڵ�����ȣ : ", i + 1);
		scanf_s("%s", list[i].phone_number, sizeof(list[i].phone_number));
	}

	char search[20];

	printf("�̸� �˻� : ");
	scanf_s("%s", search, sizeof(search));

	int num = -1;

	for (int i = 0; i < MANY; i++) {
		if (!(strcmp(search, list[i].name))) {
			num = i;
			break;
		}
	}

	if (num == -1) {
		printf("�˻� ����� �����ϴ�.");
	}
	else {
		printf("�̸� : %s\n", list[num].name);
		printf("����ȭ��ȣ : %s\n", list[num].home_number);
		printf("�ڵ�����ȣ : %s\n", list[num].phone_number);
	}


	return 0;
}