#include <cstdio>


#define GOOD_DESIGN ":-) Matrioshka!"
#define BAD_DESIGN ":-( Try again."


/**********************************************/


inline int get_int (int &n)
{
	return scanf("%d", &n);
}


/**********************************************/


int matrioshka (int size)
{
	int r;
	int sum; // Sum of directly contained toys.

	sum = 0;

	get_int(r);
	while (r != size)
	{
		if (r > 0)
			return 0;
		else {
			r = -r;
			sum += r;
			if (sum >= size || !matrioshka(r))
				return 0;
		}
		get_int(r);
	}

	return size;
}


/**********************************************/


int main ()
{
	int n;

	while (get_int (n) > 0)
	{
		if (matrioshka(-n))
		{
			puts(GOOD_DESIGN);
		}
		else
		{
			puts(BAD_DESIGN);
			do {
				n = getchar();
			} while (n != '\n' && n != EOF);
		}
	}

	return 0;
}