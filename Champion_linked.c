#include <stdio.h>
#include <Windows.h>		// System()
#include <conio.h>			// _getch()
#include <string.h>			// strcmp()

#define NAME_SIZE 20
#define SAMPLE_SIZE 25
#define ENTER 13

typedef enum POSITION { TOP = 1, JG = 2, MID = 3, AD = 4, SUP = 5 } POSITION;
typedef struct CHAMPION {
	char name[NAME_SIZE];
	int hp, mp, speed, range;
	POSITION position;
	struct CHAMPION *link;
} CHAMPION;

int list_view(void);
void equal_element(CHAMPION **X, CHAMPION **Y);						// CHAMPION 구조체간 대입 선언
CHAMPION *init_sample(CHAMPION **prev);								// 초기값 설정
void get_MaxHP(CHAMPION **list);									// 최대값이 변경될 경우 체크
void delete_list(CHAMPION **next, CHAMPION **list);					// 프로그램 종료 시 메모리 해제

void Search(CHAMPION **next, CHAMPION **list);								// 1. Search
void Insert(CHAMPION **list, CHAMPION **prev);								// 2. Insert
void Delete(CHAMPION **next, CHAMPION **list, CHAMPION **prev);				// 3. Delete
void DeleteAll(CHAMPION **next, CHAMPION **list, CHAMPION **prev);			// 4. DeleteAll(position)
void PrintAll(CHAMPION **list, CHAMPION **next);							// 5. PrintAll
void FindMaxHP(CHAMPION **next, CHAMPION **list);							// 6. FindMaxHP
void SortByHp(CHAMPION **next, CHAMPION **list, CHAMPION **prev);			// 7. SortByHp

int MaxHP = 0;																// 검색속도 향상을 위한 HP 최대값

int main() {

	CHAMPION *prev = NULL;							// 배열리스트의 마지막
	CHAMPION *list = init_sample(&prev);			// 배열리스트의 처음
	CHAMPION *next = NULL;							// 순차 진행에 사용할 매개변수, 내부에 선언해도 무방
	int select;


	while ((select = list_view()) != 8)				// 8. Exit
	{
		while (getchar() != '\n');					// 버퍼 비우기, fflush 먹통일 때 사용
		system("cls");

		if (select == 1) {							// 1. Search
			Search(&next, &list);
		}
		else if (select == 2) {						// 2. Insert
			Insert(&list, &prev);
		}
		else if (select == 3) {						// 3. Delete
			Delete(&next, &list, &prev);
		}
		else if (select == 4) {						// 4. DeleteAll(position)
			DeleteAll(&next, &list, &prev);
			get_MaxHP(&list);
		}
		else if (select == 5) {						 // 5. PrintAll
			PrintAll(&list, &next);
		}
		else if (select == 6) {						// 6. FindMaxHp
			FindMaxHP(&next, &list);
		}
		else if (select == 7) {						// 7. SortByHp
			SortByHp(&next, &list, &prev);
		}
		else {										// 예외 처리

		}
	}

	delete_list(&next, &list);						// 메모리 해제

	return 0;
}

