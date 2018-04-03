#include <stdio.h>
#include <malloc.h>
#include <Windows.h>		// system()
#include <conio.h>			// _getch()

#define NUMBER_SIZE 10000

typedef struct NUMBER {
	int number;
	struct NUMBER *link;
} NUMBER;

typedef struct LIMIT {
	int min, max;
} LIMIT;

void PrintAll(NUMBER **list);

void arr_setting(NUMBER **list) {
	NUMBER *data;

	data = (NUMBER *)malloc(sizeof(NUMBER));
	data->number = 2;
	*list = data;
	data->link = NULL;
	NUMBER *prev = *list;

	prev = data;

	for (int i = 3; i <= NUMBER_SIZE; i++) {
		data = (NUMBER *)malloc(sizeof(NUMBER));
		data->number = i;
		data->link = NULL;
		prev->link = data;
		prev = data;
	}
}

void catch_limit(LIMIT *limit) {
	int M, N;
	do {
		scanf("%d", &M);					// ����
	} while (M < 1 || M>10000);
	do{
		scanf("%d", &N);					// ��
	} while (N < M || N > 10000);

	while (getchar() != '\n');

	limit->min = M;
	limit->max = N;
}

void find_prime(NUMBER **list, LIMIT *limit) {
	
	NUMBER *data = *list;
	NUMBER *prev = NULL;							// �ٷ� ��
	int end = limit->max;

	while (data != NULL) {								// �� ����� ���ٸ� ������ 
		int check = 1;
		for (int i = 2; i < data->number; i++) {			
			if (!((data->number) % i)) {
				check = 0;
				if (data == *list) {				// �� ���� ������ ���
					*list = (*list)->link;
					free(data);
					data = *list;
					break;
				}
				else {
					prev->link = data->link;
					free(data);
					data = prev->link;
					break;
				}
			}
		}
		if (check) {
			prev = data;
			data = prev->link;
		}

	}
}

void cut_limit(NUMBER **list, LIMIT *limit) {
	NUMBER *data = *list;
	NUMBER *prev = NULL;							// �ٷ� ��

	while (data != NULL) {							// �� ����� ���ٸ� ������ �ʿ� ����               
		if (data->number < limit->min || data->number > limit->max) {
			if (data == *list) {					// �� ���� ������ ���
				*list = (*list)->link;
				free(data);
				data = *list;
			}
			else {
				prev->link = data->link;
				free(data);
				data = prev->link;
			}
		}
		else {
			prev = data;
			data = prev->link;
		}

	}
}

void print_result(NUMBER **list, LIMIT *limit) {
	
	int sum = 0;
	NUMBER *data = *list;		

	while (data != NULL) {
		sum += data->number;
		data = data->link;
	}
	if (sum == 0) {
		printf("-1");
	}
	else {
		printf("%d\n", sum);
		printf("%d\n", (*list)->number);
	}
}

int main() {

	LIMIT limit;
	NUMBER *list;

	arr_setting(&list);				// 1~10000������ ���ڸ� ã�Ƴ�
	catch_limit(&limit);			// ���� ����
	cut_limit(&list, &limit);		// ���� �߶󳻱�
	
	find_prime(&list, &limit);
	// PrintAll(&list);				// üũ �뵵�� ���
	system("cls");
	print_result(&list, &limit);


	return 0;
}

void PrintAll(NUMBER **list) {										// 5. PrintAll
	NUMBER *next;
	NUMBER *data;
	data = *list;													// ó���� ������
	
	while (data != NULL) {											// ���� �׻� NULL        
																	// name, hp, mp, speed, range, position, link
		printf("number : %3d, link : %d\n", data->number, (int)data->link);
		next = data->link;											// ���� ������ �ѱ�
		data = next;
	}

	char exit = 0;
	printf("Enter");

	do {
		exit = _getch();
	} while (exit != 13);

	system("cls");

	next = NULL;
}