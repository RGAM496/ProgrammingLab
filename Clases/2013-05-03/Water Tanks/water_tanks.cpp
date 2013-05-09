#include <cstdio>
#include <cctype>
#include <algorithm>

using std::stable_sort;

#define MAX_TANKS 200
#define MAX_HEIGHT 99
#define MAX_STRING 201
#define END '#'

#define loop(i,limit) for (i = 0; i < limit; ++i)


inline int get_int (int &n)
{
	return scanf("%d", &n);
}


/**********************************************/


void print_short_title (const char *s)
{
	bool last_was_space;

	last_was_space = true;
	for (; *s; ++s)
	{
		if (last_was_space) {
			putchar(toupper(*s));
			last_was_space = false;
		}
		else if (isspace(*s)) {
			last_was_space = true;
		}
	}
	putchar(':');
	putchar(' ');
}


/**********************************************/


struct System
{
	int tank[2*MAX_TANKS];
	int total_tanks, h_average;

	int min_valves ();
};


/**********************************************/


int System::min_valves ()
{
	const int MAX_MOVEMENTS = total_tanks - 1;
	int movements, i, j, k, jlimit, mov, average_sum, hsum;

	movements = MAX_MOVEMENTS;

	for (i = 0, jlimit = MAX_MOVEMENTS; i < MAX_MOVEMENTS; ++i, ++jlimit)
	{
		mov = MAX_MOVEMENTS;
		for (j = i; j < jlimit;)
		{
			hsum = 0;
			average_sum = h_average;
			for (k = j; k < jlimit; ++k)
			{
				hsum += tank[k];
				if (hsum == average_sum) {
					--mov;
					++k;
					break;
				}
				average_sum += h_average;
			}
			j = k;
		}

		if (mov < movements)
			movements = mov;
	}

	return movements;
}


/**********************************************/


char title[MAX_STRING];
System sys;


int main ()
{
	int height, i;

	while (fgets (title, MAX_STRING, stdin), *title != END)
	{
		print_short_title (title);
		sys.h_average = 0;
		get_int (sys.total_tanks);
		loop (i, sys.total_tanks) {
			get_int (height);
			/* No altera la naturaleza del problema,
			 * y evita posibles divisiones inexactas.
			 */
			sys.tank[i + sys.total_tanks] = sys.tank[i] = height * sys.total_tanks;
			sys.h_average += height;
		}
		getchar();
		printf("%d\n", sys.min_valves());
	}

	return 0;
}