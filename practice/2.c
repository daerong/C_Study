#include <stdio.h>
#include <Windows.h>    // system() �Լ��� ����ϱ� ���� ���̺귯��
#include <conio.h>		// _getch()
#include <string.h>		// strtok �Լ��� ����� ��� ����

typedef struct TARGET {
	int num;
	struct TARGET *link;
} TARGET;

TARGET *init_sample(TARGET **prev, int K) {						// �⺻ ���� �߰�
																// name, hp, mp, speed, range, position, link
	TARGET *init = NULL;
	init = (TARGET*)malloc(sizeof(TARGET));
	init->num = 1;
	*prev = init;

	for (int i = 1; i < K; i++) {
		TARGET *data;											// p�� ���� �߰��� ������
		data = (TARGET*)malloc(sizeof(TARGET));					// �����޸� �Ҵ�
		data->num = i + 1;
		(*prev)->link = data;									// prev.link�� ���ּ� ����
		data->link = NULL;										// �������� �ش��ϹǷ� NULL
		*prev = data;											// ���� ��ȯ�� �������� �ȴ�.
	}

	return init;
}

void Delete(TARGET **next, TARGET **list) {

	TARGET *data, *back = NULL;									// �����˻� �Ű���, ����
	int insert = 0;
	scanf("%d", &insert);

	data = *list;													// ó���� ������

	int i = 1;

	while (data != NULL) {									// �� ����� ���ٸ� ������ �ʿ� ����    
		if (!(i%insert)) {
			if (data == *list) {									// �� ���� ������ ���
				*list = data->link;
				free(data);
			}
			else {
				*next = data->link;									// ������ ���� n�̸� n+1�� ���� ������
				back->link = *next;									// n-1�� ��ũ�� n+1�� ����
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
	data = *list;													// ó���� ������

	while (data != NULL) {											// ���� �׻� NULL        
																	// name, hp, mp, speed, range, position, link
		printf("%d\n", data->num);

		*next = data->link;											// ���� ������ �ѱ�
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

	TARGET *list = init_sample(&prev, K);			// ���Ḯ��Ʈ�� ó��

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