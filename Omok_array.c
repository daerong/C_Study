#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#define BOARD_SIZE 19
#define BUF_SIZE 255

#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESCAPE 27
#define OPENBRACKET 91
#define CLOSEBRACKET 93

// 모양 기호 ◐, ● ,○
// 방향 기호 →, ↓, ↗, ↘
// 격자 기호 ┌─, ┬─, ┐, ├─, ┼─, ┤, └─, ┴─, ┘



typedef struct GAME_BOARD {
	int type;		// ◐ = 0, ● = 1 ,○ = 2, ★ = 3, ☆ = 4
	int col;
	int row;
	int turn;
} GAME_BOARD;

const GAME_BOARD RETURN_MENU = { 0, 20, 20, 0 };

/* 스택 관련 */

typedef struct BOARD_STACK {
	GAME_BOARD data;
	struct BOARD_STACK *link;
} BOARD_STACK;

BOARD_STACK *prevTop = NULL;

void prevFreeStack() {
	BOARD_STACK *next = NULL;
	while (prevTop != NULL) {
		next = prevTop->link;
		free(prevTop);
		prevTop = next;
	}
}
void prevPush(GAME_BOARD data) {
	BOARD_STACK *newData = (BOARD_STACK *)malloc(sizeof(BOARD_STACK));
	newData->data = data;
	if (prevTop == NULL) {
		newData->link = NULL;
		prevTop = newData;
	}
	else {
		newData->link = prevTop;
		prevTop = newData;
	}
}
GAME_BOARD prevPop() {
	BOARD_STACK *next = NULL;
	if (prevTop != NULL) {
		GAME_BOARD returnData = prevTop->data;
		next = prevTop->link;
		free(prevTop);
		if (next == NULL) prevTop = NULL;
		else prevTop = next;
		return returnData;
	}
	else return RETURN_MENU;
}

BOARD_STACK *nextTop = NULL;

void nextFreeStack() {
	BOARD_STACK *next = NULL;
	while (nextTop != NULL) {
		next = nextTop->link;
		free(nextTop);
		nextTop = next;
	}
}
void nextPush(GAME_BOARD data) {
	BOARD_STACK *newData = (BOARD_STACK *)malloc(sizeof(BOARD_STACK));
	newData->data = data;
	if (nextTop == NULL) {
		newData->link = NULL;
		nextTop = newData;
	}
	else {
		newData->link = nextTop;
		nextTop = newData;
	}
}
GAME_BOARD nextPop() {
	BOARD_STACK *next = NULL;
	if (nextTop != NULL) {
		GAME_BOARD returnData = nextTop->data;
		next = nextTop->link;
		free(nextTop);
		if (next == NULL) nextTop = NULL;
		else nextTop = next;
		return returnData;
	}
	else return RETURN_MENU;
}

typedef struct QUEUE {
	BOARD_STACK *front;		// 디큐
	BOARD_STACK *rear;		// 인큐
	int count;
} QUEUE;

void InitQueue(QUEUE *queue) {
	queue->front = queue->rear = NULL;	// front와 rear를 NULL로 설정
	queue->count = 0;					// 보관 개수를 0으로 설정
}

int IsEmpty(QUEUE *queue) {
	return queue->count == 0;	// 보관 개수가 0이면 빈 상태
}

void Enqueue(QUEUE *queue, GAME_BOARD data) {
	BOARD_STACK *new_node = (BOARD_STACK *)malloc(sizeof(BOARD_STACK));		//노드 생성
	new_node->data = data;		// 데이터 설정
	new_node->link = NULL;

	if (IsEmpty(queue)) {
		queue->front = new_node;	// 맨 앞을 now로 설정       
	}
	else {
		queue->rear->link = new_node;	// 맨 뒤의 다음을 now로 설정
	}
	queue->rear = new_node;		// 맨 뒤를 now로 설정   
	queue->count++;
}

GAME_BOARD Dequeue(QUEUE *queue){
	GAME_BOARD stoneData;
	BOARD_STACK *useNode;
	if (IsEmpty(queue))			// 큐가 비었을 때
	{
		return RETURN_MENU;
	}
	useNode = queue->front;			// 맨 앞의 노드를 now에 기억
	stoneData = useNode->data;		// 반환할 값은 now의 data로 설정
	queue->front = useNode->link;	// 맨 앞은 now의 다음 노드로 설정
	free(useNode);					// now 소멸
	queue->count--;					// 보관 개수를 1 감소
	return stoneData;
}

