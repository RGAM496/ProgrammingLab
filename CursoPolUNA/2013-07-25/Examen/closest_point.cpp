#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define MAX_N 50000


struct Point
{
	double x, y;
};


istream & operator >> (istream &s, Point &p)
{
	s >> p.x >> p.y;
}


double distancia (const Point &a, const Point &b)
{
	double x, y;
	x = a.x - b.x;
	y = a.y - b.y;
	x *= x;
	y *= y;
	return sqrt (x + y);
}


Point p[MAX_N];


int main ()
{
	int n, min_i, min_j;
	double min_d, d;

	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		cin >> p[i];
	}

	min_d = 20000000;
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			d = distancia (p[i], p[j]);
			if (min_d > d)
			{
				min_d = d;
				min_i = i;
				min_j = j;
			}
		}
	}

	cout << min_i << ' ' << min_j << ' ';
	printf("%.6lf\n", min_d);

	return 0;
}