#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s_size 10		// 문자열 배열의 크기
#define buffer_size 30	// 입력버퍼 크기

void pr_str_array(char **dp, int n) {
	for (int i = 1; i <= s_size; i++) {
		printf("%02d : %s\n", i, dp[i - 1]);		// 자리 맞춰서 출력, %2d 빈칸 두개, %02d 빈칸 대신 0
		free(dp[i - 1]);							// 메모리 해제, malloc() 이나 calloc() 에서 할당 받은 메모리를 시스템에 반환합니다. 포인터 값이 NULL이면 작업을 취소합니다.
		dp[i - 1] = NULL;							// string 배열의 포인터 제거
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

	pr_str_array(string, s_size);

	/*
	for (int i = 0; i < s_size; i++) {
		printf("%02d : %s\n", i, string[i]);		// 자리 맞춰서 출력, %2d 빈칸 두개, %02d 빈칸 대신 0
		free(string[i]);						// 메모리 해제
	}
	*/

	return 0;
}