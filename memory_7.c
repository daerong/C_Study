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

int view_movie(void);								// �޴� ����
void add_movie(MOVIE **list, MOVIE **prev);			// 1. ��ȭ ���� �߰�
void list_moive(MOVIE **next, MOVIE **list);		// 2. ��ȭ ���� ���
void delete_movie(MOVIE **next, MOVIE **list);		// �޸� ����

int main() {
	MOVIE *movie = NULL;
	MOVIE *prev = NULL;			// ���Ḯ��Ʈ�� �������� '����' �ܰ��� ��ũ ���� �ٲٴ� ������ ���Եȴ�.
	MOVIE *next = NULL;			// ���Ḯ��Ʈ�� �������࿡�� '��'�ּҸ� ����� ��, '����' ���� �����ؾ� �Ѵ�.
	int choice = 0;

	while ((choice = view_movie()) != 3)		// 3. ����
	{
		while (getchar() != '\n');				// ���� ����, fflush ������ �� ���
		system("cls");
		if (choice == 1) {						// 1. ��ȭ ���� �߰�
			add_movie(&movie, &prev);
		}
		else if (choice == 2) {					// 2. ��ȭ ���� ���
			list_moive(&next, &movie);
		}
		else {									// ���� ó��

		}
	}

	delete_movie(&next, &movie);				// �޸� ����
	return 0;
}

int view_movie(void) {
	int choice = 0;

	printf("���� ����Ʈ�� �̿��� ��ȭ ��ȣ�� �޴�\n");
	printf("----------------------------------\n");
	printf("1. ��ȭ ���� �߰�\n");
	printf("2. ��ȭ ���� ���\n");
	printf("3. ����\n");
	printf("----------------------------------\n");
	printf("��ȣ�� �����Ͻÿ� : ");
	scanf("%d", &choice);

	return choice;
}

void add_movie(MOVIE **list, MOVIE **prev) {	// 1. ��ȭ ���� �߰�
	printf("1. ��ȭ ���� �߰�\n");

	MOVIE *data;								// data�� ���� �߰��� ������
	data = (MOVIE*)malloc(sizeof(MOVIE));		// �����޸� �Ҵ�

	printf("��ȭ�� ������ �Է��Ͻÿ�: ");
	gets_s(data->title, sizeof(char)*TITLE_SIZE);
	printf("��ȭ�� ���� ������ �Է��Ͻÿ�: ");
	scanf("%d", &data->premiere);
	if (*list == NULL) {						// list�� �ʱ���¸�,
		*list = data;								// list�� ����Ű�� �ּҿ� data�� ����, list�� ó�� ������
	}
	else {										// list�� ���� ������,
		(*prev)->link = data;						// prev.link�� ���ּ� ����
	}
	data->link = NULL;							// �������� �ش��ϹǷ� NULL
	*prev = data;

	system("cls");
}

void list_moive(MOVIE **next, MOVIE **list) {	// 2. ��ȭ ���� ���
	printf("2. ��ȭ ���� ���\n");

	MOVIE *data;
	data = *list;								// ó���� ������

	while (data != NULL) {						// ���� �׻� NULL					
		printf("���� : %s\n", data->title);
		printf("���� ���� : %d\n", data->premiere);
		*next = data->link;						// ���� ������ �ѱ�
		data = *next;
	}
	printf("�˻��� ���ƽ��ϴ�.(3�ʰ� Ȯ��)\n");
	Sleep(3000);
	system("cls");

	next = NULL;


}

void delete_movie(MOVIE **next, MOVIE **list) {	// �޸� ����
	MOVIE *data;
	data = *list;
	while (data != NULL)
	{
		*next = data->link;
		free(data);
		data = *next;
	}
}
