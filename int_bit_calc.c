#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
char *cStack;
int cSize;
int cTop;
typedef enum {FALSE, TRUE} BOOL;
void cInitStack(int aSize)
{
	cSize = aSize;
	cStack = (char *)malloc(cSize*sizeof(char));
	cTop = -1;
}
void cFreeStack()
{
	free(cStack);
}
BOOL cPush(char data)
{
	if(cTop < cSize - 1) {
		cTop++;
		cStack[cTop] = data;
		return TRUE;
	}
	else {
		return FALSE;
	}
}
char cPop()
{
	if(cTop >= 0) {
		return cStack[cTop--];
	}
	else {
		return -1;
	}
}
int *dStack;
int dSize;
int dTop;
void dInitStack(int aSize)
{
	dSize = aSize;
	dStack = (int *)malloc(dSize*sizeof(int));
	dTop = -1;
}

void dFreeStack()
{
	free(dStack);
}
BOOL dPush(int data)
{
	if(dTop < dSize - 1) {
		dTop++;
		dStack[dTop] = data;
		return TRUE;
	}
	else {
		return FALSE;
	}
}
int dPop()
{
	if(dTop >= 0) {
		return dStack[dTop--];
	}
	else {
		return -1;
	}
}
int GetPriority(int op)
{
	switch(op) {
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
	case ' > ':
	case '<':
		return 4;
	}
	return 100;
}
void MakePostfix(char *Post, const char *Mid)
{
	const char *m = Mid;
	char *p = Post, c;
	cInitStack(256);
	while(*m) {
		// 숫자 - 그대로 출력하고 뒤에 공백 하나를 출력한다.
		if(isdigit(*m)) {
			while(isdigit(*m) || *m == '.') *p++ = *m++;
			*p++ = ' ';
		}
		else
		{
			// 연산자 - 스택에 있는 자기보다 높은 연산자를 모두 꺼내 출력하고 자신은

			if(strchr("*/+-^&|><", *m)) {
				while(cTop != -1 && GetPriority(cStack[cTop]) >= GetPriority(*m)) {
					*p++ = cPop();
				}
				cPush(*m++);
			}
			else // 여는 괄호 - 푸시한다.
			{
				if(*m == '(') {
					cPush(*m++);
				}
				else // 닫는 괄호 - 여는 괄호가 나올 때까지 팝해서 출력하고 여는 괄호는

				{
					if(*m == ')') {
						for(;;) {
							c = cPop();
							if(c == '(') break;
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
	// 스택에 남은 연산자들 모두 꺼낸다.
	while(cTop != -1) {
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
	dInitStack(256);
	while(*p) {
		// 숫자는 스택에 넣는다.
		if(isdigit(*p)) {
			num = atof(p);
			dPush(num);
			for(; isdigit(*p) || *p == '.'; p++) { ; }
		}
		else {
			// 연산자는 스택에서 두 수를 꺼내 연산하고 다시 푸시한다.
			if(strchr("*/+-^&|><", *p)) {
				right = dPop();
				left = dPop();
				switch(*p) {
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
					if(right == 0) {
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
			// 연산 후 또는 연산자가 아닌 경우 다음 문자로
			p++;
		}
	}
	if(dTop != -1) {
		num = dPop();
	}
	else {
		num = 0;
	}
	dFreeStack();
	return num;
}

int CalcExp(const char *exp, BOOL *bError)
{
	char Post[256];
	const char *p;
	int count;
	if(bError != NULL) {
		for(p = exp, count = 0; *p; p++) {
			if(*p == '(') count++;
			if(*p == ')') count--;
		}
		*bError = (count != 0);
	}
	MakePostfix(Post, exp);
	return CalcPostfix(Post);
}

void main()
{
	char exp[256];
	BOOL bError;
	int result;
	strcpy(exp, "2.2+3.5*4.1");
	printf("%s = %d\n", exp, CalcExp(exp, NULL));
	strcpy(exp, "(34+93)*2-(43/2)");
	printf("%s = %d\n", exp, CalcExp(exp, NULL));
	strcpy(exp, "1+(2+3)/4*5+2^10+(6/7)*8");
	printf("%s = %d\n", exp, CalcExp(exp, NULL));
	while(1) {
		printf("수식을 입력하세요(종료 : 0) : ");
		gets(exp);
		if(strcmp(exp, "0") == 0) break;
		result = CalcExp(exp, &bError);
		if(bError) {
			puts("수식의 괄호짝이 틀립니다.");
		}
		else {
			printf("%s = %d\n", exp, result);
		}
	}
}
//[출 처 : 행복한 프로그래밍]