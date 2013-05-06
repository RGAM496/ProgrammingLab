#include <cstdio>
#include <cctype>

#define MAX_TANKS 200
#define MAX_HEIGHT 99
#define MAX_STRING 201
#define END '#'

#define loop(i,limit) for (int i = 0; i < limit; ++i)


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
	int tank[MAX_TANKS];
	int total_tanks, h_average;

	int min_valves ();
};


int System::min_valves ()
{
	return 0;
}


/**********************************************/


int main ()
{
	char title[MAX_STRING];
	System sys;
	int height;


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
			sys.tank[i] = height * sys.total_tanks;
			sys.h_average += height;
		}
		getchar();
		printf("%d\n", sys.min_valves());
	}

	return 0;
}