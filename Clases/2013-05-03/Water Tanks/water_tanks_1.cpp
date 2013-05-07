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


struct Valve
{
	int count;
	int from_tank;
	int to_tank;

	inline bool operator < (const Valve &v) const {
		bool ans =
			(this->count > v.count) ||
			(this->from_tank < v.from_tank);
		return ans;
	}

	inline bool operator == (const Valve &v) const {
		bool ans = 
			(this->count == v.count) &&
			(this->from_tank == v.from_tank);
		return ans;
	}

	inline Valve & operator = (const Valve &v) {
		this->count = v.count;
		this->from_tank = v.from_tank;
		this->to_tank = v.to_tank;
	}
};


/**********************************************/


struct System
{
	int tank[MAX_TANKS];
	int total_tanks, h_average;

	Valve valves_moved[MAX_TANKS];
	int tanks_sum[MAX_TANKS];

	int min_valves ();
};


int System::min_valves ()
{
	const int MAX_MOVEMENTS = total_tanks - 1;
	int not_equilibrated_tanks, average, movements, t, i;

	not_equilibrated_tanks = total_tanks;
	loop (i, total_tanks)
	{
		valves_moved[i].count = MAX_MOVEMENTS;
		tanks_sum[i] = tank[i];
	}

	for (average = h_average, movements = 0;
		movements < MAX_MOVEMENTS;
		average += h_average)
	{
		loop (t, total_tanks)
		{
			if (movements < valves_moved[t].count && tanks_sum[t] == average)
			{
				int last_tank = (t + movements) % total_tanks;
				for (int i = 0, iv = t; i <= movements; ++i, iv = (iv + 1) % total_tanks)
				{
					Valve &vm = valves_moved[iv];
					not_equilibrated_tanks -= (vm.count == MAX_MOVEMENTS);
					vm.count = movements;
					vm.from_tank = t;
					vm.to_tank = last_tank;
				}
			}
		}

		if (not_equilibrated_tanks)
		{
			++movements;
			for (int ts = 0, ta = (ts +movements) % total_tanks;
				ts < total_tanks;
				++ts, ta = (ta + 1) % total_tanks)
			{
				tanks_sum[ts] += tank[ta];
			}
		}
		else
			break;
	}

	if (movements == MAX_MOVEMENTS)
		return MAX_MOVEMENTS;

	t = 0;
	movements = 0;
	Valve *val;
	int limit = valves_moved[0].from_tank;
	if (!limit) limit = total_tanks;
	while (t < limit)
	{
		val = valves_moved + t;
		movements += val->count;
		t = val->to_tank + 1;
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
			sys.tank[i] = height * sys.total_tanks;
			sys.h_average += height;
		}
		getchar();
		printf("%d\n", sys.min_valves());
	}

	return 0;
}
