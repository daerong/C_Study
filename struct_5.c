#include <stdio.h>

typedef struct point {			// 좌표 입력
	double x;
	double y;
} POINT;

typedef struct vector {
	POINT start, end;					// a는 시작 위치 , b는 끝 위치
} VECTOR;

VECTOR vector_add(VECTOR v1, VECTOR v2) {
	VECTOR target;
	target.start.x = v1.start.x + v2.start.x;
	target.start.y = v1.start.y + v2.start.y;
	target.end.x = v1.end.x + v2.end.x;
	target.end.y = v1.end.y + v2.end.y;

	return target;
}


int main(void) {

	VECTOR v[2];

	printf("벡터 1의 시작 좌표를 입력하세요 : ");
	scanf("%lf %lf", &v[0].start.x, &v[0].start.y);

	printf("벡터 1의 끝 좌표를 입력하세요 : ");
	scanf("%lf %lf", &v[0].end.x, &v[0].end.y);

	printf("벡터 2의 시작 좌표를 입력하세요 : ");
	scanf("%lf %lf", &v[1].start.x, &v[1].start.y);

	printf("벡터 2의 끝 좌표를 입력하세요 : ");
	scanf("%lf %lf", &v[1].end.x, &v[1].end.y);

	VECTOR result = vector_add(v[0], v[1]);

	printf("두 벡터의 합 벡터의 시작점은 (%.2lf, %.2lf) 끝 점은 (%.2lf, %.2lf)입니다.", result.start.x, result.start.y, result.end.x, result.end.y);

	return 0;

}