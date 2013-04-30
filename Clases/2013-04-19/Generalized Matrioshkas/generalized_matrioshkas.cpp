#include <cstdio>


#define GOOD_DESIGN ":-) Matrioshka!"
#define BAD_DESIGN ":-( Try again."


/**********************************************/


inline int get_int (int &n)
{
	static int c;
	return scanf("%d%c", &n, &c) == 2 ? c : EOF;
}


/**********************************************/

int e;


int matrioshka (int size)
{
	int r;
	int sum; // Sum of directly contained toys.

	sum = 0;

	e = get_int(r);
	while (r != size)
	{
		if (e == '\n' || e == EOF || r > 0)
			return 0;
		else {
			r = -r;
			sum += r;
			if (sum >= size || !matrioshka(r) || e == '\n' || e == EOF)
				return 0;
		}
		e = get_int(r);
	}

	return size;
}


/**********************************************/


int main ()
{
	int n;

	e = get_int(n);
	while (e != EOF)
	{
		if (e == '\n') {
			puts(BAD_DESIGN);
		}
		else if (matrioshka(-n))
		{
			puts(GOOD_DESIGN);
		}
		else
		{
			puts(BAD_DESIGN);
			while (e != '\n' && e != EOF)
				e = getchar();
		}

		e = get_int(n);
	}

	return 0;
}