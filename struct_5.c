#include <stdio.h>

typedef struct point {			// ��ǥ �Է�
	double x;
	double y;
} POINT;

typedef struct vector {
	POINT start, end;					// a�� ���� ��ġ , b�� �� ��ġ
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

	printf("���� 1�� ���� ��ǥ�� �Է��ϼ��� : ");
	scanf("%lf %lf", &v[0].start.x, &v[0].start.y);

	printf("���� 1�� �� ��ǥ�� �Է��ϼ��� : ");
	scanf("%lf %lf", &v[0].end.x, &v[0].end.y);

	printf("���� 2�� ���� ��ǥ�� �Է��ϼ��� : ");
	scanf("%lf %lf", &v[1].start.x, &v[1].start.y);

	printf("���� 2�� �� ��ǥ�� �Է��ϼ��� : ");
	scanf("%lf %lf", &v[1].end.x, &v[1].end.y);

	VECTOR result = vector_add(v[0], v[1]);

	printf("�� ������ �� ������ �������� (%.2lf, %.2lf) �� ���� (%.2lf, %.2lf)�Դϴ�.", result.start.x, result.start.y, result.end.x, result.end.y);

	return 0;

}