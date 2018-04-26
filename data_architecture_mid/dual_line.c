#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>

#define NAME_SIZE 20
#define ENTER 13

typedef struct CHAMPION {
	char *name;
	int hp, mp, speed, range, position;
	struct CHAMPION *r_link;
	struct CHAMPION *l_link;
} CHAMPION;
typedef struct CHAMPION_H {
	CHAMPION *head;
} CHAMPION_H;

CHAMPION_H *init_head(void) {
	CHAMPION_H *init = (CHAMPION_H *)malloc(sizeof(CHAMPION_H));
	init->head = NULL;
	
	return init;
}
CHAMPION *Search_R(CHAMPION_H *list, char *N) {
	CHAMPION *data = list->head;
	while (data != NULL) {
		if (!strcmp(data->name, N)) {
			return data;
		}
		data = data->r_link;
	}
	return NULL;
}

void Insert_R(CHAMPION_H *list, char *name, int hp, int mp, int speed, int range, int position) {
	CHAMPION *data = (CHAMPION *)malloc(sizeof(CHAMPION));
	data->name = name;
	data->hp = hp;
	data->mp = mp;
	data->speed = speed;
	data->range = range;
	data->position = position;
	data->l_link = NULL;
	data->r_link = NULL;
	if (list->head == NULL) {
		list->head = data;
	}
	else {
		CHAMPION *right = list->head;
		right->l_link = data;
		data->r_link = right;
		list->head = data;
	}
}

void Delete_R(CHAMPION_H *list, CHAMPION *target) {
	if (target->l_link == NULL) {
		list->head = target->r_link;
		if (target->r_link == NULL) {
			list->head = NULL;
		}
		else {
			list->head->l_link = NULL;
		}
		free(target);
	}
	else {
		CHAMPION *left = target->l_link;
		left->r_link = target->r_link;
		if (target->r_link != NULL) {
			CHAMPION *right = target->r_link;
			right->l_link = left;
		}
		free(target);
	}
}

void DeleteAll_R(CHAMPION_H *list, int P) {
	CHAMPION *data = list->head;
	while (data != NULL) {
		if (data->position == P) {
			if (data->l_link == NULL) {
				list->head = data->r_link;
				list->head->l_link = NULL;
				free(data);
				data = list->head;
				continue;
			}
			else {
				CHAMPION *left = data->l_link;
				left->r_link = data->r_link;
				if (data->r_link != NULL) {
					CHAMPION *right = data->r_link;
					right->l_link = left;
				}
				free(data);
				data = left;
			}	
		}
		data = data->r_link;
	}
}

void PrintAll_R(CHAMPION_H *list) {
	system("cls");
	CHAMPION *data = list->head;
	while (data != NULL) {
		printf("%-20s\t %3d\t %3d\t %3d\t %3d\t %d\n", data->name, data->hp, data->mp, data->speed, data->range, data->position);
		data = data->r_link;
	}
}

void FindMaxHp_R(CHAMPION_H *list) {
	CHAMPION *data = list->head;
	CHAMPION *result = NULL;
	int MaxHP = 0;
	while (data != NULL) {
		if (data->hp > MaxHP) {
			system("cls");
			printf("%-20s\t %3d\t %3d\t %3d\t %3d\t %d\n", data->name, data->hp, data->mp, data->speed, data->range, data->position);
			result = data;
		}
		else if (data->hp == MaxHP) {
			printf("%-20s\t %3d\t %3d\t %3d\t %3d\t %d\n", data->name, data->hp, data->mp, data->speed, data->range, data->position);
		}
		data = data->r_link;
	}
}

CHAMPION *FindMinHp_R_only(CHAMPION_H *list) {
	CHAMPION *data = list->head;
	CHAMPION *result = NULL;
	int MaxHP = 9999;
	while (data != NULL) {
		if (data->hp < MaxHP) {
			MaxHP = data->hp;
			result = data;
		}
		data = data->r_link;
	}
	return result;
}

CHAMPION_H *SortByHp_R(CHAMPION_H *list) {
	CHAMPION_H *new_list = init_head();
	CHAMPION *data = NULL;
	while (list->head != NULL) {
		data = FindMinHp_R_only(list);
		Insert_R(new_list, data->name, data->hp, data->mp, data->speed, data->range, data->position);
		printf("%-20s\t %3d\t %3d\t %3d\t %3d\t %d\n", data->name, data->hp, data->mp, data->speed, data->range, data->position);
		Delete_R(list, data);
	}
	free(list);
	return new_list;
}