/* /스택 관련 */

void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void menu_choice(int *select) {
	system("cls");
	*select = 0;
	while (*select < 1 || *select > 4) {
		printf("1. 새로하기\n");
		printf("2. 불러오기\n");
		printf("3. 저장하기\n");
		printf("4. 종료하기\n");
		printf("select menu : ");
		scanf("%d", select);
		while (getchar() != '\n');
	}
}

void remove_stone(GAME_BOARD list[][BOARD_SIZE], GAME_BOARD target) {
	list[target.col][target.row].type = 0;
	list[target.col][target.row].turn = 0;
}
void add_stone(GAME_BOARD list[][BOARD_SIZE], GAME_BOARD target) {
	list[target.col][target.row].type = target.type;
	list[target.col][target.row].turn = target.turn;
}

void draw_board(GAME_BOARD locate[][BOARD_SIZE]) {
	system("cls");
	// 윗줄 격자 생성
	printf("┌─");
	for (int j = 0; j < BOARD_SIZE; j++) {
		printf("┬─");
	}
	printf("┐\n");

	// 메인 바둑판
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf("├─");						// Y좌표계 출력
		for (int j = 0; j < BOARD_SIZE; j++) {
			switch (locate[i][j].type) {
			case 0: printf("┼─");	break;
			case 1: printf("●");	break;
			case 2: printf("○");	break;
			case 3: printf("★");	break;
			case 4: printf("☆");	break;
			}
		}
		printf("┤\n");
	}

	// 아래줄 격자 생성
	printf("└─");
	for (int j = 0; j < BOARD_SIZE; j++) {
		printf("┴─");
	}
	printf("┘\n");
}
GAME_BOARD get_position(GAME_BOARD board[][BOARD_SIZE], int *turn) {
	GAME_BOARD took_stone;
	int end = 1;
	int x = 9, y = 9;					// 좌표
	int cursor_x = 21, cursor_y = 10;	// 화면에 보이는 위치
	do {
		int z = _getch(); // char c 변수에 문자를 입력 받는다

		switch (z) {
		case RIGHT:
			++x, cursor_x += 2;
			if (x >= BOARD_SIZE) --x, cursor_x -= 2;	// 만약 오목판을 넘어선다면 입력이 무시가 됩니다. 
			gotoxy(cursor_x, cursor_y); // 아니라면 커서를 입력한 좌표로 이동합니다.
			break; // 그리고 다시 입력을 받기 위해 swtich문을 빠져 나가며 다시 루트가 됩니다.

		case LEFT:
			--x, cursor_x -= 2;
			if (x < 0) ++x, cursor_x += 2;
			gotoxy(cursor_x, cursor_y);
			break;

		case UP:
			--y, --cursor_y;
			if (y < 0) ++y, ++cursor_y;
			gotoxy(cursor_x, cursor_y);
			break;

		case DOWN:
			++y, ++cursor_y;
			if (y >= BOARD_SIZE) --y, --cursor_y;
			gotoxy(cursor_x, cursor_y);
			break;

		case ESCAPE:
			return RETURN_MENU;

		case OPENBRACKET:
			took_stone = prevPop();
			if (took_stone.turn != 0) {
				nextPush(took_stone);
				remove_stone(board, took_stone);
				(*turn)--;
			}
			draw_board(board);
			break;
		case CLOSEBRACKET:
			took_stone = nextPop();
			if (took_stone.turn != 0) {
				prevPush(took_stone);
				add_stone(board, took_stone);
				(*turn)++;
			}
			draw_board(board);
			break;
		case ENTER:					//ENTER가 입력되면 현재 위치를 오목 배열에 저장
			if (board[y][x].type == 0) {
				if (*turn % 2) {
					board[y][x].type = 2;				// status[HEIGHT][WIDTH]에 대입
				}
				else {
					board[y][x].type = 1;
				}
				board[y][x].turn = *turn;
				(*turn)++;
				took_stone = board[y][x];
				end = 0;					// 무한루프를 벗어납니다.
			}
			break;
		}
	} while (end);

	return took_stone;
}

void list_setting(GAME_BOARD list[][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			list[i][j].type = 0;
			list[i][j].col = i;
			list[i][j].row = j;
			list[i][j].turn = 0;
		}
	}
}

