/*
 * (x - a_x)² + (y - a_y)² = (x - b_x)² + (y - b_y)² = (x - c_x)² + (y - c_y)² = r²
 *
 * For linear pre circle equation
 * ------------------------------
 * 2(a_x - b_x) x + 2(a_y - b_y) y = (a_x - b_x)(a_x + b_x) + (a_y - b_y)(a_y + b_y)
 * 2(a_x - c_x) x + 2(a_y - c_y) y = (a_x - c_x)(a_x + c_x) + (a_y - c_y)(a_y + c_y)
 *
 * For linear equation
 * -------------------
 * a_1 x + b_1 y = c_1
 * a_2 x + b_2 y = c_2
 * x = (c_1 b_2 - c_2 b_1) / (a_1 b_2 - a_2 b_1)
 * y = (c_1 a_2 - c_2 a_1) / - (a_1 b_2 - a_2 b_1)
 *
 */

#include <iostream>
#include <cmath>
#include <map>
#include <bitset>

using namespace std;

#define MAX_N 100

typedef double eqarray[3];


struct Point
{
	double x, y;
};

istream & operator >> (istream &s, Point &p)
{
	return s >> p.x >> p.y;
}

ostream & operator << (ostream &s, const Point &p)
{
	return s << '(' << p.x << ", " << p.y << ')';
}

inline bool operator < (const Point &A, const Point &B)
{
	return A.x < B.x || (A.x == B.x && A.y < B.y);
}


inline void linear_pre_circle_equation (const Point &p1, const Point &p2, eqarray e)
{
	e[0] = p1.x - p2.x;
	e[1] = p1.y - p2.y;
	e[2] = e[0] * (p1.x + p2.x) + e[1] * (p1.y + p2.y);
	e[0] *= 2;
	e[1] *= 2;
}

inline bool linear_equation (eqarray e1, eqarray e2, Point &p)
{
	double denom = e1[0] * e2[1] - e2[0] * e1[1];
	if (denom == 0.0) return false;
	p.x = e1[2] * e2[1] - e2[2] * e1[1];
	p.y = e1[2] * e2[0] - e2[2] * e1[0];
	p.x /= denom;
	p.y /= -denom;
	return true;
}


inline double distancia (const Point &p1, const Point &p2)
{
	double dx, dy;
	dx = p1.x - p2.x; dx *= dx;
	dy = p1.y - p2.y; dy *= dy;
	return sqrt (dx + dy);
}


struct Circle
{
	Point c;
	double r;

	inline void set_invalid () {r = -1.0;}

	inline bool invalid () {return r < 0.0;}

	inline void from_points (const Point &p0, const Point &p1, const Point &p2)
	{
		eqarray a, b;
		linear_pre_circle_equation (p0, p1, a);
		linear_pre_circle_equation (p0, p2, b);
		if (linear_equation (a, b, c))
			r = distancia (p0, c);
		else
			set_invalid ();
	}
};

inline bool operator < (const Circle &C, const Circle &D)
{
	return C.r < D.r || (C.r == D.r && C.c < D.c);
}

ostream & operator << (ostream &s, const Circle &C)
{
	s << C.r << ' ' << C.c;
}

typedef bitset <MAX_N> Set;
typedef map <Circle, Set> Map;
typedef Map::iterator Iterator;

Point P[MAX_N];
Map cocircular;

int main ()
{
	int points, max_cocircular, c;
	Circle C;

	while (cin >> points, points)
	{
		for (int i = 0; i < points; ++i)
			cin >> P[i];

		cocircular.clear ();
		for (int i = 0; i < points; ++i)
		{
			for (int j = i + 1; j < points; ++j)
			{
				for (int k = j + 1; k < points; ++k)
				{
					C.from_points (P[i], P[j], P[k]);
					if (C.invalid ())
						continue;
					//cerr << "\t" << C << "\t\t\t\t\t" << P[i] << "\t" << P[j] << "\t" << P[k] << "\t" << endl;
					cocircular[C].set (i);
					cocircular[C].set (j);
					cocircular[C].set (k);
				}
			}
		}
		//cerr << endl;

		max_cocircular = 2;
		for (Iterator it = cocircular.begin (); it != cocircular.end (); ++it)
		{
			//cerr << "\t" << it->second.size() << "\t" << it->first << endl;
			c = it->second.count ();
			if (max_cocircular < c)
				max_cocircular = c;
		}
		cout << max_cocircular << endl;
		//cerr << max_cocircular << endl;
	}

	return 0;
}