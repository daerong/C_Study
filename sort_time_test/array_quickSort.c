#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

typedef struct NODE {
	int data;
	struct NODE *lLink;
	struct NODE *rLink;
} NODE;

typedef struct HEAD {
	NODE *head;
} HEAD;

NODE *left_end;
NODE *right_end;

HEAD *init_list() {
	HEAD *list = (HEAD *)malloc(sizeof(HEAD));
	list->head = NULL;
	return list;
}

void add_node(HEAD *list, int data) {
	NODE *target = (NODE *)malloc(sizeof(NODE));
	target->data = data;
	target->lLink = NULL;
	if (list->head == NULL) {
		target->rLink = NULL;	
		right_end = target;
	}
	else {
		target->rLink = list->head;
	}
	list->head = target;
	left_end = target;
}

void print_all(HEAD *list) {
	if (list->head == NULL) return;
	NODE *data = list->head;
	while (data != NULL) {
		printf("%d\n", data->data);
		data = data->rLink;
	}
}

void quick_sort(HEAD *list, NODE *left, NODE *right) {
	
}


int main() {

	HEAD *list = init_list();
	add_node(list, 3);
	add_node(list, 4);
	add_node(list, 5);
	add_node(list, 6);
	add_node(list, 7);
	print_all(list, left_end, right_end);


	return 0;
}