#include <stdio.h>
#include <string.h>            // memcpy()
#include <Windows.h>        // system()
#include <conio.h>            // _getch()

#define NAME_SIZE 20
#define SAMPLE_SIZE 25
#define MAX_SIZE 100
#define ENTER 13

typedef enum POSITION { EMPTY = 0, TOP = 1, JG = 2, MID = 3, AD = 4, SUP = 5 } POSITION;
typedef struct CHAMPION {
	char name[NAME_SIZE];
	int hp, mp, speed, range;
	POSITION position;
} CHAMPION;

int list_view(void);
int all_empty(CHAMPION list[], int i);
CHAMPION *init_sample(void);
int name_check(CHAMPION list[], int j, char strs[]);
int insert_champion(CHAMPION *target, CHAMPION *copy);
int find_max(CHAMPION list[], int j, int Max);
int *insert_HP(CHAMPION list[], int HP_arr[], int i);
int HP_rev(int HP_arr[]);
CHAMPION *find_HP(CHAMPION list[], int target_HP, int i);
int full_sample(CHAMPION list[], CHAMPION sample[], int HP_arr[], int i);

int Search(CHAMPION list[], int i, char search[]);                            // 1. Search
int Insert(CHAMPION list[], int i);                                        // 2. Insert
int Delete(CHAMPION list[], int i, char search[]);                            // 3. Delete
int DeleteAll(CHAMPION list[], int i, int target);                            // 4. DeleteAll(position)
int PrintAll(CHAMPION list[], int i);                                        // 5. PrintAll
int FindMaxHp(CHAMPION list[], int i);                                        // 6. FindMaxHP
int SortByHp(CHAMPION list[]);                                                // 7. SortByHp

