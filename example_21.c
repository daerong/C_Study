#include <stdio.h>
#include <malloc.h>
#include <string.h>

// �� ���׽��� �Է� �޾� ���׽��� ���� ���ϴ� multPoly �Լ��� �ۼ��Ͻÿ�.

typedef struct CONTENT {
	int Coefficient;		// ��
	int Exponent;			// ����
	struct CONTENT *prev_link;
	struct CONTENT *next_link;
} CONTENT;

typedef struct polynomial {
	CONTENT *content;		// ��
	int max;				// ����
} polynomial;

polynomial zeroP(void);			// 0�� ����� ����
int isZeroP(polynomial);		// 0�̸� true ��ȯ
int coef(polynomial, int);		// ������ e�� ���� ��� a�� ���ϴ� ����
int maxExp(polynomial);			// �ִ� ������ ���ϴ� ����
int addTerm(polynomial *, int a, int e);		// ���׽� p�� ������ e�� ���� ���� ��쿡 ���ο� �� <e, a>�� �߰��ϴ� ����
int delTerm(polynomial *, int e);			// ������ e�� �� <e, a>�� �����ϴ� ����
void multTerm(polynomial *, int a, int e);		// ���׽��� ��� �׿� ax^e���� ���ϴ� ����
polynomial addPoly(polynomial, polynomial);		// ���׽� p1, p2�� ���� ���ϴ� ����


polynomial multPoly(polynomial, polynomial);		// ���׽� p1�� p2�� ���� ���ϴ� ����


// �׽�Ʈ�� ���� ���
void printPoly(polynomial target);

int main() {
	
	polynomial X = zeroP();
	polynomial Y = zeroP();
	polynomial Z;
	/*
	printf("X = ");		
	printPoly(X);
	printf("Y = ");		
	printPoly(Y);
	// ���� 0���� üũ�ϴ� ����
	printf("X is 0??? : %d\n", isZeroP(X));
	printf("Y is 0??? : %d\n", isZeroP(Y));
	// ������ e�� ���� ��� a�� ���ϴ� ����
	addTerm(&X, 3, 4);
	addTerm(&X, 5, 2);
	printPoly(X);
	addTerm(&Y, 2, 2);
	addTerm(&Y, 7, 0);
	printPoly(Y);
	Z = multPoly(X, Y);
	printPoly(Z);
	printf("X�� %d�� ����� %d�Դϴ�.\n", 0, coef(X, 0));
	printf("Y�� %d�� ����� %d�Դϴ�.\n", 0, coef(Y, 0));
	printf("X�� �ִ� ������ %d�Դϴ�.\n", maxExp(X));
	printf("Y�� �ִ� ������ %d�Դϴ�.\n", maxExp(Y));
	addTerm(&X, 3, 4);
	addTerm(&X, 4, 3);
	addTerm(&X, 5, 2);
	addTerm(&X, 6, 1);
	printf("X�� %d�� ����� %d�Դϴ�.\n", 2, coef(X, 2));			// ��� 5
	printf("X�� �ִ� ������ %d�Դϴ�.\n", maxExp(X));				// ��� 4														
	printPoly(X);												// 3 * x ^ 4 + 4 * x ^ 3 + 5 * x ^ 2 + 6 * x ^ 1
	multTerm(&X, 6, 3);
	printPoly(X);												// 18 * x ^ 7 + 24 * x ^ 6 + 30 * x ^ 5 + 36 * x ^ 4	
	printf("X is 0??? : %d\n", isZeroP(X));						// ��� 0
	delTerm(&X, 2);
	printf("X�� %d�� ����� %d�Դϴ�.\n", 2, coef(X, 2));			// ��� 0
	printf("X�� �ִ� ������ %d�Դϴ�.\n", maxExp(X));				// ��� 0
	addTerm(&Y, 7, 0);
	addTerm(&Y, 2, 2);
	addTerm(&Y, 6, 7);
	addTerm(&Y, 1, 5);
	Z = addPoly(X, Y);
	printPoly(Z);
	*/
	return 0;
}

