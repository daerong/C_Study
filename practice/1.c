#include <stdio.h>
#include <Windows.h>    // system() �Լ��� ����ϱ� ���� ���̺귯��
#include <conio.h>		// _getch()
#include <string.h>		// strtok �Լ��� ����� ��� ����

#define NUMBER 30
#define NAME_SIZE 10

typedef struct CHECK {
	char *A;
	char *B;
	int check;
} CHECK;

int main()
{
	int insert_num;

	CHECK list[NUMBER];

	do {
		scanf("%d", &insert_num);
	} while (insert_num <= 1 || insert_num > 30);

	while (getchar() != '\n');

	char s1[NAME_SIZE*NUMBER];				// ���ڿ� ���� ����
	char s2[NAME_SIZE*NUMBER];

	fgets(s1, sizeof(s1), stdin);
	s1[strlen(s1) - 1] = '\0';

	char *sArr_1[NUMBER] = { NULL, };			// ũ�Ⱑ 10�� ���ڿ� ������ �迭�� �����ϰ� NULL�� �ʱ�ȭ
	int i = 0;								// ���ڿ� ������ �迭�� �ε����� ����� ����

	char *ptr = strtok(s1, " ");			// ���� ���ڿ��� �������� ���ڿ��� �ڸ�

	while (ptr != NULL)						// �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		sArr_1[i] = ptr;						// ���ڿ��� �ڸ� �� �޸� �ּҸ� ���ڿ� ������ �迭�� ����
		i++;								// �ε��� ����

		ptr = strtok(NULL, " ");   // ���� ���ڿ��� �߶� �����͸� ��ȯ
	}

	fgets(s2, sizeof(s2), stdin);
	s2[strlen(s2) - 1] = '\0';

	char *sArr_2[NUMBER] = { NULL, };			// ũ�Ⱑ 10�� ���ڿ� ������ �迭�� �����ϰ� NULL�� �ʱ�ȭ
	i = 0;									// ���ڿ� ������ �迭�� �ε����� ����� ����

	ptr = strtok(s2, " ");					// ���� ���ڿ��� �������� ���ڿ��� �ڸ�

	while (ptr != NULL)						// �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		sArr_2[i] = ptr;						// ���ڿ��� �ڸ� �� �޸� �ּҸ� ���ڿ� ������ �迭�� ����
		i++;								// �ε��� ����

		ptr = strtok(NULL, " ");			// ���� ���ڿ��� �߶� �����͸� ��ȯ
	}


	for (int j = 0; j < insert_num; j++) {
		if (sArr_1[j] == NULL || sArr_2[j] == NULL) {
			break;
		}
		list[j].A = sArr_1[j];		// A ���ڿ�
		list[j].B = sArr_2[j];		// B ���ڿ�
	}

	for (int j = 0; j < insert_num; j++) {
		for (int k = 0; k < insert_num; k++) {
			if (*(list[j].B) == *(list[k].A)) {
				if (*(list[k].B) == *(list[j].A)) {
					list[j].check = 1;
				}
			}
		}
	}

	int result = 1;

	for (int j = 0; j < insert_num; j++) {
		if (list[j].check != 1) {
			result = 0;
		}
	}

	if (result == 1) {
		printf("good\n");
	}
	else if (result == 0) {
		printf("bad\n");
	}


	return 0;
}
