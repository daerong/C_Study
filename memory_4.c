#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// strlen()�Լ� ����� ���� ���̺귯�� ȣ��

#define MAX_LENGTH 50

char *get_word() {
	char *flash;
	char buffer[MAX_LENGTH];
	printf("�ܾ �Է��Ͻÿ� : ");
	gets_s(buffer, sizeof(buffer));

	int str_size = sizeof(char)*strlen(buffer);

	flash = (char *)malloc(str_size + 1);		// �������� NULL���ڷ� ���ڿ� �� �˷��ֱ�, ���ϸ� free()���� �����߻�

	strcpy(flash, buffer);

	return flash;
};

int main() {

	char *check;
	check = get_word();

	printf("���� �޸𸮿� ����� �ܾ�� %s�Դϴ�.\n", check);

	free(check);

	return 0;
}
