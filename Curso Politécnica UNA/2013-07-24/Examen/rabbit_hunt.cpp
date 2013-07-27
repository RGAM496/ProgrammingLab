#include <iostream>
#include <map>
#include <set>

using namespace std;

#define MAX_RABBITS 200
#define SPECIAL 10000.0

struct Point
{
	double x, y;
};

bool operator == (const Point &a, const Point &b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator < (const Point &a, const Point &b)
{
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

istream & operator >> (istream &is, Point &p)
{
	return is >> p.x >> p.y;
}

ostream & operator << (ostream &os, const Point &p)
{
	return os << p.x << ' ' << p.y;
}

typedef map <Point, set <Point> > HashTable;


inline void pendiente (const Point &u, const Point &v, Point &m)
{
	m.x	= u.x == v.x
		? SPECIAL
		: (v.y - u.y) / (v.x - u.x);
	m.y = - m.x * u.x + u.y;
}


Point rabbit[MAX_RABBITS];
HashTable conteo;


int main ()
{
	int n, r, c;
	Point m;

	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> rabbit[i];
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			pendiente (rabbit[i], rabbit[j], m);
			//cerr << "\t\t" << rabbit[i] << '\t' << rabbit[j] << '\t' << m << endl;
			conteo[m].insert (rabbit[i]);
			conteo[m].insert (rabbit[j]);
		}
	}

	r = 0;
	for (HashTable::iterator it = conteo.begin(); it != conteo.end(); ++it)
	{
		//cerr << '\t' << it->first << '\t' << it->second << endl;
		c = it->second.size();
		if (r < c)
			r = c;
	}
	cout << r << endl;

	return 0;
}