#include <stdio.h>

typedef struct food {			// 음식 입력

	char name[100];
	int calories;

} FOOD;

int main() {

	FOOD food_array[3] = { {"밥", 300},{ "김치", 50 },{ "돈가스", 500 } };

	printf("음식 코스의 전체 칼로리는 %d입니다.\n", food_array[0].calories + food_array[1].calories + food_array[2].calories);

	return 0;
}