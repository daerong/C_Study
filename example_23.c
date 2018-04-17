#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct term {
	int row;
	int col;
	int value;
	struct term *rLink;
	struct term *dLink;
} term;

term *set_init(int col, int row) {	// 3 by 4
	term *init = NULL, *prev = NULL, *data = NULL, *upper = NULL;
	init = (term *)malloc(sizeof(term));
	init->rLink = NULL;
	init->dLink = NULL;
	upper = init;
	prev = init;
	for (int i = 1; i < row*col; i++) {
		data = (term *)malloc(sizeof(term));
		data->rLink = NULL;
		data->dLink = NULL;
		if (i >= row) {
			upper->dLink = data;
			upper = upper->rLink;
		}
		else {
			data->dLink = NULL;
		}
		prev->rLink = data;
		prev = data;
	}
	data = init;
	prev = init;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (j == 0 && i != 0) {
				prev->rLink = NULL;
			}
			data->col = i + 1;
			data->row = j + 1;
			data->value = 0;
			prev = data;
			data = data->rLink;
		}
	}

	return init;
}

void print_term(term *target) {
	term *data= NULL, *upper = target;
	while (data != NULL || upper != NULL) {
		data = upper;
		while (data != NULL) {
			printf("%d ", data->value);
			data = data->rLink;
		}
		printf("\n");
		upper = upper->dLink;
	}
}

void insert_data(term *target, int col, int row, int value) {
	term *data = NULL, *upper = target;
	while (data != NULL || upper != NULL) {
		data = upper;
		while (data != NULL) {
			if (data->col == col && data->row == row) { data->value = value; }
			data = data->rLink;
		}
		upper = upper->dLink;
	}
}
void change_colrow(term *target) {
	term *backup = (term *)malloc(sizeof(term));
	term *data = NULL, *upper = target;
	while (data != NULL || upper != NULL) {
		data = upper;
		while (data != NULL) {
			memcpy(backup, data, sizeof(term));
			data->col = backup->row;
			data->row = backup->col;
			data->dLink = backup->rLink;
			data->rLink = backup->dLink;
			data = backup->rLink;
		}
		upper = upper->rLink;
	}
	free(backup);
}

int main() {

	term *data = set_init(3, 4);
	// print_term(data);
	insert_data(data, 1, 1, 1);
	insert_data(data, 1, 2, 3);
	insert_data(data, 1, 3, 5);
	insert_data(data, 1, 4, 7);
	insert_data(data, 2, 1, 5);
	insert_data(data, 2, 2, 7);
	insert_data(data, 2, 3, 9);
	insert_data(data, 2, 4, 4);
	insert_data(data, 3, 1, 4);
	insert_data(data, 3, 2, 9);
	insert_data(data, 3, 3, 5);
	insert_data(data, 3, 4, 9);
	// print_term(data);
	change_colrow(data);
	print_term(data);

	return 0;
}