polynomial zeroP(void) {
	polynomial data;
	CONTENT *zero;
	zero = (CONTENT *)malloc(sizeof(CONTENT));
	zero->Coefficient = 0;
	zero->Exponent = 0;
	zero->prev_link = NULL;
	zero->next_link = NULL;
	data.content = zero;
	data.max = zero->Exponent;
	return data;
}
int isZeroP(polynomial target) {		// 0�̸� true ��ȯ
	CONTENT *data = target.content;
	if (data->Coefficient == 0 && data->Exponent == 0) return 1;
	else return 0;
}
int coef(polynomial target, int e) {								//  ������ e�� ���� ��� a�� ���ϴ� ����
	CONTENT *data = target.content;
	while (data != NULL) {
		if (data->Exponent == e) {
			return data->Coefficient;
		}
		data = data->next_link;
	}
	return 0;			// 0�� �����ϰ� ����� 0�� ������ �����Ƿ� 0�� �����Ͽ� ó�� 
}
int maxExp(polynomial target) {						// �ִ� ������ ���ϴ� ����
	return target.max;
}
int addTerm(polynomial *target, int a, int e) {			// ���׽� p�� ������ e�� ���� ���� ��쿡 ���ο� �� <e, a>�� �߰��ϴ� ����
	CONTENT *data = (*target).content;
	if (data->Exponent < e) {
		CONTENT *insert = (CONTENT *)malloc(sizeof(CONTENT));
		insert->Coefficient = a;
		insert->Exponent = e;
		insert->next_link = data;
		insert->prev_link = NULL;
		data->prev_link = insert;
		(*target).content = insert;
		(*target).max = e;
	}
	else {
		while (data != NULL) {
			if (data->Exponent > e) {			// e���� ū ���� �����˻�
				data = data->next_link;
			}
			else {								// e���� �۰ų� �������� ����
				if (data->Exponent != e) {		// ������ ���� �Ұ���
					CONTENT *insert = (CONTENT *)malloc(sizeof(CONTENT));
					insert->Coefficient = a;
					insert->Exponent = e;
					insert->next_link = data;
					insert->prev_link = data->prev_link;
					(data->prev_link)->next_link = insert;
					data->prev_link = insert;
					return 0;
				}
				else {							// �޶� ���� ������ �ϳ� �߻� <0, 0> = 0�̸� ������ �� �־����
					if (data->Exponent == 0 && data->Coefficient == 0) {
						data->Coefficient = a;
					}
					return 0;
				}
			}
		}
	}
	return 0;
}
int delTerm(polynomial *target, int e) {		// ������ e�� �� <e, a>�� �����ϴ� ����
	CONTENT *data = (*target).content;
	while (data != NULL) {
		if (data->Exponent == e) {							// e���� ū ���� �����˻�
			if (e == 0) {
				data->Coefficient = 0;
				return 0;
			}
			else {
				(data->next_link)->prev_link = data->prev_link;
				if (data->prev_link == NULL) {
					target->max = (data->next_link)->Exponent;
					(*target).content = data->next_link;
				}
				else {
					(data->prev_link)->next_link = data->next_link;
				}
				free(data);
				return 0;
			}
		}
		data = data->next_link;
	}
	return 0;
}
void multTerm(polynomial *target, int a, int e) {	// ���׽��� ��� �׿� ax^e���� ���ϴ� ����
	(*target).max += e;
	if (a == 0) *target = zeroP();
	else if (isZeroP(*target));
	else {
		CONTENT *data = (*target).content;
		while (data->next_link != NULL) {
			data->Coefficient *= a;
			data->Exponent += e;
			data = data->next_link;
		}
		if (data->Coefficient != 0) {
			data->Coefficient *= a;
			data->Exponent += e;
			CONTENT *insert = (CONTENT *)malloc(sizeof(CONTENT));
			insert->Coefficient = 0;
			insert->Exponent = 0;
			data->next_link = insert;
			insert->next_link = NULL;
			insert->prev_link = data;
		}
	}
}
CONTENT *copy_content(polynomial *data) {
	CONTENT *target = data->content;
	CONTENT *init = (CONTENT *)malloc(sizeof(CONTENT));
	CONTENT *prev = init;
	memcpy(init, target, sizeof(CONTENT));
	init->next_link = NULL;
	target = target->next_link;
	while (target != NULL) {
		CONTENT *copy = (CONTENT *)malloc(sizeof(CONTENT));
		memcpy(copy, target, sizeof(CONTENT));
		copy->next_link = NULL;
		copy->prev_link = prev;
		prev->next_link = copy;
		target = target->next_link;
		prev = copy;
	}
	return init;
}

