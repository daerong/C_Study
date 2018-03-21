#include <stdio.h>

typedef struct point {			// ��ǥ �Է�
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

	printf("��и��� �˻��� ��ǥ�� �Է��Ͻÿ�: ");
	scanf("%d %d", &p.x, &p.y);						// ��ǥ�Է�
	
	i = quadrant(p);

	if (i) {
		printf("%d��и� �Դϴ�.", i);
	} else {
		printf("������ �ֽ��ϴ�.");
	}

	return 0;

}