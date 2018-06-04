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
	struct CHAMPION *link;
} CHAMPION;
typedef struct CHAMPION_H {
	CHAMPION *head;
} CHAMPION_H;

CHAMPION_H *init_head(void) {
	CHAMPION_H *init = (CHAMPION_H *)malloc(sizeof(CHAMPION_H));
	init->head = NULL;
	return init;
}

CHAMPION *Search_SL(CHAMPION_H *list_head, char *search) {
	system("cls");
	CHAMPION *data = list_head->head;
	while (data != NULL) {
		if (!strcmp(data->name, search)) {
			return data;
		}
		data = data->link;
	}
	return NULL;
}
void Insert_SL(CHAMPION_H *list_head, CHAMPION **prev, char *P, char *N, int H, int A, int S) {
	CHAMPION *data = (CHAMPION *)malloc(sizeof(CHAMPION));
	data->position = P;
	data->name = N;
	data->hp = H;
	data->attack = A;
	data->shield = S;

	data->link = NULL;
	if (list_head->head == NULL) {
		list_head->head = data;
	}
	else {
		(*prev)->link = data;
	}
	*prev = data;
}
void Delete_SL(CHAMPION_H *list_head, CHAMPION **prev, CHAMPION *target) {
	if (target == NULL) return;
	if (target == list_head->head) {
		list_head->head = target->link;
		return;
	}
	CHAMPION *data = list_head->head;

	while (data->link != target) {
		data = data->link;
	}
	data->link = target->link;
	if (target->link == NULL) {
		*prev = data;
	}
	free(target);
}
void DeleteAll_SL(CHAMPION_H *list_head, CHAMPION **prev, char *position) {
	CHAMPION *data = list_head->head;
	CHAMPION *back = NULL;
	while (data != NULL) {
		if (!strcmp(data->position, position)) {
			if (back == NULL) {
				list_head->head = data->link;
				free(data);
				data = list_head->head;
				continue;
			}
			else {
				back->link = data->link;
				free(data);
				data = back;
				if (back->link == NULL) *prev = back;
			}
		}
		back = data;
		data = data->link;
	}
}
void PrintAll_SL(CHAMPION_H *list_head) {
	system("cls");
	CHAMPION *data = list_head->head;
	while (data != NULL) {
		printf("position : %-10s, name : %-20s, hp : %5d, attack : %5d, shield : %5d\n", data->position, data->name, data->hp, data->attack, data->shield);
		data = data->link;
	}
	char end = 0;
	while ((end = _getch()) != ENTER);
}

void FindMaxHp_SL(CHAMPION_H *list_head) {
	system("cls");
	CHAMPION *data = list_head->head;
	int maxHP = 0;
	while (data != NULL) {
		if (data->hp > maxHP) {
			system("cls");
			printf("position : %-10s, name : %-20s, hp : %5d, attack : %5d, shield : %5d\n", data->position, data->name, data->hp, data->attack, data->shield);
			maxHP = data->hp;
		}
		else if (data->hp == maxHP) {
			printf("position : %-10s, name : %-20s, hp : %5d, attack : %5d, shield : %5d\n", data->position, data->name, data->hp, data->attack, data->shield);
		}
		data = data->link;
	}
}

CHAMPION *FindMaxHp_SL_only(CHAMPION_H *list_head) {
	CHAMPION *data = list_head->head;
	CHAMPION *target = NULL;
	if (data != NULL) target = data;
	while (data != NULL) {
		if (strcmp(data->name, target->name) == -1) {		// 이름 오름차순
			target = data;
		}
		data = data->link;
	}
	return target;
}
CHAMPION_H *SortByHp_SL(CHAMPION_H *list_head, CHAMPION **prev) {
	CHAMPION_H *new_head = init_head();
	CHAMPION *new_prev = NULL;
	CHAMPION *target = NULL;
	while (list_head->head != NULL) {
		target = FindMaxHp_SL_only(list_head);
		if (target != NULL) {
			Insert_SL(new_head, &new_prev, target->position, target->name, target->hp, target->attack, target->shield);
			Delete_SL(list_head, prev, target);
		}
		else {
			break;
		}
	}
	free(list_head);
	*prev = new_prev;
	return new_head;
}
int select_num(void) {
	system("cls");
	int choice = 0;
	printf("1. Search_SL\n");
	printf("2. Insert_SL\n");
	printf("3. Delete_SL\n");
	printf("4. DeleteAll_SL\n");
	printf("5. PrintAll\n");
	printf("6. FindMaxHp\n");
	printf("7. SortByHp_SL\n");
	printf("8. Exit\n");
	printf("숫자를 입력하세요 : ");
	while (choice<1 || choice>8) scanf("%d", &choice);
	while (getchar() != '\n');
	return choice;
}
void sample_setting(CHAMPION_H *list_head, CHAMPION **prev) {
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
		Insert_SL(list_head, prev, P, N, H, A, S);
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
	printf("%f seconds.\n", ((double)t) / CLOCKS_PER_SEC);
	getchar();
}

int main() {
	CHAMPION_H *list_head = init_head();
	CHAMPION *prev = NULL;
	int select = 0;
	clock_t checkTime;

	start_check(&checkTime);
	sample_setting(list_head, &prev);
	end_check(&checkTime);

	while ((select = select_num()) != 8) {
		if (select == 1) {
			char *N = catch_name();
			CHAMPION *result = Search_SL(list_head, N);
			free(N);
			if (result == NULL) printf("검색 결과가 없습니다.\n");
			else printf("position : %-10s, name : %-20s, hp : %5d, attack : %5d, shield : %5d\n", result->position, result->name, result->hp, result->attack, result->shield);
			char end = 0;
			while ((end = _getch()) != ENTER);
		}
		else if (select == 2) {
			char *N = catch_name();
			if (Search_SL(list_head, N) != NULL) {
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
					Insert_SL(list_head, &prev, P, N, H, A, S);
				}
			}
		}
		else if (select == 3) {
			char *N = catch_name();
			CHAMPION *result;
			if ((result = Search_SL(list_head, N)) == NULL) {
				printf("해당 챔피언이 없습니다.\n");
				char end = 0;
				while ((end = _getch()) != ENTER);
			}
			else {
				Delete_SL(list_head, &prev, result);
			}
			free(N);
		}
		else if (select == 4) {
			char *P = catch_position();
			if (strncmp(P, "ADCARRY", 7) && strncmp(P, "TOP", 3) && strncmp(P, "SUPPORTER", 9) && strncmp(P, "MID", 3) && strncmp(P, "JUNGLE", 6)) {
				printf("포지션을 제대로 입력하세요.\n");
				char end = 0;
				while ((end = _getch()) != ENTER);
				free(P);
			}
			else {
				DeleteAll_SL(list_head, &prev, P);
			}
		}
		else if (select == 5) {
			PrintAll_SL(list_head);
		}
		else if (select == 6) {
			FindMaxHp_SL(list_head);
			char end = 0;
			while ((end = _getch()) != ENTER);
		}
		else if (select == 7) {
			start_check(&checkTime);
			list_head = SortByHp_SL(list_head, &prev);
			end_check(&checkTime);
		}
		else if (select == 8) {
			exit(0);
		}
	}
	return 0;
}