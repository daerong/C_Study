#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define OPEN 'C'         
#define CLOSE 'O'   
#define DISTANCE 20     

int main()
{
	int i, j = 0;

	while (j < DISTANCE) {           

		system("cls");

		for (i = 0; i < j; i++) {
			printf(" ");
		}

		if (j % 2) {
			printf("%c", CLOSE);	
		}else {
			printf("%c", OPEN);
		}

		j++;

		for (i = 0; i < DISTANCE - j - 1; i++) {
			printf(",");
		}

		char key;
		while (1) {
			key = _getch();
			if (key == 77) {
				break;
			}
			else if (j == 1) {
				j -= 1;
				break;
			}
			else if (key == 75) {
				j -= 2;
				break;
			}
		}
	}

	return 0;
}