int list_view(void) {
	int choice = 0;

	printf("Select Menu\n");
	printf("---------------------------\n");
	printf("1. Search\n");
	printf("2. Insert\n");
	printf("3. Delete\n");
	printf("4. DeleteAll(position)\n");
	printf("5. PrintAll\n");
	printf("6. FindMaxHp\n");
	printf("7. SortByHp\n");
	printf("8. Exit\n");
	printf("---------------------------\n");
	printf("Enter number : ");
	scanf("%d", &choice);

	return choice;
}
void equal_element(CHAMPION **X, CHAMPION **Y) {				// X의 값에 Y를 대입
	strcpy_s((*X)->name, NAME_SIZE, (*Y)->name);				// name, hp, mp, speed, range, position, link
	(*X)->hp = (*Y)->hp;
	(*X)->mp = (*Y)->mp;
	(*X)->speed = (*Y)->speed;
	(*X)->range = (*Y)->range;
	(*X)->position = (*Y)->position;
	(*X)->link = (*Y)->link;
}
CHAMPION *init_sample(CHAMPION **prev) {						// 기본 샘플 추가
																// name, hp, mp, speed, range, position, link
	CHAMPION champion_sample[SAMPLE_SIZE] = {
		{ "가렌", 495, 100, 75, 50, TOP, NULL },
		{ "요릭", 475, 140, 50, 50, TOP, NULL },
		{ "초가스", 675, 70, 50, 60, JG, NULL },
		{ "카시오페아", 335, 295, 55, 375, MID, NULL },
		{ "칼리스타", 295, 120, 60, 375, AD, NULL },
		{ "케인", 350, 110, 50, 50, JG, NULL },
		{ "퀸", 275, 150, 100, 405, AD, NULL },
		{ "트위스티드 페이트",310, 35, 55, 375, MID, NULL },
		{ "하이머딩거", 385, 25, 60, 375, TOP, NULL },
		{ "갈리오", 325, 75, 50, 50, MID, NULL },
		{ "갱플랭크", 330, 100, 50, 50, TOP, NULL },
		{ "그라가스", 335, 95, 50, 2, JG, NULL },
		{ "그레이브즈", 340, 90, 100, 50, JG, NULL },
		{ "나르", 345, 100, 85, 105, TOP, NULL },
		{ "나미", 100, 100, 80, 65, SUP, NULL },
		{ "나서스", 355, 100, 75, 70, TOP, NULL },
		{ "노틸러스", 360, 70, 50, 75, TOP, NULL },
		{ "녹턴", 365, 65, 50, 55, JG, NULL },
		{ "누누", 675, 60, 50, 45, SUP, NULL },
		{ "니달리", 375, 55, 70, 55, JG, NULL },
		{ "다리우스", 380, 50, 80, 60, TOP, NULL },
		{ "다이애나", 385, 45, 90, 65, MID, NULL },
		{ "드레이븐", 390, 40, 100, 70, AD, NULL },
		{ "라이즈", 400, 35, 105, 40, MID, NULL },
		{ "라칸", 200, 30, 110, 30, SUP, NULL }
	};

	CHAMPION *init = NULL;
	init = (CHAMPION*)malloc(sizeof(CHAMPION));
	*init = champion_sample[0];
	*prev = init;

	for (int i = 1; i < SAMPLE_SIZE; i++) {
		CHAMPION *data;											// p는 새로 추가할 데이터
		data = (CHAMPION*)malloc(sizeof(CHAMPION));				// 동적메모리 할당
		*data = champion_sample[i];
		if (data->hp > MaxHP) {
			MaxHP = data->hp;
		}
		(*prev)->link = data;									// prev.link에 현주소 대입
		data->link = NULL;										// 마지막에 해당하므로 NULL
		*prev = data;											// 다음 순환의 마지막이 된다.
	}

	return init;
}
void get_MaxHP(CHAMPION **list) {
	CHAMPION *data, *next = NULL;								// 순차검색 매개값
	MaxHP = 0;
	data = *list;												// 처음을 가져옴

	while (data != NULL) {										// 끝은 항상 NULL                    
		if (data->hp > MaxHP) {
			MaxHP = data->hp;
		}
		next = data->link;
		data = next;
	}

	next = NULL;
}
void delete_list(CHAMPION **next, CHAMPION **list) {			// 메모리 해제
	CHAMPION *data;
	data = *list;
	while (data != NULL)
	{
		*next = data->link;
		free(data);
		data = *next;
	}
}

