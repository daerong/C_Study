#include <stdio.h>

typedef struct point {			// ��ǥ �Է�
	int x;
	int y;
} POINT;

typedef struct rectangle {
	POINT a, b;					// a�� ������ ���, b�� ���� �ϴ��� ��ǥ�� ���� 
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

	printf("���� ��� ��ǥ�� �Է��Ͻÿ�: ");
	scanf("%d %d", &r.a.x, &r.a.y);	

	printf("���� ��� ��ǥ�� �Է��Ͻÿ�: ");
	scanf("%d %d", &r.b.x, &r.b.y);
	
	printf("r�� ���̴� %d�Դϴ�.\n", area(r));
	printf("r�� �ѷ��� %d�Դϴ�.\n", perimeter(r));
	printf("r�� ���簢�� ������ %d�Դϴ�. (1:TRUE, 0:FALSE)\n", is_square(r));

	return 0;

}