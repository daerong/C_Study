#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// strcpy() �� ���ڿ� ó���Լ� ����ϱ� ���� ���̺귯��

#define NAME_SIZE 12
#define PHONE_SIZE 28

typedef struct book {
	char *name;
	char *phone;
} BOOK;


int main() {

	BOOK *A;		// BOOK �迭 ������ ����
	int arr_size;

	printf("�ּ��� ���� : ");
	scanf("%d", &arr_size);

	while (getchar() != '\n');		// fflush(stdin)�� �������� �ʾ� �̷��� ó��, getchar() �� ���� ���ڸ� �Է¹���
	// getchar()�� ��� �о�鿩 ó�������� \n�� ã�� �� ���� ������ �ѱ�, ���� �������� ��� ���۸� ����� �� �ִ�.

	if ((A = malloc(arr_size * sizeof(BOOK))) != NULL) {		// int **  = (int *)malloc(sizeof(char *))
		for (int i = 0; i < arr_size; i++) {
			(A + i)->name = (char *)malloc(NAME_SIZE);
			(A + i)->phone = (char *)malloc(PHONE_SIZE);
		}
		printf("%d���� �ּҸ� ������ �� �ִ� ������ �Ҵ�Ǿ����ϴ�.\n", arr_size);

	}
	for (int i = 0; i < arr_size; i++) {
		char buffer_name[NAME_SIZE];
		char buffer_phone[PHONE_SIZE];

		printf("�̸��� �Է��Ͻÿ� : ");
		gets_s(buffer_name, sizeof(buffer_name));
		strcpy((A + i)->name, buffer_name);

		printf("�޴�����ȣ�� �Է��Ͻÿ� : ");
		gets_s(buffer_phone, sizeof(buffer_phone));
		strcpy((A + i)->phone, buffer_phone);
	}
	
	for (int i = 0; i < arr_size; i++) {
		printf("�̸� : %s\n", (A + i)->name);
		printf("��ȣ : %s\n", (A + i)->phone);
	}
	
	free(A);

	return 0;
}