int main() {

	CHAMPION list[MAX_SIZE];
	all_empty(list, 0);
	memcpy(list, init_sample(), sizeof(CHAMPION)*MAX_SIZE);
	int select;

	while ((select = list_view()) != 8)                // 8. Exit
	{
		while (getchar() != '\n');                    // 버퍼 비우기, fflush 먹통일 때 사용
		system("cls");

		if (select == 1) {                            // 1. Search
			char search[NAME_SIZE];
			printf("Search : ");
			gets_s(search, sizeof(char)*NAME_SIZE);
			system("cls");
			Search(list, 0, search);
		}
		else if (select == 2) {                        // 2. Insert
			Insert(list, 0);
		}
		else if (select == 3) {                        // 3. Delete
			char search[NAME_SIZE];
			printf("Search : ");
			gets_s(search, sizeof(char)*NAME_SIZE);
			system("cls");
			Delete(list, 0, search);
		}
		else if (select == 4) {                        // 4. DeleteAll(position)
			int delete_position;
			printf("Search : ");
			scanf("%d", &delete_position);
			system("cls");
			DeleteAll(list, 0, delete_position);
		}
		else if (select == 5) {                         // 5. PrintAll
			PrintAll(list, 0);
		}
		else if (select == 6) {                        // 6. FindMaxHp
			FindMaxHp(list, 0);
		}
		else if (select == 7) {                        // 7. SortByHp
			SortByHp(list);
		}
		else {                                        // 예외 처리

		}
	}

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
int all_empty(CHAMPION list[], int i) {
	if (i < MAX_SIZE) {
		memcpy((list + i)->name, "\0", sizeof(NAME_SIZE));
		(list + i)->hp = 0;
		(list + i)->mp = 0;
		(list + i)->speed = 0;
		(list + i)->range = 0;
		(list + i)->position = EMPTY;
		return all_empty(list, i + 1);
	}
	return 0;
}
CHAMPION *init_sample(void) {
	CHAMPION champion_sample[MAX_SIZE] = {
		{ "가렌", 495, 100, 75, 50, TOP },
		{ "요릭", 475, 140, 50, 50, TOP },
		{ "초가스", 675, 70, 50, 60, JG },
		{ "카시오페아", 335, 295, 55, 375, MID },
		{ "칼리스타", 295, 120, 60, 375, AD },
		{ "케인", 350, 110, 50, 50, JG },
		{ "퀸", 275, 150, 100, 405, AD },
		{ "트위스티드 페이트",310, 35, 55, 375, MID },
		{ "하이머딩거", 385, 25, 60, 375, TOP },
		{ "갈리오", 325, 75, 50, 50, MID },
		{ "갱플랭크", 330, 100, 50, 50, TOP },
		{ "그라가스", 335, 95, 50, 2, JG },
		{ "그레이브즈", 340, 90, 100, 50, JG },
		{ "나르", 345, 100, 85, 105, TOP },
		{ "나미", 100, 100, 80, 65, SUP },
		{ "나서스", 355, 100, 75, 70, TOP },
		{ "노틸러스", 360, 70, 50, 75, TOP },
		{ "녹턴", 365, 65, 50, 55, JG },
		{ "누누", 675, 60, 50, 45, SUP },
		{ "니달리", 375, 55, 70, 55, JG },
		{ "다리우스", 380, 50, 80, 60, TOP },
		{ "다이애나", 385, 45, 90, 65, MID },
		{ "드레이븐", 390, 40, 100, 70, AD },
		{ "라이즈", 400, 35, 105, 40, MID },
		{ "라칸", 200, 30, 110, 30, SUP }
	};

	return champion_sample;
}
int name_check(CHAMPION list[], int j, char strs[]) {
	if (j < MAX_SIZE) {
		if (strcmp((list + j)->name, strs) == 0) {
			return 0;
		}
		else {
			return name_check(list, j + 1, strs);
		}
	}
	else {
		return 1;
	}
}
int insert_champion(CHAMPION *target, CHAMPION *copy) {
	memcpy(target, copy, sizeof(CHAMPION));
	return 0;
}
int find_max(CHAMPION list[], int j, int Max) {
	if (j < MAX_SIZE) {
		if ((list + j)->hp > Max) {
			Max = (list + j)->hp;
			return find_max(list, j + 1, Max);
		}
		else {
			return find_max(list, j + 1, Max);
		}
	}
	return Max;
}
int *insert_HP(CHAMPION list[], int HP_arr[], int i) {
	if (i < MAX_SIZE) {
		*(HP_arr + i) = (list + i)->hp;
		return insert_HP(list, HP_arr, i + 1);
	}

	return HP_arr;
}
int HP_rev(int HP_arr[]) {
	int i = 0, j = 0;
	int new_arr[MAX_SIZE];
	memcpy(new_arr, HP_arr, sizeof(int)*MAX_SIZE);
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 1; j < MAX_SIZE; j++) {
			if (i == j) { continue; }
			if (new_arr[j - 1] < new_arr[j]) {                // n+1이 n보다 작으면, n이 더 크면
				int p = new_arr[j - 1];
				new_arr[j - 1] = new_arr[j];
				new_arr[j] = p;
			}
		}
	}
	memcpy(HP_arr, new_arr, sizeof(int)*MAX_SIZE);
	return 0;
}
CHAMPION *find_HP(CHAMPION list[], int target_HP, int i) {
	if (i < MAX_SIZE) {
		if ((list + i)->hp == target_HP) {
			(list + i)->hp = 0;
			return (list + i);
		}
		return find_HP(list, target_HP, i + 1);
	}
	return NULL;
}
int full_sample(CHAMPION list[], CHAMPION sample[], int HP_arr[], int i) {        // list는 원본, sample은 정리본
	if (i < MAX_SIZE) {
		insert_champion(sample + i, find_HP(list, HP_arr[i], 0));
		(sample + i)->hp = HP_arr[i];
		return full_sample(list, sample, HP_arr, i + 1);
	}
	memcpy(list, sample, sizeof(CHAMPION)*MAX_SIZE);
	return 0;
}

