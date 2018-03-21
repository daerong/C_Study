#include <stdio.h>
#include <stdlib.h>

typedef struct LIST {
	int num;
	struct LIST *link;
} LIST;

LIST *add_list(LIST **list, LIST **prev, int input);	// ������ �߰�
void read_list(LIST **lsit, LIST **next);				// ������ ����
void delete_list(LIST **list, LIST **next);				// �޸� ����

int main() {
	LIST *list = NULL;
	LIST *prev = NULL;
	LIST *next = NULL;
	int input;

	do {
		printf("���� ������ �Է��ϼ���(����: -1) : ");
		scanf("%d", &input);
		if (input == -1) { break; }
		add_list(&list, &prev, input);
		//while (getchar() != '\n');			// ���� ����, fflush ������ �� ���
	} while (1);

	read_list(&list, &next);					// ������ ����

	delete_list(&list, &next);					// �޸� ����
	return 0;
}

LIST *add_list(LIST **list, LIST **prev, int input) {

	LIST *data;									// data�� ���� �߰��� ������
	data = (LIST*)malloc(sizeof(LIST));			// �����޸� �Ҵ�

	data->num = input;
	if (*list == NULL) {						// list�� �ʱⰪ�̸�,
		*list = data;								// list�� ����Ű�� �ּҿ� data�� ����, list�� ó�� ������
	}
	else {										// list�� ���� ������,
		(*prev)->link = data;						// prev.link�� ���ּ� ����
	}
	data->link = NULL;							// �������� �ش��ϹǷ� NULL
	*prev = data;
}

void read_list(LIST **list, LIST **next) {		// ������ ����
	LIST *data;
	data = *list;								// ó���� ������

	while (data != NULL) {						// ���� �׻� NULL					
		printf("%d->", data->num);
		*next = data->link;						// ���� ������ �ѱ�
		data = *next;
	}

	printf("NULL\n");

	next = NULL;
}

void delete_list(LIST **list, LIST **next) {	// �޸� ����
	LIST *data;
	data = *list;
	while (data != NULL)						// �ʱ�ȭ�� ����
	{
		*next = data->link;
		free(data);
		data = *next;
	}
}
