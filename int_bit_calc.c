#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define STACK_SIZE 256

typedef enum { FALSE, TRUE } BOOL;

char *cStack;
int cSize;		// max size, �迭�� ũ��
int cTop;		// �ʱⰪ -1

void cInitStack(int aSize);		// aSize ��ŭ�� ũ�� ������ ����
void cFreeStack();				// ���� ����
BOOL cPush(char data);			// if(cTop < cSize - 1) �������� push
char cPop();					// if (cTop >= 0) �������� Pop

int *dStack;
int dSize;		// max size, �迭�� ũ��
int dTop;		// �ʱⰪ -1

void dInitStack(int aSize);		// aSize ��ŭ�� ũ�� ������ ����
void dFreeStack();				// ���� ����
BOOL dPush(int data);			// if(dTop < dSize - 1) �������� push
int dPop();						// if (dTop >= 0) �������� Pop

int GetPriority(int op);						
void MakePostfix(char *Post, const char *Mid);
int CalcPostfix(const char *Post);
int CalcExp(const char *exp, BOOL *bError);		// ������ ��ȣ ������ ���� �Լ�

void main(int argc, char** argv)
{
	char exp[STACK_SIZE];
	BOOL bError;
	int result;
	strcpy(exp, "9&(5+(((2+3)*2)>1))");
	printf("%s = %d\n", exp, CalcExp(exp, NULL));
	strcpy(exp, "9|(5+(((2+3)*2)>1))");
	printf("%s = %d\n", exp, CalcExp(exp, NULL));

	while (1) {
		printf("������ �Է��ϼ���(���� : 0) : ");
		gets_s(exp, strlen(exp));
		if (strcmp(exp, "0") == 0) break;
		result = CalcExp(exp, &bError);
		if (bError) {
			puts("������ ��ȣ¦�� Ʋ���ϴ�.");
		}
		else {
			printf("%s = %d\n", exp, result);
		}
	}
}

void cInitStack(int aSize){
	cSize = aSize;
	cStack = (char *)malloc(cSize * sizeof(char));
	cTop = -1;
}
void cFreeStack(){
	free(cStack);
}
BOOL cPush(char data){
	if (cTop < cSize - 1) {
		cTop++;
		cStack[cTop] = data;
		return TRUE;
	}
	else {
		return FALSE;
	}
}
char cPop(){
	if (cTop >= 0) {
		return cStack[cTop--];
	}
	else {
		return -1;
	}
}

void dInitStack(int aSize){
	dSize = aSize;
	dStack = (int *)malloc(dSize * sizeof(int));
	dTop = -1;
}
void dFreeStack(){
	free(dStack);
}
BOOL dPush(int data){
	if (dTop < dSize - 1) {
		dTop++;
		dStack[dTop] = data;
		return TRUE;
	}
	else {
		return FALSE;
	}
}
int dPop(){
	if (dTop >= 0) {
		return dStack[dTop--];
	}
	else {
		return -1;
	}
}

int GetPriority(int op){
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
	case '&':
	case '|':
		return 3;
	case '>':
	case '<':
		return 4;
	}
	return 100;
}
void MakePostfix(char *Post, const char *Mid)
// Post�� ����, Mid�� ���� ���ڿ�
{
	const char *m = Mid;
	char *p = Post, c;
	cInitStack(STACK_SIZE);
	while (*m) {
		// ���� - �״�� ����ϰ� �ڿ� ���� �ϳ��� ����Ѵ�.
		if (isdigit(*m)) {		// int isdigit(int c) : c�� ������ ���ڸ� �Ǵ���. char�� �Էµ� ���ڸ� �Ǻ�
			while (isdigit(*m)) {
				*p++ = *m++;	// ���ÿ� ���ڸ� �ø�
			}
			*p++ = ' ';			// ���� �ڿ� ������ �߰�
		}
		else
		{
			// ������ - ���ÿ� �ִ� �ڱ⺸�� ���� �����ڸ� ��� ���� ����ϰ� �ڽ���

			if (strchr("*/+-^&|><", *m)) {		// ������ ���ڿ����� *m�� ��ġ�ϴ� ���� ã�� ������ char *, ������ NULL����  
				while (cTop != -1 && GetPriority(cStack[cTop]) >= GetPriority(*m)) {	// &&���� >= �켱���� �ռ�
					*p++ = cPop();
				}
				cPush(*m++);
			}
			else // ���� ��ȣ - Ǫ���Ѵ�.
			{
				if (*m == '(') {
					cPush(*m++);
				}
				else // �ݴ� ��ȣ - ���� ��ȣ�� ���� ������ ���ؼ� ����ϰ� ���� ��ȣ��

				{
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
	// ���ÿ� ���� �����ڵ� ��� ������.
	while (cTop != -1) {
		*p++ = cPop();
	}
	*p = 0;
	cFreeStack();
}
int CalcPostfix(const char *Post)
{
	const char *p = Post;
	int num;
	int left, right;
	dInitStack(STACK_SIZE);
	while (*p) {
		// ���ڴ� ���ÿ� �ִ´�.
		if (isdigit(*p)) {
			num = atoi(p);
			dPush(num);
			for (; isdigit(*p) || *p == '.'; p++) { ; }
		}
		else {
			// �����ڴ� ���ÿ��� �� ���� ���� �����ϰ� �ٽ� Ǫ���Ѵ�.
			if (strchr("*/+-^&|><", *p)) {
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
					dPush(left*right);
					break;
				case '/':
					if (right == 0) {
						dPush(0);
					}
					else {
						dPush(left / right);
					}
					break;
				case '^':
					dPush(left ^ right);
					break;
				case '&':
					dPush(left & right);
					break;
				case '|':
					dPush(left | right);
					break;
				case '>':
					dPush(left >> right);
					break;
				case '<':
					dPush(left << right);
					break;
				}
			}
			// ���� �� �Ǵ� �����ڰ� �ƴ� ��� ���� ���ڷ�
			p++;
		}
	}
	if (dTop != -1) {
		num = dPop();
	}
	else {
		num = 0;
	}
	dFreeStack();
	return num;
}
int CalcExp(const char *exp, BOOL *bError){
	// exp�� ����
	char Post[STACK_SIZE];
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