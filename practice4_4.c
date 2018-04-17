#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
	char data[4];
	struct ListNode *lLink;
	struct ListNode *rLink;
} listNode;

typedef struct {
	listNode *head;
} linkedList_h;


linkedList_h *createLinkedList_h(void) {
	linkedList_h *DL;
	DL = (linkedList_h *)malloc(sizeof(linkedList_h));
	DL->head = NULL;
	return DL;
}

void printList(linkedList_h *DL) {
	listNode *p;
	printf("DL = (");
	p = DL->head;
	while (p != DL->head) {
		printf("%s", p->data);
		p = p->rLink;
		if (p != NULL) {
			printf(", ");
		}
	}
	printf(")\n");
}

void insertNode(linkedList_h *DL, listNode *pre, char *x) {
	listNode *newNode;
	newNode = (listNode *)malloc(sizeof(listNode));
	strcpy(newNode->data, x);
	if (DL->head == NULL) {
		DL->head = newNode;
		newNode->rLink = NULL;
		newNode->lLink = NULL;
	}
	else {
		newNode->rLink = pre->rLink;
		pre->rLink = newNode;
		newNode->lLink = pre;
		if (newNode ->rLink !=NULL) {
			newNode->rLink->lLink = newNode;
		}
	}
}

void deleteNode(linkedList_h *DL, listNode *old) {
	if (DL->head == NULL) return;
	else if (old == NULL) return;
	else {
		old->lLink->rLink = old->rLink;
		old->rLink->lLink = old->lLink;
		free(old);
	}
}

listNode *searchNode(linkedList_h *DL, char *x) {
	listNode *temp;
	temp = DL->head;
	while (temp != NULL) {
		if (!strcmp(temp->data, x)) return temp;
		else temp = temp->rLink;
	}
	return temp;
}

int main() {


	linkedList_h *DL;
	listNode *p;
	DL = createLinkedList_h();
	printf("(1) ���� ���� ����Ʈ �����ϱ�! \n");
	printList(DL);
	getchar();

	printf("(2) ���� ���� ����Ʈ�� [��] ��� �����ϱ�! \n");
	insertNode(DL, NULL, "��");
	printList(DL); getchar();

	printf("(3) ���� ���� ����Ʈ�� [��] ��� �ڿ� [��] ��� �����ϱ�! \n");
	p = searchNode(DL, "��");
	insertNode(DL, p, "��");
	printList(DL); getchar();

	printf("(3) ���� ���� ����Ʈ�� [��] ��� �ڿ� [��] ��� �����ϱ�! \n");
	p = searchNode(DL, "��");
	insertNode(DL, p, "��");
	printList(DL); getchar();

	printf("(5) ���� ���� ����Ʈ���� [��] ��� �����ϱ�! \n");
	p = searchNode(DL, "��");
	deleteNode(DL, p);
	printList(DL); getchar();

	return 0;
}