void save_file(QUEUE *queue) {
	FILE *file_pointer_prev;
	FILE *file_pointer_next;
	char *file_prev = "prev_stack.txt";
	char *file_next = "next_stack.txt";

	while (nextTop != NULL) {
		Enqueue(queue, nextPop());
	}
	while (queue->count > 0) {
		nextPush(Dequeue(queue));
	}
	file_pointer_next = fopen(file_next, "w");
	while (nextTop != NULL) {
		fprintf(file_pointer_next, "\n%2d %2d %2d %3d", nextTop->data.type, nextTop->data.col, nextTop->data.row, nextTop->data.turn);
		nextPop();
	}
	fclose(file_pointer_next);
	
	while (prevTop != NULL) {
		Enqueue(queue, prevPop());
	}
	while (queue->count > 0) {
		prevPush(Dequeue(queue));
	}
	file_pointer_prev = fopen(file_prev, "w");
	while (prevTop != NULL) {
		fprintf(file_pointer_prev, "\n%2d %2d %2d %3d", prevTop->data.type, prevTop->data.col, prevTop->data.row, prevTop->data.turn);
		prevPop();
	}
	fclose(file_pointer_prev);
}
int load_file(GAME_BOARD list[][BOARD_SIZE]) {
	GAME_BOARD use_stone;
	int turn = 0;
	FILE *file_pointer_prev;
	FILE *file_pointer_next;
	char *file_prev = "prev_stack.txt";
	char *file_next = "next_stack.txt";

	char buf[BUF_SIZE];		// 한줄씩 읽어서 저장할 배열선언

	file_pointer_prev = fopen(file_prev, "r");
	if (file_pointer_prev == NULL) {
		printf("Error : Not exist file\n");
		return -1;
	}

	while (feof(file_pointer_prev) == 0) {
		fgets(buf, BUF_SIZE, file_pointer_prev);
		fscanf(file_pointer_prev, "%2d %2d %2d %3d", &use_stone.type, &use_stone.col, &use_stone.row, &use_stone.turn);
		// printf("%2d %2d %2d %3d\n", use_stone.type, use_stone.col, use_stone.row, use_stone.turn);
		prevPush(use_stone);
		list[use_stone.col][use_stone.row].type = use_stone.type;
		list[use_stone.col][use_stone.row].col = use_stone.col;
		list[use_stone.col][use_stone.row].row = use_stone.row;
		list[use_stone.col][use_stone.row].turn = use_stone.turn;
		turn = use_stone.turn;
	}
	fclose(file_pointer_prev);

	file_pointer_next = fopen(file_next, "r");
	if (file_pointer_next == NULL) {
		printf("Error : Not exist file\n");
		return -1;
	}

	while (feof(file_pointer_next) == 0) {
		fgets(buf, BUF_SIZE, file_pointer_next);
		fscanf(file_pointer_next, "%2d %2d %2d %3d", &use_stone.type, &use_stone.col, &use_stone.row, &use_stone.turn);
		// printf("%2d %2d %2d %3d\n", use_stone.type, use_stone.col, use_stone.row, use_stone.turn);
		nextPush(use_stone);
	}
	fclose(file_pointer_prev);

	// Sleep(1000);
	return turn + 1;
}

int main() {
	int choiceMenu = 0;
	int	catchMenu = 0;
	int turn = 1;
	GAME_BOARD list[BOARD_SIZE][BOARD_SIZE];
	GAME_BOARD last_stone;
	list_setting(list);
	QUEUE queue;
	InitQueue(&queue);

	do {
		menu_choice(&choiceMenu);
		if (choiceMenu == 1 || choiceMenu == 2) {			// 1. 새로하기, 2. 불러오기
			if (choiceMenu == 1) {
				prevFreeStack();
				nextFreeStack();
				list_setting(list);
				turn = 1;
			}
			else if (choiceMenu == 2) {
				turn = load_file(list);
			}
			do {
				draw_board(list);							// 바둑판 그리기
				last_stone = get_position(list, &turn);
				if (last_stone.turn == 0) break;
				else {
					nextFreeStack();
					prevPush(last_stone);
				}
			} while (1);		// !!승리조건으로 갱신하기
		}
		else if (choiceMenu == 3) {		// 3. 저장하기
			save_file(&queue);
		}
		else if (choiceMenu == 4) {		// 4. 종료하기
			exit(0);
		}
	} while (choiceMenu != 4);

	prevFreeStack();
	nextFreeStack();

	return 0;
}