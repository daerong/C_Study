#include <stdio.h>

typedef struct food {			// ���� �Է�

	char name[100];
	int calories;

} FOOD;

int main() {

	FOOD food_array[3] = { {"��", 300},{ "��ġ", 50 },{ "������", 500 } };

	printf("���� �ڽ��� ��ü Į�θ��� %d�Դϴ�.\n", food_array[0].calories + food_array[1].calories + food_array[2].calories);

	return 0;
}