#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s_size 10		// ���ڿ� �迭�� ũ��
#define buffer_size 30	// �Է¹��� ũ��

void pr_str_array(char **dp, int n) {
	for (int i = 1; i <= s_size; i++) {
		printf("%02d : %s\n", i, dp[i - 1]);		// �ڸ� ���缭 ���, %2d ��ĭ �ΰ�, %02d ��ĭ ��� 0
		free(dp[i - 1]);							// �޸� ����, malloc() �̳� calloc() ���� �Ҵ� ���� �޸𸮸� �ý��ۿ� ��ȯ�մϴ�. ������ ���� NULL�̸� �۾��� ����մϴ�.
		dp[i - 1] = NULL;							// string �迭�� ������ ����
	}
}

int main() {

	char * string[s_size];				// s_size ũ���� ������
	char buffer[buffer_size];			// �Է¹���

	int s_length;						// ���ڿ� ����
	int arr_count = 0;					// �迭 ����

	for (int i = 0; i < s_size; i++) {
		printf("%d��° ���ڿ��� �Է��ϼ��� : ", i + 1);
		scanf("%s", buffer);			// buffer�� ���ڿ� �Ҵ�
		s_length = strlen(buffer);		// \n ���������� ������ ������ ��ȯ
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
		printf("%02d : %s\n", i, string[i]);		// �ڸ� ���缭 ���, %2d ��ĭ �ΰ�, %02d ��ĭ ��� 0
		free(string[i]);						// �޸� ����
	}
	*/

	return 0;
}