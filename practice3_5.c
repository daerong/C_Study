#include <stdio.h>

typedef struct {
	int row;
	int col;
	int value;
} term;

void smTranspose(term a[], term b[])
{
	int m, n, v, i, j, p;

	m = a[0].row;
	n = a[0].col;
	v = a[0].value;

	b[0].row = n;
	b[0].col = m;
	b[0].value = v;

	if (v>0) {
		p = 1;
		for (i = 0; i<n; i++)
			for (j = 1; j <= v; j++)
				if (a[j].col == i) {
					b[p].row = a[j].col;
					b[p].col = a[j].row;
					b[p].value = a[j].value;
					p++;
				}
	}
}

void main()
{
	term a[8] = {
		{ 5,5,7 },
		{ 0,0,7 },
		{ 0,4,-2 },
		{ 1,3,-5 },
		{ 2,1,3 },
		{ 3,0,-6 },
		{ 4,2,37 },
		{ 4,4,9 }
	};

	term b[11];
	int i, j;

	for (i = 0; i<8; i++)
		smTranspose(a, b);

	for (i = 0; i<8; i++)
		printf("%d,%d,%3d\n", b[i].row, b[i].col, b[i].value);

}