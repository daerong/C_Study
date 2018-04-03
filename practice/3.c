#include <stdio.h>
#include <Windows.h>

void plus_1(int *money, int D) {		// 운임
	*money += ((D - 1) / 10 + 1) * 1000;
	// printf("%d\n", *money);
}
void plus_2(int *money, int D, int H) {		// 숙박비
	if (D >= 120) {
		*money += (H - 1) * 40000;
	}
	// printf("%d\n", *money);
}
void plus_3(int *money, int D, int H) {	// 일비
	if (D >= 120) {
		if (H <= 15) {
			*money += (int)(20000 * H * 0.5);
		}
		else if (H >= 16 && H < 30) {
			*money += (int)(20000 * 15 * 0.5);
			int k = H - 15;
			*money += (int)(20000 * k * 0.5 * 0.9);
		}
		else if (H >= 31 && H < 60) {
			*money += (int)(20000 * 15 * 0.5);
			*money += (int)(20000 * 15 * 0.5 * 0.9);
			int k = H - 30;
			*money += (int)(20000 * k * 0.5 * 0.9 * 0.8);
		}
		else {
			*money += (int)(20000 * 15 * 0.5);
			*money += (int)(20000 * 15 * 0.5 * 0.9);
			*money += (int)(20000 * 30 * 0.5 * 0.8);
			int k = H - 60;
			*money += (int)(20000 * k * 0.5 * 0.7);
		}
	}
	else {
		*money += 20000 * H;
	}
	// printf("%d\n", *money);
}
void plus_4(int *money, int D, int H) {
	*money += ((H - 1) * 3 + 1) * 5000;
	// printf("%d\n", *money);
}


int main() {

	int money = 0;

	int D, H;

	do {
		scanf("%d", &D);
	} while (D < 10 || D > 400);

	while (getchar() != '\n');

	do {
		scanf("%d", &H);
	} while (H < 1 || H > 100);

	while (getchar() != '\n');

	plus_1(&money, D);
	plus_2(&money, D, H);
	plus_3(&money, D, H);
	plus_4(&money, D, H);

	system("cls");
	printf("%d\n", money);

	return 0;
}