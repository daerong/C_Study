#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>	

#define CHAMPION_POSITION 10
#define CHAMPION_NAME 20
#define BUF_SIZE 255
#define ENTER 13

/* ========== 시간 관련 =========== */

clock_t checkTime;

void start_check(clock_t *checkTime) {
	*checkTime = clock();
}

void end_check(clock_t *checkTime) {
	*checkTime = clock() - *checkTime;
	clock_t t = *checkTime;
	printf("%f seconds.\n", ((double)t) / CLOCKS_PER_SEC);
	getchar();
}

/* ========== 시간 관련 =========== */

/* ========== 트리 관련 =========== */

typedef struct CHAMPION {	// key 값은 name
	char *position;
	char *name;
	int hp, attack, shield;
	struct CHAMPION *left;
	struct CHAMPION *right;
} CHAMPION;

CHAMPION *rotate_LL(CHAMPION *parent) {		// right rotate
	CHAMPION *child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}

CHAMPION *rotate_RR(CHAMPION *parent) {		// left rotate
	CHAMPION *child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}

CHAMPION *rotate_LR(CHAMPION *parent) {
	CHAMPION *child = parent->left;
	parent->left = rotate_RR(child);
	return rotate_LL(parent);
}

CHAMPION *rotate_RL(CHAMPION *parent) {
	CHAMPION *child = parent->right;
	parent->right = rotate_LL(child);
	return rotate_RR(parent);
}

int height_check(CHAMPION *tree) {
	int height = 0;
	if (tree != NULL) {
		if (height_check(tree->left) > height_check(tree->right)) {
			height = height_check(tree->left) + 1;
		}
		else {
			height = height_check(tree->right) + 1;
		}
	}
	return height;
}

int get_balanceFactor(CHAMPION *tree) {
	if (tree == NULL) { return 0; }
	return height_check(tree->left) - height_check(tree->right);
}

CHAMPION *make_AVL(CHAMPION **tree) {
	int BF = get_balanceFactor(*tree);

	if (BF > 1) {
		if (get_balanceFactor((*tree)->left) > 0) {
			*tree = rotate_LL(*tree);
		}
		else {
			*tree = rotate_LR(*tree);
		}
	}
	else if (BF < -1) {
		if (get_balanceFactor((*tree)->right) < 0) {
			*tree = rotate_RR(*tree);
		}
		else {
			*tree = rotate_RL(*tree);
		}
	}

	return *tree;
}

/* ========== 트리 관련 =========== */

void copy_data(CHAMPION *data, CHAMPION *target) {
	data->position = target->position;
	data->name = target->name;
	data->hp = target->hp;
	data->attack = target->attack;
	data->shield = target->shield;
}

/* ========== 주요 함수 =========== */

CHAMPION *SearchByName_BT(CHAMPION *root, char *name) {
	CHAMPION *result = root;
	while (result != NULL) {
		if (strcmp(name, result->name) < 0) { result = result->left; }
		else if (strcmp(name, result->name) == 0) { return result; }
		else { result = result->right; }
	}
	return result;			// result == NULL
}

