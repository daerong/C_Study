#include <Windows.h>	// system(), Sleep()
#include <stdio.h>        
#include <string.h>		// memcpy(), memcmp(), strcmp(), strncmp(), strcat(), strtok(), strlen(), strcpy()
#include <stdlib.h>		// free(), malloc(), calloc(), ralloc(), atoi(), rand(), exit()
#include <time.h>		// 시간관련 라이브러리
#include <conio.h>		// _getch()

#define CHAMPION_POSITION 10
#define CHAMPION_NAME 20
#define ENTER 13
#define BUF_SIZE 255

typedef struct CHAMPION {
	char *position;
	char *name;
	int hp, attack, shield;
	struct CHAMPION *l_link;
	struct CHAMPION *r_link;
} CHAMPION;
typedef struct CHAMPION_H {
	CHAMPION *head;
} CHAMPION_H;

CHAMPION_H *init_head(void) {
	CHAMPION_H *init = (CHAMPION_H *)malloc(sizeof(CHAMPION_H));
	init->head = NULL;
	return init;
}
CHAMPION *Search_DL(CHAMPION_H *list_head, char *search) {
	system("cls");
	CHAMPION *data = list_head->head;
	while (data != NULL) {
		if (!strcmp(data->name, search)) {
			return data;
		}
		data = data->r_link;
	}
	return NULL;
}
void Insert_DL(CHAMPION_H *list_head, char *P, char *N, int H, int A, int S) {
	CHAMPION *data = (CHAMPION *)malloc(sizeof(CHAMPION));
	data->position = P;
	data->name = N;
	data->hp = H;
	data->attack = A;
	data->shield = S;
	data->l_link = NULL;
	data->r_link = NULL;

	if (list_head->head == NULL) {
		list_head->head = data;
	}
	else {
		CHAMPION *right = list_head->head;
		right->l_link = data;
		data->r_link = right;
		list_head->head = data;
	}
}
void Delete_DL(CHAMPION_H *list_head, CHAMPION *target) {
	if (target == NULL) return;
	if (target->l_link == NULL) {
		list_head->head = target->r_link;
		if (target->r_link == NULL) {
			list_head->head = NULL;
		}
		else {
			list_head->head->l_link = NULL;
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
void DeleteAll_DL(CHAMPION_H *list_head, char *position) {
	CHAMPION *data = list_head->head;
	while (data != NULL) {
		if (!strcmp(data->position, position)) {
			if (data->l_link == NULL) {
				list_head->head = data->r_link;
				list_head->head->l_link = NULL;
				free(data);
				data = list_head->head;
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
void PrintAll_DL(CHAMPION_H *list_head) {
	system("cls");
	CHAMPION *data = list_head->head;
	while (data != NULL) {
		printf("position : %-10s, name : %-20s, hp : %5d, attack : %5d, shield : %5d\n", data->position, data->name, data->hp, data->attack, data->shield);
		data = data->r_link;
	}
	char end = 0;
	while ((end = _getch()) != ENTER);
}
void FindMaxHp_DL(CHAMPION_H *list_head) {
	CHAMPION *data = list_head->head;
	int MaxHP = 0;
	while (data != NULL) {
		if (data->hp > MaxHP) {
			system("cls");
			printf("position : %-10s, name : %-20s, hp : %5d, attack : %5d, shield : %5d\n", data->position, data->name, data->hp, data->attack, data->shield);
			MaxHP = data->hp;
		}
		else if (data->hp == MaxHP) {
			printf("position : %-10s, name : %-20s, hp : %5d, attack : %5d, shield : %5d\n", data->position, data->name, data->hp, data->attack, data->shield);
		}
		data = data->r_link;
	}
}
CHAMPION *FindMinHp_DL_only(CHAMPION_H *list_head) {
	CHAMPION *data = list_head->head;
	CHAMPION *result = NULL;
	if (data != NULL) result = data;
	while (data != NULL) {
		if (strcmp(data->name, result->name) == 1) {		// 이름 오름차순
			result = data;
		}
		data = data->r_link;
	}
	return result;
}
CHAMPION_H *SortByHp_DL(CHAMPION_H *list_head) {
	CHAMPION_H *new_head = init_head();
	CHAMPION *target = NULL;
	while (list_head->head != NULL) {
		target = FindMinHp_DL_only(list_head);
		Insert_DL(new_head, target->position, target->name, target->hp, target->attack, target->shield);
		Delete_DL(list_head, target);
	}
	free(list_head);
	return new_head;
}
int select_num(void) {
	system("cls");
	int choice = 0;
	printf("1. Search_DL\n");
	printf("2. Insert_DL\n");
	printf("3. Delete_DL\n");
	printf("4. DeleteAll_DL\n");
	printf("5. PrintAll_DL\n");
	printf("6. FindMaxHp_DL\n");
	printf("7. SortByHp_DL\n");
	printf("8. Exit\n");
	printf("숫자를 입력하세요 : ");
	while (choice<1 || choice>8) scanf("%d", &choice);
	while (getchar() != '\n');
	return choice;
}
void sample_setting(CHAMPION_H *list_head) {
	char P_buf[CHAMPION_POSITION];
	char *P;
	char N_buf[CHAMPION_NAME];
	char *N;
	int H, A, S;
	FILE *filePointer;
	char *fileName = "SUB14Dic.txt";

	char buf[BUF_SIZE];

	filePointer = fopen(fileName, "r");
	if (filePointer == NULL) {
		printf("Error : Not exist file\n");
		char end = 0;
		while ((end = _getch()) != ENTER);
		return;
	}

	while (feof(filePointer) == 0) {
		fgets(buf, BUF_SIZE, filePointer);
		fscanf(filePointer, "%s %s %d %d %d", &P_buf, &N_buf, &H, &A, &S);
		P = (char *)malloc(strlen(P_buf) + 1);
		strcpy(P, P_buf);
		N = (char *)malloc(strlen(N_buf) + 1);
		strcpy(N, N_buf);
		Insert_DL(list_head, P, N, H, A, S);
	}
	fclose(filePointer);
}
char *catch_position(void) {
	char buffer[CHAMPION_POSITION];
	char *P = NULL;
	printf("포지션을 입력하세요 : ");
	gets_s(buffer, CHAMPION_POSITION);
	P = (char *)malloc(strlen(buffer) + 1);
	strcpy(P, buffer);
	return P;
}
char *catch_name(void) {
	char buffer[CHAMPION_NAME];
	char *N = NULL;
	printf("이름을 입력하세요 : ");
	gets_s(buffer, CHAMPION_NAME);
	N = (char *)malloc(strlen(buffer) + 1);
	strcpy(N, buffer);
	return N;
}
void start_check(clock_t *checkTime) {
	*checkTime = clock();
}
void end_check(clock_t *checkTime) {
	*checkTime = clock() - *checkTime;
	clock_t t = *checkTime;
	printf("%f seconds.\n", ((float)t) / CLOCKS_PER_SEC);
	getchar();
}

int main() {
	CHAMPION_H *list_head = init_head();
	int select = 0;
	clock_t checkTime;

	start_check(&checkTime);
	sample_setting(list_head);
	end_check(&checkTime);

	while ((select = select_num()) != 8) {
		if (select == 1) {		// printf("1. Search_R\n");
			char *N = catch_name();
			CHAMPION *result = Search_DL(list_head, N);
			free(N);
			if (result == NULL) printf("검색 결과가 없습니다.\n");
			else printf("position : %-10s, name : %-20s, hp : %5d, attack : %5d, shield : %5d\n", result->position, result->name, result->hp, result->attack, result->shield);
			char end = 0;
			while ((end = _getch()) != ENTER);
		}
		else if (select == 2) {	// printf("2. Insert_R\n");
			char *N = catch_name();
			if (Search_DL(list_head, N) != NULL) {
				printf("이름이 중복됩니다.\n");
				char end = 0;
				while ((end = _getch()) != ENTER);
				free(N);
			}
			else {
				char *P = catch_position();
				if (strncmp(P, "ADCARRY", 7) && strncmp(P, "TOP", 3) && strncmp(P, "SUPPORTER", 9) && strncmp(P, "MID", 3) && strncmp(P, "JUNGLE", 6)) {
					printf("포지션을 제대로 입력하세요.\n");
					char end = 0;
					while ((end = _getch()) != ENTER);
					free(P);
					free(N);
				}
				else {
					int H, A, S;
					printf("name : %s\n", N);
					printf("hp, attack, shield을 공백으로 구분하여 입력하세요 : ");
					scanf("%d %d %d", &H, &A, &S);
					while (getchar() != '\n');
					Insert_DL(list_head, P, N, H, A, S);
				}
			}
		}
		else if (select == 3) {	// printf("3. Delete_R\n");
			char *N = catch_name();
			CHAMPION *result;
			if ((result = Search_DL(list_head, N)) == NULL) {
				printf("해당 챔피언이 없습니다.\n");
				char end = 0;
				while ((end = _getch()) != ENTER);
			}
			else {
				Delete_DL(list_head, result);
			}
			free(N);
		}
		else if (select == 4) {	// printf("4. DeleteAll_R\n");
			char *P = catch_position();
			if (strncmp(P, "ADCARRY", 7) && strncmp(P, "TOP", 3) && strncmp(P, "SUPPORTER", 9) && strncmp(P, "MID", 3) && strncmp(P, "JUNGLE", 6)) {
				printf("포지션을 제대로 입력하세요.\n");
				char end = 0;
				while ((end = _getch()) != ENTER);
				free(P);
			}
			else {
				DeleteAll_DL(list_head, P);
			}
		}
		else if (select == 5) {	// printf("5. PrintAll_R\n");
			PrintAll_DL(list_head);
			char end = 0;
			while ((end = _getch()) != ENTER);
		}
		else if (select == 6) {	// printf("6. FindMaxHp_R\n");
			FindMaxHp_DL(list_head);
			char end = 0;
			while ((end = _getch()) != ENTER);
		}
		else if (select == 7) {	// printf("7. SortByHp_R\n");
			start_check(&checkTime);
			list_head = SortByHp_DL(list_head);
			end_check(&checkTime);
		}
	}
	return 0;
}