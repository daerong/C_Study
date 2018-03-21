#include <stdio.h>

typedef struct point {			// 좌표 입력
	int x;
	int y;
} POINT;

typedef struct rectangle {
	POINT a, b;					// a는 오른쪽 상단, b는 왼쪽 하단의 좌표를 저장 
} RECT;

int area(RECT r) {
	int w, h;
	w = r.b.x - r.a.x;
	h = r.b.y - r.a.y;

	return w*h;
}

int perimeter(RECT r) {
	int w, h;
	w = r.b.x - r.a.x;
	h = r.b.y - r.a.y;

	return 2 * (w + h);
}

int is_square(RECT r) {
	int w, h;
	w = r.b.x - r.a.x;
	h = r.b.y - r.a.y;

	if (w == h) {
		return 1;
	}
	else {
		return 0;
	}
}

int main(void) {

	RECT r;

	printf("우측 상단 좌표를 입력하시오: ");
	scanf("%d %d", &r.a.x, &r.a.y);	

	printf("우측 상단 좌표를 입력하시오: ");
	scanf("%d %d", &r.b.x, &r.b.y);
	
	printf("r의 넓이는 %d입니다.\n", area(r));
	printf("r의 둘레는 %d입니다.\n", perimeter(r));
	printf("r의 정사각형 유무는 %d입니다. (1:TRUE, 0:FALSE)\n", is_square(r));

	return 0;

}