int select_menu(void) {
	system("cls");
	int choice = 0;
	while (choice < 1 || choice >8) {
		printf("1. Search_R\n");
		printf("2. Insert_R\n");
		printf("3. Delete_R\n");
		printf("4. DeleteAll_R\n");
		printf("5. PrintAll_R\n");
		printf("6. FindMaxHp_R\n");
		printf("7. SortByHp_R\n");
		printf("8. Exit\n");
		printf("선택하세요 : ");
		scanf("%d", &choice);
		while (getchar() != '\n');
	}
	return choice;
}
void setting_sample(CHAMPION_H *list) {
	Insert_R(list, "가렌", 495, 100, 75, 50, 1);
	Insert_R(list, "요릭", 475, 140, 50, 50, 2);
	Insert_R(list, "초가스", 675, 70, 50, 60, 3);
	Insert_R(list, "카시오페아", 335, 295, 55, 375, 4);
	Insert_R(list, "칼리스타", 295, 120, 60, 375, 5);
	Insert_R(list, "케인", 350, 110, 50, 50, 1);
	Insert_R(list, "퀸", 275, 150, 100, 405, 2);
	Insert_R(list, "트위스티드 페이트", 310, 35, 55, 375, 3);
	Insert_R(list, "하이머딩거", 385, 25, 60, 375, 4);
	Insert_R(list, "갈리오", 325, 75, 50, 50, 5);
	Insert_R(list, "갱플랭크", 330, 100, 50, 50, 1);
	Insert_R(list, "그라가스", 335, 95, 50, 2, 2);
	Insert_R(list, "그레이브즈", 340, 90, 100, 50, 3);
	Insert_R(list, "나르", 345, 100, 85, 105, 4);
	Insert_R(list, "나미", 100, 100, 80, 65, 5);
	Insert_R(list, "나서스", 355, 100, 75, 70, 1);
	Insert_R(list, "노틸러스", 360, 70, 50, 75, 2);
	Insert_R(list, "녹턴", 365, 65, 50, 55, 3);
	Insert_R(list, "누누", 675, 60, 50, 45, 4);
	Insert_R(list, "니달리", 375, 55, 70, 55, 5);
	Insert_R(list, "다리우스", 380, 50, 80, 60, 1);
	Insert_R(list, "다이애나", 385, 45, 90, 65, 2);
	Insert_R(list, "드레이븐", 390, 40, 100, 70, 3);
	Insert_R(list, "라이즈", 400, 35, 105, 40, 4);
	Insert_R(list, "라칸", 200, 30, 110, 30, 5);
}
char *catch_name(void) {
	char buffer[NAME_SIZE];
	char *N = NULL;
	printf("이름을 입력하세요 : ");
	gets_s(buffer, NAME_SIZE);
	N = (char *)malloc(strlen(buffer) + 1);
	strcpy(N, buffer);
	return N;
}


int main() {
	CHAMPION_H *list = init_head();
	setting_sample(list);
	int choice = 0;

	while ((choice = select_menu()) != 8) {
		if (choice == 1) {		// printf("1. Search_R\n");
			char *N = catch_name();
			CHAMPION *result = Search_R(list, N);
			free(N);
			printf("%-20s\t %3d\t %3d\t %3d\t %3d\t %d\n", result->name, result->hp, result->mp, result->speed, result->range, result->position);
			char end = 0;
			while ((end = _getch()) != ENTER);
		}
		else if (choice == 2) {	// printf("2. Insert_R\n");
			char *N = catch_name();
			if(Search_R(list, N) != NULL) {
				free(N);
			}
			else {
				printf("name : %-20s", N);
				int H, M, S, R, P;
				printf("hp, mp, speed, range, position을 공백으로 구분하여 입력 : ");
				scanf("%d %d %d %d %d", &H, &M, &S, &R, &P);
				Insert_R(list, N, H, M, S, R, P);
			}
		}
		else if (choice == 3) {	// printf("3. Delete_R\n");
			char *N = catch_name();
			CHAMPION *result;
			if ((result = Search_R(list, N)) == NULL) {
				printf("해당 챔피언이 없습니다.\n");
				char end = 0;
				while ((end = _getch()) != ENTER);
			}
			else {
				Delete_R(list, result);
			}
			free(N);
		}
		else if (choice == 4) {	// printf("4. DeleteAll_R\n");
			int P = 0;
			printf("삭제할 포지션을 입력하세요 : ");
			scanf("%d", &P);
			DeleteAll_R(list, P);
		}
		else if (choice == 5) {	// printf("5. PrintAll_R\n");
			PrintAll_R(list);
			char end = 0;
			while ((end = _getch()) != ENTER);
		}
		else if (choice == 6) {	// printf("6. FindMaxHp_R\n");
			FindMaxHp_R(list);
			char end = 0;
			while ((end = _getch()) != ENTER);
		}
		else if (choice == 7) {	// printf("7. SortByHp_R\n");
			list = SortByHp_R(list);
		}
	}

	return 0;
}