polynomial addPoly(polynomial X, polynomial Y) {			// ���׽� p1, p2�� ���� ���ϴ� ����
	CONTENT *xCopy = X.content;
	CONTENT *yCopy = Y.content;
	polynomial Z;
	CONTENT *init, *prev, *data;				// init Z�� �ʱ� ����Ʈ
	if (X.max > Y.max) { 
		Z.max = X.max;
		init = (CONTENT*)malloc(sizeof(CONTENT));
		memcpy(init, xCopy, sizeof(CONTENT));
		init->next_link = NULL;
		xCopy = xCopy->next_link;
	}
	else if (X.max == Y.max) {
		Z.max = X.max;
		init = (CONTENT *)malloc(sizeof(CONTENT));
		memcpy(init, xCopy, sizeof(CONTENT));
		init->Coefficient += yCopy->Coefficient;
		init->next_link = NULL;
		xCopy = xCopy->next_link;
		yCopy = yCopy->next_link;
	}
	else { 
		Z.max = Y.max;
		init = (CONTENT*)malloc(sizeof(CONTENT));
		memcpy(init, yCopy, sizeof(CONTENT));
		init->next_link = NULL;
		yCopy = yCopy->next_link;
	}
	prev = init;

	while (xCopy != NULL && yCopy != NULL) {
		if (xCopy->Exponent > yCopy->Exponent) {
			data = (CONTENT *)malloc(sizeof(CONTENT));
			memcpy(data, xCopy, sizeof(CONTENT));
			data->prev_link;
			prev->next_link = data;
			xCopy = xCopy->next_link;
			prev = data;
		}
		else if (yCopy->Exponent == xCopy->Exponent) {
			data = (CONTENT *)malloc(sizeof(CONTENT));
			memcpy(data, xCopy, sizeof(CONTENT));
			data->Coefficient += yCopy->Coefficient;
			data->prev_link;
			prev->next_link = data;
			xCopy = xCopy->next_link;
			yCopy = yCopy->next_link;
			prev = data;
		}
		else {
			data = (CONTENT *)malloc(sizeof(CONTENT));
			memcpy(data, yCopy, sizeof(CONTENT));
			data->prev_link;
			prev->next_link = data;
			yCopy = yCopy->next_link;
			prev = data;
		}
	}
	Z.content = init;
	return Z;
}


void codingPoly(CONTENT *target) {
	CONTENT *move, *data;
	data = target;
	int check = 1;
	while (check) {
		check = 0;
		while (data->next_link != NULL) {
			if (data->Exponent == (data->next_link)->Exponent) {
				move = data->next_link;
				data->Coefficient += move->Coefficient;
				data->next_link = move->next_link;
				free(move);
				check = 1;
			}
			else if (data->Exponent < data->next_link->Exponent) {
				move = data->next_link;
				data->next_link = move->next_link;
				move->prev_link = data->prev_link;
				data->prev_link = move;
				move->next_link = data;
				check = 1;
			}
			else { data = data->next_link; }
		}
	}
}


polynomial multPoly(polynomial X, polynomial Y) {	// ���׽� p1�� p2�� ���� ���ϴ� ����
	CONTENT *xCopy, *yCopy = Y.content;
	polynomial Z;
	CONTENT *init = NULL, *prev = NULL, *data = NULL;				// init Z�� �ʱ� ����Ʈ
	Z.max = X.max + Y.max;
	while (yCopy != NULL && yCopy->Coefficient != 0) {
		xCopy = X.content;
		while (xCopy != NULL && xCopy->Coefficient != 0) {
			data = (CONTENT *)malloc(sizeof(CONTENT));
			data->Coefficient = xCopy->Coefficient * yCopy->Coefficient;
			data->Exponent = xCopy->Exponent + yCopy->Exponent;
			data->next_link = NULL;
			if (prev != NULL) {
				data->prev_link = prev;
				prev->next_link = data;
			}
			else {
				init = data;
				data->prev_link = NULL;
			}
			prev = data;
			xCopy = xCopy->next_link;
		}
		yCopy = yCopy->next_link;
	}
	codingPoly(init);
	Z.content = init;
	return Z;
}

void printPoly(polynomial target) {
	CONTENT *data = target.content;
	
	if (target.max == 0) {
		printf("%d ", data->Coefficient);
	}
	else {
		while (data != NULL) {
			printf("%dx^%d + ", data->Coefficient, data->Exponent);
			data = data->next_link;
		}
		/*
		while (data != NULL) {
			if (data->Coefficient != 0) {
				printf("%dx^%d ", data->Coefficient, data->Exponent);
				data = data->next_link;
				if (data->Coefficient != 0)	printf("+ ");
			}
		}
		if (data->Coefficient != 0)	printf("%d", data->Coefficient);
		*/
	}
	printf("\n");
}