CHAMPION *Insert_BT(CHAMPION **root, char *P, char *N, int H, int A, int S) {

	if (*root == NULL) {
		*root = (CHAMPION *)malloc(sizeof(CHAMPION));
		(*root)->position = P;
		(*root)->name = N;
		(*root)->hp = H;
		(*root)->attack = A;
		(*root)->shield = S;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	else if (strcmp(N, (*root)->name) < 0) {
		(*root)->left = Insert_BT(&((*root)->left), P, N, H, A, S);
		*root = make_AVL(root);
	}
	else if (strcmp(N, (*root)->name) > 0) {
		(*root)->right = Insert_BT(&((*root)->right), P, N, H, A, S);
		*root = make_AVL(root);
	}
	else {
		printf("이름이 중복됩니다.\n");
		char end = 0;
		while ((end = _getch()) != ENTER);
	}

	return *root;
}

void Delete_BT(CHAMPION *root, char *N) {
	CHAMPION *data = root;		// search Node 삭제의 대상이 되면 target 
	CHAMPION *parent = NULL;	// target의 부모
	CHAMPION *child;			// target의 자식
	CHAMPION *succ;				// successor 후임자. 즉, 후계자를 의미
	CHAMPION *succ_parent;		// successor의 부모
	start_check(&checkTime);
	while ((data != NULL) && (strcmp(N, data->name))) {  // 빡친다...
		parent = data;
		if (strcmp(N, data->name) < 0) { data = data->left; }
		else { data = data->right; }
	}

	if (data == NULL) {
		printf("해당 챔피언이 존재하지 않습니다.\n");
		end_check(&checkTime);
		return;
	}

	if ((data->left == NULL) && (data->right == NULL)) {		// none side ( leaf node )
		if (parent != NULL) {
			if (parent->left == data) { parent->left = NULL; }
			else { parent->right = NULL; }
		}
		else { root = NULL; }
	}
	else if ((data->left == NULL) || (data->right == NULL)) {	// one side
		if (data->left != NULL) { child = data->left; }
		else { child = data->right; }

		if (parent != NULL) {	// 부모 자리로 땡겨오기
			if (parent->left == data) { parent->left = child; }
			else { parent->right = child; }
		}
		else root = child;
	}
	else {	// both side
		succ_parent = data;
		succ = data->left;				// 왼쪽 후계자 선택 루틴
		while (succ->right != NULL) {	// search for successor on left sub tree 
			succ_parent = succ;
			succ = succ->right;			// 왼쪽 서브트리의 가장 우측. 즉, 최대값
		}
		if (succ_parent->left == succ) { succ_parent->left = succ->left; }		// while문 안 통과. 즉, succ가 left sub tree의 최대값
		else { succ_parent->right = succ->left; }
		copy_data(data, succ);
		data = succ;
	}
	free(data);

	printf("성공적으로 삭제하였습니다.\n");
	end_check(&checkTime);
}

void PrintAll_BT(CHAMPION *root) {

	if (root) {		// root != NULL
		PrintAll_BT(root->left);
		printf("position : %-10s, name : %-20s, hp : %5d, attack : %5d, shield : %5d\n", root->position, root->name, root->hp, root->attack, root->shield);
		PrintAll_BT(root->right);
	}
}

/* ========== 주요 함수 =========== */

/* ========== 기타 함수 =========== */

int select_num(void) {
	system("cls");

	int choice = 0;

	printf("2. save_file\n");
	printf("3. SearchByName_BT\n");
	printf("4. Insert_BT\n");
	printf("5. Delete_BT\n");
	printf("6. PrintAll_BT\n");
	printf("7. SortByName_BT\n");
	printf("8. Exit\n");
	printf("숫자를 입력하세요 : ");

	while (choice<2 || choice>8) scanf("%d", &choice);

	while (getchar() != '\n');					// 버퍼 비우기, fflush 먹통일 때 사용
	return choice;
}

void sample_setting(CHAMPION **root) {
	char P_buf[CHAMPION_POSITION];
	char *P;
	char N_buf[CHAMPION_NAME];
	char *N;
	int H, A, S;
	FILE *filePointer;
	char *fileName = "SUB23Dic.txt";

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
		Insert_BT(root, P, N, H, A, S);
	}
	fclose(filePointer);
}

void save_file(CHAMPION *root, FILE *file_pointer) {

	if (root) {		// root != NULL
		save_file(root->left, file_pointer);
		fprintf(file_pointer, "%s %s %d %d %d\n", root->position, root->name, root->hp, root->attack, root->shield);
		save_file(root->right, file_pointer);
	}

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

/* ========== 기타 함수 =========== */

int main() {
	CHAMPION *root = NULL;
	start_check(&checkTime);
	sample_setting(&root);
	end_check(&checkTime);

	int select = 0;

	while ((select = select_num()) != 8) {
		if (select == 2) {
			FILE *file_pointer;
			char *file_name = "SUB23Dic_rev.txt";

			file_pointer = fopen(file_name, "w");
			save_file(root, file_pointer);
			fclose(file_pointer);
		}
		if (select == 3) {
			char *N = catch_name();
			CHAMPION *result = SearchByName_BT(root, N);
			free(N);

			start_check(&checkTime);
			if (result == NULL) printf("검색 결과가 없습니다.\n");
			else printf("position : %-10s, name : %-20s, hp : %5d, attack : %5d, shield : %5d\n", root->position, root->name, root->hp, root->attack, root->shield);
			end_check(&checkTime);
		}
		else if (select == 4) {
			char *N = catch_name();
			if (SearchByName_BT(root, N) != NULL) {
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
					start_check(&checkTime);
					Insert_BT(&root, P, N, H, A, S);
					end_check(&checkTime);
				}
			}

		}
		else if (select == 5) {
			char *N = catch_name();
			Delete_BT(root, N);
			free(N);
		}
		else if (select == 6) {
			system("cls");
			start_check(&checkTime);
			PrintAll_BT(root);
			end_check(&checkTime);
		}
		else if (select == 7) {

		}
		else if (select == 8) {
			exit(0);
		}
		else { printf("select_num() error has occur\n"); }
	}
	return 0;
}