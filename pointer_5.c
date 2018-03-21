#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s_size 3		// 문자열 배열의 크기
#define buffer_size 30	// 입력버퍼 크기

void sort_strings(char *s[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (strcmp(s[i], s[j]) > 0) {		// 문자열 비교함수
				char *sub = s[i];
				s[i] = s[j];
				s[j] = sub;
			}
		}
		printf("%02d : %s\n", i + 1, s[i]);
	}
}

int main() {

	char * string[s_size];				// s_size 크기의 포인터
	char buffer[buffer_size];			// 입력버퍼

	int s_length;						// 문자열 길이
	int arr_count = 0;					// 배열 갯수

	for (int i = 0; i < s_size; i++) {
		printf("%d번째 문자열을 입력하세요 : ", i + 1);
		scanf("%s", buffer);			// buffer에 문자열 할당
		s_length = strlen(buffer);		// \n 직전까지의 문자의 갯수를 반환
		if (s_length > 0) {
			char * str_pointer = (char *)malloc(sizeof(char)* (s_length + 1));
			strcpy(str_pointer, buffer);
			string[arr_count] = str_pointer;
			arr_count++;
		}
		else {
			break;
		}
	}

	sort_strings(string, s_size);

	for (int i = 0; i < s_size; i++) {				// main 내에서 확인
		printf("%02d : %s\n", i + 1, string[i]);
	}

	return 0;
}