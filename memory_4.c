#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// strlen()함수 사용을 위한 라이브러리 호출

#define MAX_LENGTH 50

char *get_word() {
	char *flash;
	char buffer[MAX_LENGTH];
	printf("단어를 입력하시오 : ");
	gets_s(buffer, sizeof(buffer));

	int str_size = sizeof(char)*strlen(buffer);

	flash = (char *)malloc(str_size + 1);		// 마지막에 NULL문자로 문자열 끝 알려주기, 안하면 free()에서 에러발생

	strcpy(flash, buffer);

	return flash;
};

int main() {

	char *check;
	check = get_word();

	printf("동적 메모리에 저장된 단어는 %s입니다.\n", check);

	free(check);

	return 0;
}
