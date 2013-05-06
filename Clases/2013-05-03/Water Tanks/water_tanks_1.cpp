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

	int valves_moved[MAX_TANKS];
	int tanks_sum[MAX_TANKS];

	int min_valves ();
};


int System::min_valves ()
{
	const int MAX_MOVEMENTS = total_tanks - 1;
	int not_equilibrated_tanks, average, movements;

	not_equilibrated_tanks = total_tanks;
	loop (i, total_tanks)
	{
		valves_moved[i] = MAX_MOVEMENTS;
		tanks_sum[i] = tank[i];
	}

	for (average = h_average, movements = 0;
		movements < MAX_MOVEMENTS;
		average += h_average)
	{
		loop (t, total_tanks)
		{
			if (tanks_sum[t] == average)
			{
				for (int i = 0, iv = t; i <= movements; ++i, iv = (iv + 1) % total_tanks)
				{
					int &vm = valves_moved[iv];
					not_equilibrated_tanks -= (vm == MAX_MOVEMENTS);
					if (movements < vm)
						vm = movements;
				}
			}
		}

		if (not_equilibrated_tanks)
		{
			++movements;
			for (int ts = 0, t = (ts +movements) % total_tanks;
				ts < total_tanks;
				++ts, t = (t + 1) % total_tanks)
			{
				tanks_sum[ts] += tank[t];
			}
		}
		else
			break;
	}

	return movements;
}


/**********************************************/


char title[MAX_STRING];
System sys;


int main ()
{
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