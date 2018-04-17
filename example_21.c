#include <stdio.h>
#include <malloc.h>
#include <string.h>

// 두 다항식을 입력 받아 다항식의 곱을 구하는 multPoly 함수를 작성하시오.

typedef struct CONTENT {
	int Coefficient;		// 값
	int Exponent;			// 지수
	struct CONTENT *prev_link;
	struct CONTENT *next_link;
} CONTENT;

typedef struct polynomial {
	CONTENT *content;		// 값
	int max;				// 지수
} polynomial;

polynomial zeroP(void);			// 0을 만드는 연산
int isZeroP(polynomial);		// 0이면 true 반환
int coef(polynomial, int);		// 지수가 e인 항의 계수 a를 구하는 연산
int maxExp(polynomial);			// 최대 지수를 구하는 연산
int addTerm(polynomial *, int a, int e);		// 다항식 p에 지수가 e인 항이 없는 경우에 새로운 항 <e, a>를 추가하는 연산
int delTerm(polynomial *, int e);			// 지수가 e인 항 <e, a>를 삭제하는 연산
void multTerm(polynomial *, int a, int e);		// 다항식의 모든 항에 ax^e항을 곱하는 연산
polynomial addPoly(polynomial, polynomial);		// 다항식 p1, p2의 합을 구하는 연산


polynomial multPoly(polynomial, polynomial);		// 다항식 p1과 p2의 곱을 구하는 연산


// 테스트를 위해 사용
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
	// 값이 0인지 체크하는 문장
	printf("X is 0??? : %d\n", isZeroP(X));
	printf("Y is 0??? : %d\n", isZeroP(Y));
	// 지수가 e인 항의 계수 a를 구하는 연산
	addTerm(&X, 3, 4);
	addTerm(&X, 5, 2);
	printPoly(X);
	addTerm(&Y, 2, 2);
	addTerm(&Y, 7, 0);
	printPoly(Y);
	Z = multPoly(X, Y);
	printPoly(Z);
	printf("X의 %d승 계수는 %d입니다.\n", 0, coef(X, 0));
	printf("Y의 %d승 계수는 %d입니다.\n", 0, coef(Y, 0));
	printf("X의 최대 지수는 %d입니다.\n", maxExp(X));
	printf("Y의 최대 지수는 %d입니다.\n", maxExp(Y));
	addTerm(&X, 3, 4);
	addTerm(&X, 4, 3);
	addTerm(&X, 5, 2);
	addTerm(&X, 6, 1);
	printf("X의 %d승 계수는 %d입니다.\n", 2, coef(X, 2));			// 결과 5
	printf("X의 최대 지수는 %d입니다.\n", maxExp(X));				// 결과 4														
	printPoly(X);												// 3 * x ^ 4 + 4 * x ^ 3 + 5 * x ^ 2 + 6 * x ^ 1
	multTerm(&X, 6, 3);
	printPoly(X);												// 18 * x ^ 7 + 24 * x ^ 6 + 30 * x ^ 5 + 36 * x ^ 4	
	printf("X is 0??? : %d\n", isZeroP(X));						// 결과 0
	delTerm(&X, 2);
	printf("X의 %d승 계수는 %d입니다.\n", 2, coef(X, 2));			// 결과 0
	printf("X의 최대 지수는 %d입니다.\n", maxExp(X));				// 결과 0
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
int isZeroP(polynomial target) {		// 0이면 true 반환
	CONTENT *data = target.content;
	if (data->Coefficient == 0 && data->Exponent == 0) return 1;
	else return 0;
}
int coef(polynomial target, int e) {								//  지수가 e인 항의 계수 a를 구하는 연산
	CONTENT *data = target.content;
	while (data != NULL) {
		if (data->Exponent == e) {
			return data->Coefficient;
		}
		data = data->next_link;
	}
	return 0;			// 0을 제외하고 계수가 0인 조건은 없으므로 0을 리턴하여 처리 
}
int maxExp(polynomial target) {						// 최대 지수를 구하는 연산
	return target.max;
}
int addTerm(polynomial *target, int a, int e) {			// 다항식 p에 지수가 e인 항이 없는 경우에 새로운 항 <e, a>를 추가하는 연산
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
			if (data->Exponent > e) {			// e보다 큰 구간 순차검색
				data = data->next_link;
			}
			else {								// e보다 작거나 같아지는 순간
				if (data->Exponent != e) {		// 같으면 대입 불가능
					CONTENT *insert = (CONTENT *)malloc(sizeof(CONTENT));
					insert->Coefficient = a;
					insert->Exponent = e;
					insert->next_link = data;
					insert->prev_link = data->prev_link;
					(data->prev_link)->next_link = insert;
					data->prev_link = insert;
					return 0;
				}
				else {							// 달라도 행할 조건이 하나 발생 <0, 0> = 0이면 대입할 수 있어야함
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
int delTerm(polynomial *target, int e) {		// 지수가 e인 항 <e, a>를 삭제하는 연산
	CONTENT *data = (*target).content;
	while (data != NULL) {
		if (data->Exponent == e) {							// e보다 큰 구간 순차검색
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
void multTerm(polynomial *target, int a, int e) {	// 다항식의 모든 항에 ax^e항을 곱하는 연산
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

polynomial addPoly(polynomial X, polynomial Y) {			// 다항식 p1, p2의 합을 구하는 연산
	CONTENT *xCopy = X.content;
	CONTENT *yCopy = Y.content;
	polynomial Z;
	CONTENT *init, *prev, *data;				// init Z의 초기 리스트
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


polynomial multPoly(polynomial X, polynomial Y) {	// 다항식 p1과 p2의 곱을 구하는 연산
	CONTENT *xCopy, *yCopy = Y.content;
	polynomial Z;
	CONTENT *init = NULL, *prev = NULL, *data = NULL;				// init Z의 초기 리스트
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