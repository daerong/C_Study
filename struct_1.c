#include <stdio.h>

typedef struct point {			// 좌표 입력
	int x;
	int y;
} POINT;

int quadrant(POINT t) {
	if (t.x > 0 && t.y > 0){
		return 1;
	} else if (t.x < 0 && t.y > 0) {
		return 2;
	} else if (t.x < 0 && t.y < 0) {
		return 3;
	} else if (t.x > 0 && t.y < 0) {
		return 4;
	} else {
		return 0;
	}
}

int main(void) {

	POINT p;

	int i;

	printf("사분면을 검색할 좌표를 입력하시오: ");
	scanf("%d %d", &p.x, &p.y);						// 좌표입력
	
	i = quadrant(p);

	if (i) {
		printf("%d사분면 입니다.", i);
	} else {
		printf("축위에 있습니다.");
	}

	return 0;

}