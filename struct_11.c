#include <stdio.h>

typedef enum shape_type { TRI = 0, RECT, CIR } SHAPE_TYPE;
const char type_txt[3][4] = { "TRI", "RECT", "CIR" };

typedef struct shape {			// 도형
	SHAPE_TYPE type;			// 도형의 종류
	union {
		struct { int base, height; } TRI;
		struct { int width, height; } RECT;
		struct { int radius; } CIR;
	} LINE;
} SHAPE;

int main() {

	SHAPE one;
	int input;
	
	printf("입력할 도형을 선택하세요(0:삼각형, 1:사각형, 2:원) : ");
	scanf("%d", &input);

	one.type = input;
	
	switch (one.type) {
	case TRI :
		printf("밑변과 높이를 순서대로 입력하시오.");
		scanf("%d %d", &one.LINE.TRI.base, &one.LINE.TRI.height);
		printf("입력한 도형은 %d이고 밑변은 %d, 높이는 %d입니다.", one.type, one.LINE.TRI.base, one.LINE.TRI.height);
		break;
	case RECT:
		printf("가로와 세로를 순서대로 입력하시오.");
		scanf("%d %d", &one.LINE.RECT.width, &one.LINE.RECT.height);
		printf("입력한 도형은 %d이고 가로는 %d, 세로는 %d입니다.", one.type, one.LINE.RECT.width, one.LINE.RECT.height);
		break;
	case CIR : 
		printf("반지름을 입력하시오.");
		scanf("%d", &one.LINE.CIR.radius);
		printf("입력한 도형은 %d이고 반지름은 %d입니다.", one.type, one.LINE.CIR.radius);
		break;
	default :
		printf("잘못 선택하셨습니다. 프로그램을 다시 실행해주세요.");
	}

	/*
	const char type_txt[] = { "TRI", "RECT", "CIR" };
	printf("입력한 도형은 %s입니다.", *type_txt[input]);			// 가변 길이 배열은 visual studio에서 지원하지 않음
	*/
	return 0;
}