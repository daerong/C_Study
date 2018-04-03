#include <stdio.h>

typedef struct NUMBER {
	int content;
	int type;					// 2·Î ³ª´« ³ª¸ÓÁö
} NUMBER;

int main() {
	
	NUMBER k[7];

	int odd_max = 0, even_max = 0;	// È¦, Â¦

	for (int i = 0; i < 7; i++) {
		scanf("%d", &(k[i].content));
	}

	for (int i = 0; i < 7; i++) {
		if (k[i].content % 2) {
			k[i].type = 1;
		}
		else {
			k[i].type = 0;
		}
	}

	for (int i = 0; i < 7; i++) {
		if (k[i].type) {
			if (odd_max < k[i].content) {
				odd_max = k[i].content;
			}
		}
		else {
			if (even_max < k[i].content) {
				even_max = k[i].content;
			}
		}
	}

	printf("%d", odd_max + even_max);
	

	return 0;
}