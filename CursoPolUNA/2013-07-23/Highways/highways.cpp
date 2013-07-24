#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_C 750
#define MAX_DISTANCE 1000000000

int connected_cities, towns, highways;


struct City
{
	int x, y;
	bool m;

	inline void mark () {
		m = true;
		++connected_cities;
	}
};

struct Highway
{
	int d;
	bool m;
};

City city[MAX_C];
Highway hw[MAX_C][MAX_C];

inline void reset ()
{
	connected_cities = 0;
	for (int i = 0; i < towns; ++i)
	{
		city[i].m = false;
		for (int j = i + 1; j < towns; ++j)
		{
			hw[i][j].m = hw[j][i].m = false;
		}
	}
}

inline int hw_distance (int i, int j)
{
	int x, y;
	x = city[i].x - city[j].x;
	y = city[i].y - city[j].y;
	x *= x;
	y *= y;
	return x + y;
}

inline void calculate_distances ()
{
	for (int i = 0; i < towns; ++i)
	{
		for (int j = i + 1; j < towns; ++j)
		{
			hw[i][j].d = hw[j][i].d = hw_distance (i, j);
		}
	}
}


inline void add_highway (int i, int j)
{
	hw[i][j].m = hw[j][i].m = true;
}

inline void mark_connected_cities (int c)
{
	city[c].mark ();
	for (int i = 0; i < towns; ++i)
	{
		if (hw[c][i].m && city[i].m == false)
			mark_connected_cities (i);
	}
}

inline void mark_highway (int i, int j)
{
	add_highway (i, j);
	mark_connected_cities (j);
}


inline void choose_highway (int &mi, int &mj)
{
	int md = MAX_DISTANCE;
	for (int i = 0; i < towns; ++i)
	{
		if (!city[i].m)
			continue;
		for (int j = 0; j < towns; ++j)
		{
			if (city[j].m || hw[i][j].m)
				continue;
			if (hw[i][j].d < md)
			{
				md = hw[i][j].d;
				mi = i;
				mj = j;
			}
		}
	}
}


int main ()
{
	int test_cases, x, y;

	cin >> test_cases;

	while (test_cases--)
	{
		cin >> towns;
		reset ();
		for (int i = 0; i < towns; ++i)
		{
			cin >> city[i].x >> city[i].y;
		}
		cin >> highways;
		for (int i = 0; i < highways; ++i)
		{
			cin >> x >> y;
			add_highway (x - 1, y - 1);
		}
		calculate_distances ();

		mark_connected_cities (0);
		if (connected_cities == towns)
			cout << "No new highways need\n";

		do
		{
			/*cerr << "\n\nConnected cities: " << connected_cities << endl;
			for (int i = 0; i < towns; ++i)
			{
				cerr << '\t' << city[i].x << ' ' << city[i].y << " (" << city[i].m << ")\t";
				for (int j = 0; j < towns; ++j)
				{
					cerr << "\t" << hw[i][j].d << " (" << hw[i][j].m << ")";
				}
				cerr << '\n';
			}*/

			choose_highway (x, y);
			mark_highway (x, y);
			cout << (x + 1) << ' ' << (y + 1) << '\n';
		}
		while (connected_cities < towns);
	}

	return 0;
}