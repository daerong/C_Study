#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define STACK_SIZE 256

typedef enum { FALSE, TRUE } BOOL;

char *cStack;
int cSize;		// max size, 배열의 크기
int cTop;		// 초기값 -1

void cInitStack(int aSize);		// aSize 만큼의 크기 스택을 생성
void cFreeStack();				// 스택 해제
BOOL cPush(char data);			// if(cTop < cSize - 1) 조건으로 push
char cPop();					// if (cTop >= 0) 조건으로 Pop

int *dStack;
int dSize;		// max size, 배열의 크기
int dTop;		// 초기값 -1

void dInitStack(int aSize);		// aSize 만큼의 크기 스택을 생성
void dFreeStack();				// 스택 해제
BOOL dPush(int data);			// if(dTop < dSize - 1) 조건으로 push
int dPop();						// if (dTop >= 0) 조건으로 Pop

int GetPriority(int op);						
void MakePostfix(char *Post, const char *Mid);
int CalcPostfix(const char *Post);
int CalcExp(const char *exp, BOOL *bError);		// 수식의 괄호 갯수를 세는 함수

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
		printf("수식을 입력하세요(종료 : 0) : ");
		gets_s(exp, strlen(exp));
		if (strcmp(exp, "0") == 0) break;
		result = CalcExp(exp, &bError);
		if (bError) {
			puts("수식의 괄호짝이 틀립니다.");
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
// Post는 스택, Mid는 수식 문자열
{
	const char *m = Mid;
	char *p = Post, c;
	cInitStack(STACK_SIZE);
	while (*m) {
		// 숫자 - 그대로 출력하고 뒤에 공백 하나를 출력한다.
		if (isdigit(*m)) {		// int isdigit(int c) : c가 문자인 숫자를 판단함. char에 입력된 숫자를 판별
			while (isdigit(*m)) {
				*p++ = *m++;	// 스택에 숫자를 올림
			}
			*p++ = ' ';			// 숫자 뒤에 공백을 추가
		}
		else
		{
			// 연산자 - 스택에 있는 자기보다 높은 연산자를 모두 꺼내 출력하고 자신은

			if (strchr("*/+-^&|><", *m)) {		// 좌측의 문자열에서 *m과 일치하는 것을 찾고 있으면 char *, 없으면 NULL리턴  
				while (cTop != -1 && GetPriority(cStack[cTop]) >= GetPriority(*m)) {	// &&보다 >= 우선순위 앞섬
					*p++ = cPop();
				}
				cPush(*m++);
			}
			else // 여는 괄호 - 푸시한다.
			{
				if (*m == '(') {
					cPush(*m++);
				}
				else // 닫는 괄호 - 여는 괄호가 나올 때까지 팝해서 출력하고 여는 괄호는

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
	// 스택에 남은 연산자들 모두 꺼낸다.
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
		// 숫자는 스택에 넣는다.
		if (isdigit(*p)) {
			num = atoi(p);
			dPush(num);
			for (; isdigit(*p) || *p == '.'; p++) { ; }
		}
		else {
			// 연산자는 스택에서 두 수를 꺼내 연산하고 다시 푸시한다.
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
			// 연산 후 또는 연산자가 아닌 경우 다음 문자로
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
	// exp는 수식
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