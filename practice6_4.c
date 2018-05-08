#include <stdio.h>
#include <malloc.h>

typedef char element;
typedef struct DQNode {
	element data;
	struct DQNode *llink;
	struct DQNode *rlink;
} DQNode;

typedef struct {
	DQNode *front, *rear;
} DQueType;

DQueType *createDQue() {
	DQueType *DQ;
	DQ = (DQueType *)malloc(sizeof(DQueType));
	DQ->front = NULL;
	DQ->rear = NULL;

	return DQ;
}

int isEmpty(DQueType *Q) {
	if (Q->front == NULL) {
		printf(" \n Linked Queue is empty! \n");
		return 1;
	}
	else return 0;
}

void insertFront(DQueType *DQ, element item) {
	DQNode *newNode = (DQNode *)malloc(sizeof(DQNode));
	newNode->data = item;
	if (DQ->front == NULL) {
		DQ->front = newNode;
		DQ->rear = newNode;
		newNode->rlink = NULL;
		newNode->llink = NULL;
	}
	else {
		DQ->front->llink = newNode;
		newNode->rlink = DQ->front;
		newNode->llink = NULL;
		DQ->front = newNode;
	}
}

void insertRear(DQueType *DQ, element item) {
	DQNode *newNode = (DQNode *)malloc(sizeof(DQNode));
	newNode->data = item;
	if (DQ->rear == NULL) {
		DQ->front = newNode;
		DQ->rear = newNode;
		newNode->rlink = NULL;
		newNode->llink = NULL;
	}
	else {
		DQ->rear->rlink = newNode;
		newNode->rlink = NULL;
		newNode->llink = DQ->rear;
		DQ->rear = newNode;
	}
}

element deleteFront(DQueType *DQ) {
	DQNode *old = DQ->front;
	element item;
	if (isEmpty(DQ)) return 0;
	else {
		item = old->data;
		if (DQ->front->rlink == NULL) {
			DQ->front = NULL;
			DQ->rear = NULL;
		}
		else {
			DQ->front = DQ->front->rlink;
			DQ->front->llink = NULL;
		}
		free(old);
		return item;
	}
}

element deleteRear(DQueType *DQ) {
	DQNode *old = DQ->rear;
	element item;
	if (isEmpty(DQ)) return 0;
	else {
		item = old->data;
		if (DQ->front->llink == NULL) {
			DQ->front = NULL;
			DQ->rear = NULL;
		}
		else {
			DQ->front = DQ->rear->llink;
			DQ->front->rlink = NULL;
		}
		free(old);
		return item;
	}
}

element peekFront(DQueType *DQ) {
	element item;
	if (isEmpty(DQ)) return 0;
	else {
		item = DQ->front->data;
		return item;
	}
}

element peekRear(DQueType *DQ) {
	element item;
	if (isEmpty(DQ)) return 0;
	else {
		item = DQ->rear->data;
		return item;
	}
}

void printDQ(DQueType *DQ) {
	DQNode *temp = DQ->front;
	printf("DeQue : [");
	while (temp) {
		printf("%3c", temp->data);
		temp = temp->rlink;
	}
	printf(" ]");
}

int main() {

	DQueType *DQ1 = createDQue();
	element data;
	printf("\n ***** µ¥Å¥ ¿¬»ê ***** \n");
	printf("\n front »ðÀÔ A>> ");	insertFront(DQ1, 'A');	printDQ(DQ1);
	printf("\n front »ðÀÔ B>> ");	insertFront(DQ1, 'B');	printDQ(DQ1);
	printf("\n rear »ðÀÔ C>> ");		insertRear(DQ1, 'C');	printDQ(DQ1);
	printf("\n front »èÁ¦ >> ");		data = deleteFront(DQ1);	printDQ(DQ1);
	printf("\t\t»èÁ¦ µ¥ÀÌÅÍ %c", data);
	printf("\n rear »èÁ¦ >> ");		data = deleteRear(DQ1);		printDQ(DQ1);
	printf("\t\t»èÁ¦ µ¥ÀÌÅÍ %c", data);
	printf("\n rear »ðÀÔ D>> ");		insertRear(DQ1, 'D');	printDQ(DQ1);
	printf("\n front »ðÀÔ E>> ");	insertFront(DQ1, 'E');	printDQ(DQ1);
	printf("\n front »ðÀÔ F>> ");	insertFront(DQ1, 'F');	printDQ(DQ1);

	data = peekFront(DQ1);	printf("\n peek Front item : %c \n", data);
	data = peekRear(DQ1);	printf("\n peek Rear item : %c \n", data);
	getchar();

	return 0;
}