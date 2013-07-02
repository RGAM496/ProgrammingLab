#include <cstdio>
#include <cmath>

#define MAX_POINTS 100


/**********************************************************/


inline int get_int (int &n)
{
  return scanf ("%d", &n);
}

inline int get_int (int &a, int &b)
{
	return scanf ("%d %d", &a, &b);
}


template <typename N>
inline void set_min (N &a, const N &b)
{
	if (a > b)
		a = b;
}

template <typename N>
inline void set_max (N &a, const N &b)
{
	if (a < b)
		a = b;
}


inline double floor (double n, double p)
{
	return floor (n * p) / p;
}

inline double ceil (double n, double p)
{
	return ceil (n * p) / p;
}


/**********************************************************/


struct Point
{
	double x, y;

	inline void set (int x, int y) {
		this->x = (double)x;
		this->y = (double)y;
	}
};


struct Line
{

private:

	double dd;

public:

	double a, b, c;

	inline void set (const Point &A, const Point &B) {
		a = A.y - B.y;
		b = B.x - A.x;
		c = - a * B.x - b * B.y;
		dd = sqrt (a * a + b * b);
	}

	inline double distance (const Point &P)
	{
		return (a * P.x + b * P.y + c) / dd;
	}
};


struct Polygon
{
	Point p[MAX_POINTS];
	int n;
};


/**********************************************************/


inline double width (const Polygon &p)
{
	int i, j, k;
	double r, r_max, r_min, d;
	Line line;

	r = 20000.0; // Jamás hallarás este ancho.
	for (i = 0; i < p.n; ++i)
	{
		const Point &pi = p.p[i];
		for (j = i + 1; j < p.n; ++j)
		{
			r_max = r_min = 0;
			const Point &pj = p.p[j];
			line.set (pi, pj);
			for (k = 0; k < p.n; ++k)
			{
				if (k == i || k == j)
					continue;

				const Point &pk = p.p[k];
				d = line.distance (pk);
				set_max (r_max, d);
				set_min (r_min, d);
				#ifdef DEBUG_R_AUX
				fprintf(stdout, "\t\t\td:\t%g\tr_aux: %g", d, r_aux);
				fprintf(stdout, "\t\t(%g,%g) (%g, %g) (%g, %g)\n", pi.x, pi.y, pj.x, pj.y, pk.x, pk.y);
				#endif
			}
			set_min (r, r_max - r_min);
			#ifdef DEBUG
			fprintf(stdout, "\tr: %g\n", r);
			#endif
		}
	}

	return r;
}


/**********************************************************/


Polygon polygon;


int main ()
{
	int test_case, x, y, i;
	double w;

	test_case = 0;

	while (get_int (polygon.n), polygon.n)
	{
		++test_case;

		for (i = 0; i < polygon.n; ++i)
		{
			get_int (x, y);
			polygon.p[i].set (x, y);
		}

		w = width (polygon);
		printf("Case %d: %.2f\n", test_case, ceil (w, 100));
	}

	return 0;
}