int Search(CHAMPION list[], int i, char search[]) {            // 1. Search

	if (i < MAX_SIZE) {
		if (strcmp((list + i)->name, search) == 0) {
			printf("name : %-20s, hp : %3d,\t mp : %3d,\t speed : %3d,\t range : %3d,\t position : %d\n",
				(list + i)->name, (list + i)->hp, (list + i)->mp, (list + i)->speed, (list + i)->range, (list + i)->position);
		}
		else {
			return Search(list, i + 1, search);
		}
	}
	char exit = 0;
	printf("Enter");

	do {
		exit = _getch();
	} while (exit != 13);

	system("cls");
	return 0;
}
int Insert(CHAMPION list[], int i) {            // 2. Insert
	CHAMPION data;
	if (i < MAX_SIZE) {
		if ((list + i)->hp == 0) {
			printf("name : ");
			gets_s(data.name, sizeof(char)*NAME_SIZE);

			if (name_check(list, 0, data.name)) {
				printf("hp : ");
				scanf("%d", &data.hp);
				printf("mp : ");
				scanf("%d", &data.mp);
				printf("speed : ");
				scanf("%d", &data.speed);
				printf("range : ");
				scanf("%d", &data.range);

				int input;

				do {
					printf("position : ");
					scanf("%d", &input);
					switch (input) {
					case 1:
						data.position = TOP;
						break;
					case 2:
						data.position = JG;
						break;
					case 3:
						data.position = MID;
						break;
					case 4:
						data.position = AD;
						break;
					case 5:
						data.position = SUP;
						break;
					default:
						printf("Input error\n");
					}
				} while (input < 1 && input > 5);

				insert_champion(list + i, &data);

				system("cls");
			}
			else {
				system("cls");
			}
		}

		else {
			return Insert(list, i + 1);
		}
	}
	return 0;
}
int Delete(CHAMPION list[], int i, char search[]) {            // 3. Delete

	if (i < MAX_SIZE) {
		if (strcmp((list + i)->name, search) == 0) {
			CHAMPION empty_data = { "/0", 0, 0, 0, 0, EMPTY };
			insert_champion(list + i, &empty_data);
		}
		else {
			return Delete(list, i + 1, search);
		}
	}
	return 0;
}
int DeleteAll(CHAMPION list[], int i, int target) {            // 4. DeleteAll

	if (i < MAX_SIZE) {
		if ((list + i)->position == target) {
			CHAMPION empty_data = { "/0", 0, 0, 0, 0, EMPTY };
			insert_champion(list + i, &empty_data);
			return DeleteAll(list, i + 1, target);
		}
		else {
			return DeleteAll(list, i + 1, target);
		}
	}

	system("cls");
	return 0;
}
int PrintAll(CHAMPION list[], int i) {            // 5. PrintAll
	if (i < MAX_SIZE) {
		if ((list + i)->hp != 0) {
			printf("name : %-20s, hp : %3d,\t mp : %3d,\t speed : %3d,\t range : %3d,\t position : %d\n",
				(list + i)->name, (list + i)->hp, (list + i)->mp, (list + i)->speed, (list + i)->range, (list + i)->position);
		}
		return PrintAll(list, i + 1);
	}
	char exit = 0;
	printf("Enter");

	do {
		exit = _getch();
	} while (exit != 13);

	system("cls");
	return 0;
}
int FindMaxHp(CHAMPION list[], int i) {            // 6. FindMaxHp
	if (i < MAX_SIZE) {
		if ((list + i)->hp == find_max(list, 0, 0)) {
			printf("name : %-20s, hp : %3d,\t mp : %3d,\t speed : %3d,\t range : %3d,\t position : %d\n",
				(list + i)->name, (list + i)->hp, (list + i)->mp, (list + i)->speed, (list + i)->range, (list + i)->position);
			return FindMaxHp(list, i + 1);
		}
		else {
			return FindMaxHp(list, i + 1);
		}
	}
	char exit = 0;
	printf("Enter");

	do {
		exit = _getch();
	} while (exit != 13);

	system("cls");
	return 0;
}
int SortByHp(CHAMPION list[]) {        // 7. SortByHp
	int HP_arr[MAX_SIZE];
	memcpy(HP_arr, insert_HP(list, HP_arr, 0), sizeof(int)*MAX_SIZE);
	HP_rev(HP_arr);
	CHAMPION sample[MAX_SIZE];
	full_sample(list, sample, HP_arr, 0);
	return 0;
}