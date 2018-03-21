#include <stdio.h>

void set_proverb(char **q, int n) {
	static char * array[10] = {
		"Think like a man of action and act like man of thought.",
		"Courage is very important.Like a muscle, it is strengthened by use.",
		"Life is the art of drawing sufficient conclusions from insufficient premises.",
		"By doubting we come at the truth.",
		"A man that hath no virtue in himself, ever envieth virtue in others.",
		"When money speaks, the truth keeps silent.",
		"Better the last smile than the first laughter.",
		"In the morning of life, work; in the midday, give counsel; in the evening, pray.",
		"Painless poverty is better than embittered wealth.",
		"A poet is the painter of the soul."
	};
	printf("%s\n", array[n - 1]);
	printf("%d\n", &array[n - 1]);
	*q = &array[n - 1];					// (char *) * == char * []
};

int main() {

	char *s;								// char�� ����Ű�� � ������
	int choice;

	printf("1~10������ �Ӵ��� �����ϼ��� : ");
	scanf("%d", &choice);

	set_proverb(&s, choice);				// � �������� �ּҸ� �ѱ�
	
	printf("%d", s);

	return 0;
}