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

int view_list(void);							// �޴� ����
void clear_list(LIST **list, LIST **next);		// 1. �ʱ�ȭ
void add_list(LIST **list, LIST **prev);		// 2. ��ȭ ��ȣ �߰�
void search_list(LIST **next, LIST **list);		// 3. ��ȭ ��ȣ Ž��
void delete_list(LIST **next, LIST **list);		// �޸� ����

int main() {
	LIST *info = NULL;
	LIST *prev = NULL;
	LIST *next = NULL;
	int insert = 0;

	while ((insert = view_list()) != 4)		// 4. ����
	{
		while (getchar() != '\n');			// ���� ����, fflush ������ �� ���
		system("cls");
		if (insert == 1) {					// 1. �ʱ�ȭ
			clear_list(&info, &next);
		}
		else if (insert == 2) {				// 2. ��ȭ ��ȣ �߰�
			add_list(&info, &prev);
		}
		else if (insert == 3) {				// 3. ��ȭ ��ȣ Ž��
			search_list(&next, &info);
		}
		else {								// ���� ó��

		}
	}

	delete_list(&next, &info);				// �޸� ����
	return 0;
}

int view_list(void) {
	int choice = 0;

	printf("���� ����Ʈ�� �̿��� ��ȭ ��ȣ�� �޴�\n");
	printf("----------------------------------\n");
	printf("1. �ʱ�ȭ\n");
	printf("2. ��ȭ ��ȣ �߰�\n");
	printf("3. ��ȭ ��ȣ Ž��\n");
	printf("4. ����\n");
	printf("----------------------------------\n");
	printf("��ȣ�� �Է��ϼ��� : ");
	scanf("%d", &choice);

	return choice;
}

void clear_list(LIST **list, LIST **next) {	// 1. �ʱ�ȭ
	printf("1. �ʱ�ȭ\n");

	LIST *data;
	data = *list;							// p�� list�� ������ ����

	while (data != NULL) {					// ����Ʈ�� ������� ������,
		*next = data->link;						// next�� ���� �ּ� ����
		free(data);							// ���� �ּ� ����
		data = *next;							// p�� ���� �����͸� ����
	}

	next = NULL;
	printf("�ʱ�ȭ�� �Ϸ�Ǿ����ϴ�.\n");
	Sleep(1000);
	system("cls");
}

void add_list(LIST **list, LIST **prev) {	// 2. ��ȭ ��ȣ �߰�
	printf("2. ��ȭ��ȣ�� �߰�\n");

	LIST *data;									// p�� ���� �߰��� ������
	data = (LIST*)malloc(sizeof(LIST));			// �����޸� �Ҵ�

	printf("�̸�: ");
	gets_s(data->name, sizeof(char)*SIZE);
	printf("��ȣ: ");
	gets_s(data->phone, sizeof(char)*SIZE);
	if (*list == NULL) {						// list�� �ʱⰪ�̸�,
		*list = data;								// list�� ����Ű�� �ּҿ� p�� ����, list�� ó�� ������
	}
	else {										// list�� ���� ������,
		(*prev)->link = data;						// prev.link�� ���ּ� ����
	}
	data->link = NULL;							// �������� �ش��ϹǷ� NULL
	*prev = data;

	system("cls");
}

void search_list(LIST **next, LIST **list) {	// 3. ��ȭ ��ȣ Ž��
	printf("3. ��ȭ ��ȣ Ž��\n");

	LIST *data;									// �����˻� �Ű���
	char input[SIZE];
	printf("ã�� �̸�: ");
	gets_s(input, sizeof(char)*SIZE);
	data = *list;								// ó���� ������

	while (data != NULL) {						// ���� �׻� NULL					
		if (!(strcmp(data->name, input))) {
			printf("��ȭ ��ȣ�� %s�Դϴ�.\n", data->phone);
		}
		*next = data->link;
		data = *next;
	}
	printf("�˻��� ���ƽ��ϴ�.(3�ʰ� Ȯ��)\n");
	Sleep(3000);
	system("cls");

	next = NULL;


}

void delete_list(LIST **next, LIST **list) {	// �޸� ����
	LIST *data;
	data = *list;
	while (data != NULL)						// �ʱ�ȭ�� ����
	{
		*next = data->link;
		free(data);
		data = *next;
	}
}
