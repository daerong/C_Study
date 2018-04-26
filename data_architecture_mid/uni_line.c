#include <Windows.h>	// system(), Sleep()
#include <stdio.h>        
#include <math.h>		// ������� ���̺귯��
#include <string.h>		// memcpy(), memcmp(), strcmp(), strncmp(), 
						// strcat(), strtok(), strlen(), strcpy()
#include <stdlib.h>		// free(), malloc(), calloc(), ralloc(),
						// atoi(), rand(), exit()
#include <malloc.h>		// malloc()
#include <time.h>		// �ð����� ���̺귯��
#include <conio.h>		// _getch()

#define CHAMPION_NAME 20
#define ENTER 13

typedef struct CHAMPION {
	char *name;
	int hp, mp, speed, range, position;
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
		if(!strcmp(data->name, search)){
			return data;
		}
		data = data->link;
	}
	return NULL;
}
void Insert_SL(CHAMPION_H *list_head, CHAMPION **prev, char *N, int H, int M, int S, int R, int P) {
	CHAMPION *data = (CHAMPION *)malloc(sizeof(CHAMPION));
	data->name = N;
	data->hp = H;
	data->mp = M;
	data->speed = S;
	data->range = R;
	data->position = P;
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
void DeleteAll_SL(CHAMPION_H *list_head, CHAMPION **prev, int position) {
	CHAMPION *data = list_head->head;
	CHAMPION *back = NULL;
	while (data != NULL) {
		if (data->position == position) {
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
void PrintAll(CHAMPION_H *list_head) {
	system("cls");
	CHAMPION *data = list_head->head;
	while (data != NULL) {
		printf("name : %-20s, hp : %3d, mp : %3d, speed : %3d, range : %3d, position : %d\n", data->name, data->hp, data->mp, data->speed, data->range, data->position);
		data = data->link;
	}
	char end = 0;
	while ((end = _getch()) != ENTER);
}

void FindMaxHp(CHAMPION_H *list_head) {
	system("cls");
	CHAMPION *data = list_head->head;
	int maxHP = 0;
	while (data != NULL) {
		if (data->hp > maxHP) {
			system("cls");
			printf("name : %-20s, hp : %3d, mp : %3d, speed : %3d, range : %3d, position : %d\n", data->name, data->hp, data->mp, data->speed, data->range, data->position);
			maxHP = data->hp;
		}
		else if (data->hp == maxHP) {
			printf("name : %-20s, hp : %3d, mp : %3d, speed : %3d, range : %3d, position : %d\n", data->name, data->hp, data->mp, data->speed, data->range, data->position);
		}
		data = data->link;
	}
}

CHAMPION *FindMaxHp_only(CHAMPION_H *list_head) {
	system("cls");
	CHAMPION *data = list_head->head;
	CHAMPION *target = NULL;
	int maxHP = 0;
	while (data != NULL) {
		if (data->hp > maxHP) {
			maxHP = data->hp;
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
		target = FindMaxHp_only(list_head);
		Insert_SL(new_head, &new_prev, target->name, target->hp, target->mp, target->speed, target->range, target->position);
		Delete_SL(list_head, prev, target);
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
	printf("���ڸ� �Է��ϼ��� : ");
	while(choice<1||choice>8) scanf("%d", &choice);
	return choice;
}
void sample_setting(CHAMPION_H *list_head, CHAMPION **prev) {
	Insert_SL(list_head, prev, "����", 495, 100, 75, 50, 1);
	Insert_SL(list_head, prev, "�丯", 475, 140, 50, 50, 2);
	Insert_SL(list_head, prev, "�ʰ���", 675, 70, 50, 60, 3);
	Insert_SL(list_head, prev, "ī�ÿ����", 335, 295, 55, 375, 4);
	Insert_SL(list_head, prev, "Į����Ÿ", 295, 120, 60, 375, 5);
	Insert_SL(list_head, prev, "����", 350, 110, 50, 50, 1);
	Insert_SL(list_head, prev, "��", 275, 150, 100, 405, 2);
	Insert_SL(list_head, prev, "Ʈ����Ƽ�� ����Ʈ", 310, 35, 55, 375, 3);
	Insert_SL(list_head, prev, "���̸ӵ���", 385, 25, 60, 375, 4);
	Insert_SL(list_head, prev, "������", 325, 75, 50, 50, 5);
	Insert_SL(list_head, prev, "���÷�ũ", 330, 100, 50, 50, 1);
	Insert_SL(list_head, prev, "�׶󰡽�", 335, 95, 50, 2, 2);
	Insert_SL(list_head, prev, "�׷��̺���", 340, 90, 100, 50, 3);
	Insert_SL(list_head, prev, "����", 345, 100, 85, 105, 4);
	Insert_SL(list_head, prev, "����", 100, 100, 80, 65, 5);
	Insert_SL(list_head, prev, "������", 355, 100, 75, 70, 1);
	Insert_SL(list_head, prev, "��ƿ����", 360, 70, 50, 75, 2);
	Insert_SL(list_head, prev, "����", 365, 65, 50, 55, 3);
	Insert_SL(list_head, prev, "����", 675, 60, 50, 45, 4);
	Insert_SL(list_head, prev, "�ϴ޸�", 375, 55, 70, 55, 5);
	Insert_SL(list_head, prev, "�ٸ��콺", 380, 50, 80, 60, 1);
	Insert_SL(list_head, prev, "���ֳ̾�", 385, 45, 90, 65, 2);
	Insert_SL(list_head, prev, "�巹�̺�", 390, 40, 100, 70, 3);
	Insert_SL(list_head, prev, "������", 400, 35, 105, 40, 4);
	Insert_SL(list_head, prev, "��ĭ", 200, 30, 110, 30, 5);
}
char *catch_name(void) {
	char buffer[CHAMPION_NAME];
	char *N = NULL;
	printf("�̸��� �Է��ϼ��� : ");
	while (getchar() != '\n');
	gets_s(buffer, CHAMPION_NAME);
	N = (char *)malloc(strlen(buffer) + 1);
	strcpy(N, buffer);
	return N;
}

int main() {
	CHAMPION_H *list_head = init_head();
	CHAMPION *prev = NULL;
	int select = 0;
	
	sample_setting(list_head, &prev);

	while ((select = select_num()) != 8) {
		if (select == 1) {
			char *N = catch_name();
			CHAMPION *result = Search_SL(list_head, N);
			free(N);
			if (result == NULL) printf("�˻� ����� �����ϴ�.\n");
			else printf("name : %-20s, hp : %3d, mp : %3d, speed : %3d, range : %3d, position : %d\n", result->name, result->hp, result->mp, result->speed, result->range, result->position);
			char end = 0;
			while ((end = _getch()) != ENTER);
		}
		else if (select == 2) {
			char *N = catch_name();
			if (Search_SL(list_head, N) != NULL) {
				printf("�̸��� �ߺ��˴ϴ�.\n");
				char end = 0;
				while ((end = _getch()) != ENTER);
				free(N);
			}
			else {
				int H, M, S, R, P;
				printf("name : %s\n", N);
				printf("hp, mp, speed, range, position�� �������� �����Ͽ� �Է��ϼ��� : ");
				scanf("%d %d %d %d %d", &H, &M, &S, &R, &P);
				Insert_SL(list_head, &prev, N, H, M, S, R, P);
			}
		}
		else if (select == 3) {
			char *N = catch_name();
			Delete_SL(list_head, &prev, Search_SL(list_head, N));
			free(N);
		}
		else if (select == 4) {
			int position = 0;
			printf("������ �������� �Է��ϼ��� : ");
			scanf("%d", &position);
			DeleteAll_SL(list_head, &prev, position);
		}
		else if (select == 5) {
			PrintAll(list_head);
		}
		else if (select == 6) {
			FindMaxHp(list_head);
			char end = 0;
			while ((end = _getch()) != ENTER);
		}
		else if (select == 7) {
			list_head = SortByHp_SL(list_head, &prev);
		}
		else if (select == 8) {
			exit(0);
		}
	}

	return 0;
}