void Search(CHAMPION **next, CHAMPION **list) {					// 1. Search

	CHAMPION *data;												// 순차검색 매개값
	char input[NAME_SIZE];
	printf("Search : ");
	gets_s(input, sizeof(char)*NAME_SIZE);
	data = *list;												// 처음을 가져옴, data는 list. 즉, 초기값을 가짐

	while (data != NULL) {                   
		if (!(strcmp(data->name, input))) {
			printf("name : %-20s, hp : %3d,\t mp : %3d,\t speed : %3d,\t range : %3d,\t position : %d\n",
				data->name, data->hp, data->mp, data->speed, data->range, data->position);
			break;
		}
		*next = data->link;
		data = *next;
	}

	char exit = 0;
	printf("Enter");

	do {
		exit = _getch();
	} while (exit != 13);

	system("cls");

	next = NULL;
}
void Insert(CHAMPION **list, CHAMPION **prev) {					// 2. Insert

	CHAMPION *data;												// 새로 추가할 데이터
	data = (CHAMPION*)malloc(sizeof(CHAMPION));					// 동적메모리 할당
	CHAMPION *check = *list;									// check는 처음값을 가짐
	int input = 0;
	int option = 1;												// 이름 중복체크 분기 설정
																// name, hp, mp, speed, range, position, link
	printf("name : ");
	gets_s(data->name, sizeof(char)*NAME_SIZE);
	while (check != NULL) {       
		if (!(strcmp(data->name, check->name))) {
			printf("중복된 이름이 있습니다.\n");
			free(data);
			option = 0;
			char exit = 0;
			printf("Enter");
			do {
				exit = _getch();
			} while (exit != 13);
			break;
		}
		check = check->link;
	}
	if (option) {
		printf("hp : ");
		scanf("%d", &data->hp);
		printf("mp : ");
		scanf("%d", &data->mp);
		printf("speed : ");
		scanf("%d", &data->speed);
		printf("range : ");
		scanf("%d", &data->range);
		do {
			printf("position : ");
			scanf("%d", &input);
			switch (input) {
			case 1:
				data->position = TOP;
				break;
			case 2:
				data->position = JG;
				break;
			case 3:
				data->position = MID;
				break;
			case 4:
				data->position = AD;
				break;
			case 5:
				data->position = SUP;
				break;
			default:
				printf("Input error\n");
			}
		} while (input < 1 && input > 5);

		if (*list == NULL) {									// 연결리스트가 하나도 없다면,
			*list = data;											// list가 가리키는 주소에 p를 대입, list는 처음 데이터
			MaxHP = data->hp;									// 최대값 바꿔주기
		}
		else {													// list에 값이 있으면,
			(*prev)->link = data;									// prev.link에 현주소 대입
			if (data->hp > MaxHP) {								// 새로 입력한 값이 최대값이면,
				MaxHP = data->hp;									// 바꿔준다
			}
		}

		data->link = NULL;										// 마지막에 해당하므로 NULL
		*prev = data;
	}

	system("cls");
}
void Delete(CHAMPION **next, CHAMPION **list, CHAMPION **prev) {	// 3.Delete

	CHAMPION *data, *back = NULL;									// 순차검색 매개값, 이전
	char input[NAME_SIZE];
	printf("Delete : ");
	gets_s(input, sizeof(char)*NAME_SIZE);
	data = *list;													// 처음을 가져옴
	int check = 0;

	while (data != NULL) {											// 비교 대상이 없다면 실행할 필요 없음               
		if (!(strcmp(data->name, input))) {							// 이름 비교
			if (data == *list) {									// 맨 앞이 삭제될 경우
				*list = data->link;
				if (data->hp == MaxHP) {
					get_MaxHP(list);
				}
				free(data);
				break;
			}
			else {	
				if (data->link == NULL) {							// 마지막이 삭제될 경우
					*prev = back;
					(*prev)->link = NULL;
					if (data->hp == MaxHP) {
						get_MaxHP(list);
					}
				}
				else {												// 중간이 삭제될 경우
					*next = data->link;									// 삭제할 값이 n이면 n+1의 값을 저장함
					back->link = *next;									// n-1의 링크에 n+1을 연결
					if (data->hp == MaxHP) {
						get_MaxHP(list);
					}
				}
				free(data);
				break;
			}
		}
		else {
			back = data;
			*next = data->link;
			data = *next;
		}
	}

	system("cls");

	next = NULL;
}
void DeleteAll(CHAMPION **next, CHAMPION **list, CHAMPION **prev) {			// 4. DeleteAll(position)

	CHAMPION *data, *back = NULL;											// 순차검색 매개값, 이전
	int input;
	printf("TOP = 1, JG = 2, MID = 3, AD = 4, SUP = 5\n");
	printf("Input number : ");
	scanf("%d", &input);
	data = *list;									// 처음을 가져옴
           
	while (data != NULL) {							// 비교 대상이 없다면 실행할 필요 없음               
		if (data->position == input) {
			if (data == *list) {					// 맨 앞이 삭제될 경우
				*list = (*list)->link;
				free(data);
				data = *list;
			}
			else {
				if (data->link == NULL) {			// 끝일 때,
					*prev = back;						
				}
				else {								// 중간,
					*next = data->link;					// 삭제할 값이 n이면 n+1의 값을 저장함
					back->link = *next;					// n-1의 링크에 n+1을 연결
				}
				free(data);
				data = back;
			}
		}
		else {
			back = data;
			*next = data->link;
			data = *next;
		}
		(*prev)->link = NULL;
	}
	system("cls");

	next = NULL;
}
void PrintAll(CHAMPION **list, CHAMPION **next) {					// 5. PrintAll
	CHAMPION *data;
	data = *list;													// 처음을 가져옴

	printf("\t\t\t\t\t[ position info : TOP = 1, JG = 2, MID = 3, AD = 4, SUP = 5 ]\n");

	while (data != NULL) {											// 끝은 항상 NULL        
																	// name, hp, mp, speed, range, position, link
		printf("name : %-20s, hp : %3d,\t mp : %3d,\t speed : %3d,\t range : %3d,\t position : %d\n",
			data->name, data->hp, data->mp, data->speed, data->range, data->position);
		*next = data->link;											// 다음 참조를 넘김
		data = *next;
	}

	char exit = 0;
	printf("Enter");

	do {
		exit = _getch();
	} while (exit != 13);

	system("cls");

	next = NULL;
}
void FindMaxHP(CHAMPION **next, CHAMPION **list) {					// 6. FindMaxHp

	CHAMPION *data;							// 순차검색 매개값
	data = *list;							// 처음을 가져옴

	while (data != NULL) {                     
		if (data->hp == MaxHP) {
			printf("name : %-20s, hp : %3d,\t mp : %3d,\t speed : %3d,\t range : %3d,\t position : %d\n",
				data->name, data->hp, data->mp, data->speed, data->range, data->position);
		}
		*next = data->link;
		data = *next;
	}

	char exit = 0;
	printf("Enter");

	do {
		exit = _getch();
	} while (exit != 13);

	system("cls");

	next = NULL;
}
void SortByHp(CHAMPION **next, CHAMPION **list, CHAMPION **prev) {		// 7. SortByHp

	CHAMPION *data, *back = NULL;										// 순차검색 매개값, 이전
	data = *list;														// 처음을 가져옴
	CHAMPION *result;
	result = (CHAMPION*)malloc(sizeof(CHAMPION));						// 동적메모리 할당

	while (data != NULL) {												// 처음값은 MaxHP로 정해져 있기 때문에 전체 반복문 실행할 필요없음
		if (data->hp == MaxHP) {
			*result = *data;
			*prev = result;
			(*prev)->link = NULL;
			if (back == NULL) {											// 맨 앞일 경우 조심
				*list = data->link;
			}
			else {
				back->link = data->link;
			}
			free(data);
			break;
		}
		back = data;
		*next = data->link;
		data = *next;
	}

	while (*list != NULL) {
		CHAMPION *TopHP;                                        // TopHP는 새로 추가할 포인터
		TopHP = (CHAMPION*)malloc(sizeof(CHAMPION));            // 동적메모리 할당
		data = *list;
		back = NULL;
		*next = data->link;
		CHAMPION *target = data, *front = NULL;

		while (data != NULL) {									// list 하나 남았을 때를 제외한 나머지
			if (back == NULL) {									// 처음일 경우,
				back = data;
				equal_element(&TopHP, &data);					// 구조체 대입 TopHP = data, memcpy() 사용하니 에러발생.
			}
			if (data->hp > TopHP->hp){							// 큰게 중복일 경우 앞의 녀석을 사용한다.
				equal_element(&TopHP, &data);
				target = data;
				front = back;
			}
			back = data;
			data = data->link;
		}
		
		(*prev)->link = TopHP;
		*prev = TopHP;
		(*prev)->link = NULL;
		if (front == NULL) {
			*list = target->link;
		}
		else {
			front->link = target->link;
		}
		free(target);
	}

	*list = result;

	system("cls");
	next = NULL;
}

