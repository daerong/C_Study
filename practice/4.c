#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

#define MAX_SIZE 13500

int main() {
	
	short array[13500] = { 0 };
	array[0] = 1;
	int max;
	int count = 0;

	do {
		scanf("%d", &max);
	} while (max < 0 || max > MAX_SIZE);

	for (int i = 1; i <= max ; i++) {			// i�� 9�� ���� Ƚ��
		for (int j = max; j >= 0; j--) {		// j�� 9 ���ϰ� �ִ� �ڸ���
			array[j] = array[j] * 9;
			if (array[j] >= 10) {
				array[j + 1] += array[j] / 10;
				array[j] = array[j] % 10;
			}
		}135
		int k = max;
		while (1) {
			if (array[k] != 0) {
				if (array[k] == 9) {
					count++;
				}
				break;
			}
			k--;
		}
	}
	/*
	for (int j = max - 1; j >= 0; j--) {		// 9�� max�� ���� ��
		printf("%d", array[j]);
	}
	*/
	system("cls");
	printf("%d\n", count);

	return 0;
}