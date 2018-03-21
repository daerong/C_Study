#include <stdio.h>

typedef enum shape_type { TRI = 0, RECT, CIR } SHAPE_TYPE;
const char type_txt[3][4] = { "TRI", "RECT", "CIR" };

typedef struct shape {			// ����
	SHAPE_TYPE type;			// ������ ����
	union {
		struct { int base, height; } TRI;
		struct { int width, height; } RECT;
		struct { int radius; } CIR;
	} LINE;
} SHAPE;

int main() {

	SHAPE one;
	int input;
	
	printf("�Է��� ������ �����ϼ���(0:�ﰢ��, 1:�簢��, 2:��) : ");
	scanf("%d", &input);

	one.type = input;
	
	switch (one.type) {
	case TRI :
		printf("�غ��� ���̸� ������� �Է��Ͻÿ�.");
		scanf("%d %d", &one.LINE.TRI.base, &one.LINE.TRI.height);
		printf("�Է��� ������ %d�̰� �غ��� %d, ���̴� %d�Դϴ�.", one.type, one.LINE.TRI.base, one.LINE.TRI.height);
		break;
	case RECT:
		printf("���ο� ���θ� ������� �Է��Ͻÿ�.");
		scanf("%d %d", &one.LINE.RECT.width, &one.LINE.RECT.height);
		printf("�Է��� ������ %d�̰� ���δ� %d, ���δ� %d�Դϴ�.", one.type, one.LINE.RECT.width, one.LINE.RECT.height);
		break;
	case CIR : 
		printf("�������� �Է��Ͻÿ�.");
		scanf("%d", &one.LINE.CIR.radius);
		printf("�Է��� ������ %d�̰� �������� %d�Դϴ�.", one.type, one.LINE.CIR.radius);
		break;
	default :
		printf("�߸� �����ϼ̽��ϴ�. ���α׷��� �ٽ� �������ּ���.");
	}

	/*
	const char type_txt[] = { "TRI", "RECT", "CIR" };
	printf("�Է��� ������ %s�Դϴ�.", *type_txt[input]);			// ���� ���� �迭�� visual studio���� �������� ����
	*/
	return 0;
}