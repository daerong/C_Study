#include <stdio.h>
#include <Windows.h>

#define STAR '*'

int printStars(int FLOOR, int length) {

	if (FLOOR >= length) {
		for (int j = 1; j <= length; j++) {
			printf("*");
			Sleep(1000);
		}

		printf("\n");
		return printStars(FLOOR, length + 1);
	}
	else {
		return 0;
	}

	for (int i = 1; i <= FLOOR; i++) {

		for (int j = 1; j <= i; j++) {
			printf("*");
			Sleep(1000);
		}

		printf("\n");
	}
}

int main()
{
	int FLOOR;
	printf("출력할 층 수를 입력하세요 : ");
	scanf("%d", &FLOOR);
	system("cls");

	printStars(FLOOR, 1);

	return 0;
}