#include <stdio.h>
#include <stdlib.h>

void insert_arr(int *arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ��° ���� ������ �Է��Ͻÿ� : ", i + 1);
		scanf("%d", (arr + i));
	}
}

void sum_arr(int *arr, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += *(arr + i);
	}
	printf("���� %d�Դϴ�.", sum);
}

int main() {

	int arr_size;
	int *arr_target;

	printf("������ ���� : ");
	scanf("%d", &arr_size);

	arr_target = (int *)malloc(arr_size * sizeof(int));

	insert_arr(arr_target, arr_size);

	sum_arr(arr_target, arr_size);

	free(arr_target);
	

	return 0;
}