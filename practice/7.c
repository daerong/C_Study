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
		scanf("%d", &M);					// 시작
	} while (M < 1 || M>10000);
	do{
		scanf("%d", &N);					// 끝
	} while (N < M || N > 10000);

	while (getchar() != '\n');

	limit->min = M;
	limit->max = N;
}

void find_prime(NUMBER **list, LIMIT *limit) {
	
	NUMBER *data = *list;
	NUMBER *prev = NULL;							// 바로 앞
	int end = limit->max;

	while (data != NULL) {								// 비교 대상이 없다면 실행할 
		int check = 1;
		for (int i = 2; i < data->number; i++) {			
			if (!((data->number) % i)) {
				check = 0;
				if (data == *list) {				// 맨 앞이 삭제될 경우
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
	NUMBER *prev = NULL;							// 바로 앞

	while (data != NULL) {							// 비교 대상이 없다면 실행할 필요 없음               
		if (data->number < limit->min || data->number > limit->max) {
			if (data == *list) {					// 맨 앞이 삭제될 경우
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

	arr_setting(&list);				// 1~10000까지의 숫자를 찾아냄
	catch_limit(&limit);			// 범위 설정
	cut_limit(&list, &limit);		// 범위 잘라내기
	
	find_prime(&list, &limit);
	// PrintAll(&list);				// 체크 용도로 사용
	system("cls");
	print_result(&list, &limit);


	return 0;
}

void PrintAll(NUMBER **list) {										// 5. PrintAll
	NUMBER *next;
	NUMBER *data;
	data = *list;													// 처음을 가져옴
	
	while (data != NULL) {											// 끝은 항상 NULL        
																	// name, hp, mp, speed, range, position, link
		printf("number : %3d, link : %d\n", data->number, (int)data->link);
		next = data->link;											// 다음 참조를 넘김
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