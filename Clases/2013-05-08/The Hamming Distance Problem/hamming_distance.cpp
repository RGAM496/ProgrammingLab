#include <cstdio>


#define MAX_N 16
#define MAX_H 16


inline void hamming_strings ();
void hs (int ini, int fin, int nivel);
inline void display ();


int number[MAX_H], N, H;


int main ()
{
	int datasets;

	scanf ("%d\n\n", &datasets);

	while (datasets)
	{
		scanf ("%d %d\n\n", &N, &H);
		hamming_strings ();
		putchar ('\n');

		--datasets;
	}

	return 0;
}


void hamming_strings ()
{
	number[0] = N;
	H = N - H;
	hs (0, N-H+1, H-1);
}


void hs (int ini, int fin, int nivel)
{
	int i;

	if (nivel)
	{
		for (i = ini; i < fin; ++i)
		{
			number[nivel] = i;
			hs (ini + 1, fin + 1, nivel - 1);
		}
	}
	else
	{
		for (i = ini; i < fin; ++i)
		{
			number[0] = i;
			display ();
		}
	}
}


void display ()
{
	int i, j, h;

	i = H;
	j = 0;
	while (i--)
	{
		h = number[i];
		for (; j < h; ++j)
			putchar ('1');
		putchar ('0');
		++j;
	}
	for (; j < N; ++j)
		putchar ('1');
	putchar ('\n');
}