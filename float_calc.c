#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

typedef enum {FALSE, TRUE} BOOL;


char *cStack;
int cSize;
int cTop;

void cInitStack(int aSize) {
	cSize = aSize;
	cStack = (char *)malloc(cSize*sizeof(char));
	cTop = -1;
}
void cFreeStack() {
	free(cStack);
}
BOOL cPush(char data) {
	if (cTop < cSize - 1) {
		cTop++;
		cStack[cTop] = data;
		return TRUE;
	}
	else {
		return FALSE;
	}
}
char cPop() {
	if (cTop >= 0) {
		return cStack[cTop--];
	}
	else {
		return -1;
	}
}

double *dStack;
int dSize;
int dTop;

void dInitStack(int aSize) {
	dSize = aSize;
	dStack = (double *)malloc(dSize * sizeof(double));
	dTop = -1;
}
void dFreeStack() {
	free(dStack);
}
BOOL dPush(double data) {
	if (dTop < dSize - 1) {
		dTop++;
		dStack[dTop] = data;
		return TRUE;
	}
	else {
		return FALSE;
	}
}
double dPop() {
	if (dTop >= 0) {
		return dStack[dTop--];
	}
	else {
		return -1;
	}
}

int GetPriority(int op) {
	switch (op) {
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	}
	return 100;
}
void MakePostfix(char *Post, const char *Mid) {
	const char *m = Mid;
	char *p = Post, c;
	cInitStack(256);
	while (*m) {
		if (isdigit(*m)) {
			while (isdigit(*m) || *m == '.') *p++ = *m++;
			*p++ = ' ';
		}
		else {
			if (strchr("^*/+-", *m)) {
				while (cTop != -1 && GetPriority(cStack[cTop]) >= GetPriority(*m)) {
					*p++ = cPop();
				}
				cPush(*m++);
			}
			else
			{
				if (*m == '(') {
					cPush(*m++);
				}
				else {
					if (*m == ')') {
						for (;;) {
							c = cPop();
							if (c == '(') break;
							*p++ = c;
						}
						m++;
					}
					else {
						m++;
					}
				}
			}
		}
	}

	while (cTop != -1) {
		*p++ = cPop();
	}
	*p = 0;
	cFreeStack();
}

double CalcPostfix(const char *Post) {
	const char *p = Post;
	double num;
	double left, right;

	dInitStack(256);

	while (*p) {
		if (isdigit(*p)) {
			num = atof(p);
			dPush(num);
			for (; isdigit(*p) || *p == '.'; p++) { ; }
		}
		else {
			if (strchr("^*/+-", *p)) {
				right = dPop();
				left = dPop();
				switch (*p) {
				case '+':
					dPush(left + right);
					break;
				case '-':
					dPush(left - right);
					break;
				case '*':
					dPush(left * right);
					break;
				case '/':
					if (right == 0.0) {
						dPush(0.0);
					}
					else {
						dPush(left / right);
					}
					break;
				case '^':
					dPush(pow(left, right));
					break;
				}
			}
			p++;
		}
	}
	if (dTop != -1) {
		num = dPop();
	}
	else {
		num = 0.0;
	}
	
	dFreeStack();
	return num;
}

double calcExp(const char *exp, BOOL *bError) {
	char Post[256];
	const char *p;
	int count;

	if (bError != NULL) {
		for (p = exp, count = 0; *p; p++) {
			if (*p == '(') count++;
			if (*p == ')') count--;
		}
		*bError = (count != 0);
	}
	MakePostfix(Post, exp);
	return CalcPostfix(Post);
}


int main() {
	
	char exp[256];
	BOOL bError;
	double result;

	strcpy(exp, "2.2+3.5*4.1");
	printf("%s = %.2f\n", exp, calcExp(exp, NULL));
	strcpy(exp, "(34+93)*2-(43/2)");
	printf("%s = %.2f\n", exp, calcExp(exp, NULL));
	strcpy(exp, "1+(2+3)/4*5+2^10+(6/7)*8");
	printf("%s = %.2f\n", exp, calcExp(exp, NULL));


	while (1) {
		printf("수식을 입력하세요(종료 :0) :");
		gets_s(exp, strlen(exp));
		if (strcmp(exp, "0") == 0) break;
		result = calcExp(exp, &bError);
		if (bError) {
			puts("수식의 괄호짝이 틀립니다.");
		}
		else {
			printf("%s = %.2f\n", exp, result);
		}
	}
	return 0;
}