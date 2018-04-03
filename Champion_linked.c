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
void equal_element(CHAMPION **X, CHAMPION **Y);						// CHAMPION ����ü�� ���� ����
CHAMPION *init_sample(CHAMPION **prev);								// �ʱⰪ ����
void get_MaxHP(CHAMPION **list);									// �ִ밪�� ����� ��� üũ
void delete_list(CHAMPION **next, CHAMPION **list);					// ���α׷� ���� �� �޸� ����

void Search(CHAMPION **next, CHAMPION **list);								// 1. Search
void Insert(CHAMPION **list, CHAMPION **prev);								// 2. Insert
void Delete(CHAMPION **next, CHAMPION **list, CHAMPION **prev);				// 3. Delete
void DeleteAll(CHAMPION **next, CHAMPION **list, CHAMPION **prev);			// 4. DeleteAll(position)
void PrintAll(CHAMPION **list, CHAMPION **next);							// 5. PrintAll
void FindMaxHP(CHAMPION **next, CHAMPION **list);							// 6. FindMaxHP
void SortByHp(CHAMPION **next, CHAMPION **list, CHAMPION **prev);			// 7. SortByHp

int MaxHP = 0;																// �˻��ӵ� ����� ���� HP �ִ밪

int main() {

	CHAMPION *prev = NULL;							// �迭����Ʈ�� ������
	CHAMPION *list = init_sample(&prev);			// �迭����Ʈ�� ó��
	CHAMPION *next = NULL;							// ���� ���࿡ ����� �Ű�����, ���ο� �����ص� ����
	int select;


	while ((select = list_view()) != 8)				// 8. Exit
	{
		while (getchar() != '\n');					// ���� ����, fflush ������ �� ���
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
		else {										// ���� ó��

		}
	}

	delete_list(&next, &list);						// �޸� ����

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
void equal_element(CHAMPION **X, CHAMPION **Y) {				// X�� ���� Y�� ����
	strcpy_s((*X)->name, NAME_SIZE, (*Y)->name);				// name, hp, mp, speed, range, position, link
	(*X)->hp = (*Y)->hp;
	(*X)->mp = (*Y)->mp;
	(*X)->speed = (*Y)->speed;
	(*X)->range = (*Y)->range;
	(*X)->position = (*Y)->position;
	(*X)->link = (*Y)->link;
}
CHAMPION *init_sample(CHAMPION **prev) {						// �⺻ ���� �߰�
																// name, hp, mp, speed, range, position, link
	CHAMPION champion_sample[SAMPLE_SIZE] = {
		{ "����", 495, 100, 75, 50, TOP, NULL },
		{ "�丯", 475, 140, 50, 50, TOP, NULL },
		{ "�ʰ���", 675, 70, 50, 60, JG, NULL },
		{ "ī�ÿ����", 335, 295, 55, 375, MID, NULL },
		{ "Į����Ÿ", 295, 120, 60, 375, AD, NULL },
		{ "����", 350, 110, 50, 50, JG, NULL },
		{ "��", 275, 150, 100, 405, AD, NULL },
		{ "Ʈ����Ƽ�� ����Ʈ",310, 35, 55, 375, MID, NULL },
		{ "���̸ӵ���", 385, 25, 60, 375, TOP, NULL },
		{ "������", 325, 75, 50, 50, MID, NULL },
		{ "���÷�ũ", 330, 100, 50, 50, TOP, NULL },
		{ "�׶󰡽�", 335, 95, 50, 2, JG, NULL },
		{ "�׷��̺���", 340, 90, 100, 50, JG, NULL },
		{ "����", 345, 100, 85, 105, TOP, NULL },
		{ "����", 100, 100, 80, 65, SUP, NULL },
		{ "������", 355, 100, 75, 70, TOP, NULL },
		{ "��ƿ����", 360, 70, 50, 75, TOP, NULL },
		{ "����", 365, 65, 50, 55, JG, NULL },
		{ "����", 675, 60, 50, 45, SUP, NULL },
		{ "�ϴ޸�", 375, 55, 70, 55, JG, NULL },
		{ "�ٸ��콺", 380, 50, 80, 60, TOP, NULL },
		{ "���ֳ̾�", 385, 45, 90, 65, MID, NULL },
		{ "�巹�̺�", 390, 40, 100, 70, AD, NULL },
		{ "������", 400, 35, 105, 40, MID, NULL },
		{ "��ĭ", 200, 30, 110, 30, SUP, NULL }
	};

	CHAMPION *init = NULL;
	init = (CHAMPION*)malloc(sizeof(CHAMPION));
	*init = champion_sample[0];
	*prev = init;

	for (int i = 1; i < SAMPLE_SIZE; i++) {
		CHAMPION *data;											// p�� ���� �߰��� ������
		data = (CHAMPION*)malloc(sizeof(CHAMPION));				// �����޸� �Ҵ�
		*data = champion_sample[i];
		if (data->hp > MaxHP) {
			MaxHP = data->hp;
		}
		(*prev)->link = data;									// prev.link�� ���ּ� ����
		data->link = NULL;										// �������� �ش��ϹǷ� NULL
		*prev = data;											// ���� ��ȯ�� �������� �ȴ�.
	}

	return init;
}
void get_MaxHP(CHAMPION **list) {
	CHAMPION *data, *next = NULL;								// �����˻� �Ű���
	MaxHP = 0;
	data = *list;												// ó���� ������

	while (data != NULL) {										// ���� �׻� NULL                    
		if (data->hp > MaxHP) {
			MaxHP = data->hp;
		}
		next = data->link;
		data = next;
	}

	next = NULL;
}
void delete_list(CHAMPION **next, CHAMPION **list) {			// �޸� ����
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

	CHAMPION *data;												// �����˻� �Ű���
	char input[NAME_SIZE];
	printf("Search : ");
	gets_s(input, sizeof(char)*NAME_SIZE);
	data = *list;												// ó���� ������, data�� list. ��, �ʱⰪ�� ����

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

	CHAMPION *data;												// ���� �߰��� ������
	data = (CHAMPION*)malloc(sizeof(CHAMPION));					// �����޸� �Ҵ�
	CHAMPION *check = *list;									// check�� ó������ ����
	int input = 0;
	int option = 1;												// �̸� �ߺ�üũ �б� ����
																// name, hp, mp, speed, range, position, link
	printf("name : ");
	gets_s(data->name, sizeof(char)*NAME_SIZE);
	while (check != NULL) {       
		if (!(strcmp(data->name, check->name))) {
			printf("�ߺ��� �̸��� �ֽ��ϴ�.\n");
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

		if (*list == NULL) {									// ���Ḯ��Ʈ�� �ϳ��� ���ٸ�,
			*list = data;											// list�� ����Ű�� �ּҿ� p�� ����, list�� ó�� ������
			MaxHP = data->hp;									// �ִ밪 �ٲ��ֱ�
		}
		else {													// list�� ���� ������,
			(*prev)->link = data;									// prev.link�� ���ּ� ����
			if (data->hp > MaxHP) {								// ���� �Է��� ���� �ִ밪�̸�,
				MaxHP = data->hp;									// �ٲ��ش�
			}
		}

		data->link = NULL;										// �������� �ش��ϹǷ� NULL
		*prev = data;
	}

	system("cls");
}
void Delete(CHAMPION **next, CHAMPION **list, CHAMPION **prev) {	// 3.Delete

	CHAMPION *data, *back = NULL;									// �����˻� �Ű���, ����
	char input[NAME_SIZE];
	printf("Delete : ");
	gets_s(input, sizeof(char)*NAME_SIZE);
	data = *list;													// ó���� ������
	int check = 0;

	while (data != NULL) {											// �� ����� ���ٸ� ������ �ʿ� ����               
		if (!(strcmp(data->name, input))) {							// �̸� ��
			if (data == *list) {									// �� ���� ������ ���
				*list = data->link;
				if (data->hp == MaxHP) {
					get_MaxHP(list);
				}
				free(data);
				break;
			}
			else {	
				if (data->link == NULL) {							// �������� ������ ���
					*prev = back;
					(*prev)->link = NULL;
					if (data->hp == MaxHP) {
						get_MaxHP(list);
					}
				}
				else {												// �߰��� ������ ���
					*next = data->link;									// ������ ���� n�̸� n+1�� ���� ������
					back->link = *next;									// n-1�� ��ũ�� n+1�� ����
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

	CHAMPION *data, *back = NULL;											// �����˻� �Ű���, ����
	int input;
	printf("TOP = 1, JG = 2, MID = 3, AD = 4, SUP = 5\n");
	printf("Input number : ");
	scanf("%d", &input);
	data = *list;									// ó���� ������
           
	while (data != NULL) {							// �� ����� ���ٸ� ������ �ʿ� ����               
		if (data->position == input) {
			if (data == *list) {					// �� ���� ������ ���
				*list = (*list)->link;
				free(data);
				data = *list;
			}
			else {
				if (data->link == NULL) {			// ���� ��,
					*prev = back;						
				}
				else {								// �߰�,
					*next = data->link;					// ������ ���� n�̸� n+1�� ���� ������
					back->link = *next;					// n-1�� ��ũ�� n+1�� ����
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
	data = *list;													// ó���� ������

	printf("\t\t\t\t\t[ position info : TOP = 1, JG = 2, MID = 3, AD = 4, SUP = 5 ]\n");

	while (data != NULL) {											// ���� �׻� NULL        
																	// name, hp, mp, speed, range, position, link
		printf("name : %-20s, hp : %3d,\t mp : %3d,\t speed : %3d,\t range : %3d,\t position : %d\n",
			data->name, data->hp, data->mp, data->speed, data->range, data->position);
		*next = data->link;											// ���� ������ �ѱ�
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

	CHAMPION *data;							// �����˻� �Ű���
	data = *list;							// ó���� ������

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

	CHAMPION *data, *back = NULL;										// �����˻� �Ű���, ����
	data = *list;														// ó���� ������
	CHAMPION *result;
	result = (CHAMPION*)malloc(sizeof(CHAMPION));						// �����޸� �Ҵ�

	while (data != NULL) {												// ó������ MaxHP�� ������ �ֱ� ������ ��ü �ݺ��� ������ �ʿ����
		if (data->hp == MaxHP) {
			*result = *data;
			*prev = result;
			(*prev)->link = NULL;
			if (back == NULL) {											// �� ���� ��� ����
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
		CHAMPION *TopHP;                                        // TopHP�� ���� �߰��� ������
		TopHP = (CHAMPION*)malloc(sizeof(CHAMPION));            // �����޸� �Ҵ�
		data = *list;
		back = NULL;
		*next = data->link;
		CHAMPION *target = data, *front = NULL;

		while (data != NULL) {									// list �ϳ� ������ ���� ������ ������
			if (back == NULL) {									// ó���� ���,
				back = data;
				equal_element(&TopHP, &data);					// ����ü ���� TopHP = data, memcpy() ����ϴ� �����߻�.
			}
			if (data->hp > TopHP->hp){							// ū�� �ߺ��� ��� ���� �༮�� ����Ѵ�.
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

