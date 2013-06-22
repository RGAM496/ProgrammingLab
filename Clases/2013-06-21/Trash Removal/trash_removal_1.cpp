#include <cstdio>
#include <cmath>

#define MAX_POINTS 100

const double PI = 3.14159265;
const int ITERATIONS = 8354;
const double MIN_ANGLE = PI / (double)ITERATIONS;


double SIN[ITERATIONS], COS[ITERATIONS];


inline int get_int (int &n)
{
  return scanf ("%d", &n);
}

inline int get_int (int &a, int &b)
{
	return scanf ("%d %d", &a, &b);
}


void init ()
{
	int i;
	double angle;

	for (i = 0, angle = 0.0; i < ITERATIONS; ++i, angle += MIN_ANGLE)
	{
		SIN[i] = sin (angle);
		COS[i] = cos (angle);
	}
}


struct Point
{
	double x, y;

	void set (int x, int y) {
		this->x = (double)x;
		this->y = (double)y;
	}

	inline void operator -= (const Point &p) {
		x -= p.x;
		y -= p.y;
	}
};

void rotate (const Point &s, int i, Point &d)
{
	d.x = s.x * COS[i] - s.y * SIN[i];
	d.y = s.x * SIN[i] + s.y * COS[i];
}


Point point[MAX_POINTS], rotated_point[MAX_POINTS];


inline double weight (int n)
{
	double min, max, x;

	min = max = rotated_point[0].x;

	for (int i = 1; i < n; ++i)
	{
		x = rotated_point[i].x;
		if (min > x)
			min = x;
		if (max < x)
			max = x;
	}

	return max - min;
}


inline double min_weight (int n)
{
	double w, w_aux;
	int i, it;

	for (i = 0; i < n; ++i)
		rotated_point[i] = point[i];
	w = weight (n);
	for (it = 1; it < ITERATIONS; ++it)
	{
		for (i = 0; i < n; ++i)
			rotate (point[i], it, rotated_point[i]);
		w_aux = weight (n);
		if (w > w_aux)
			w = w_aux;
	}

	return w;
}


int main ()
{
	int test_case, n, x, y, i;
	Point m;

	init ();

	test_case = 0;
	while (get_int (n), n)
	{
		++test_case;
		m.set (0, 0);
		for (i = 0; i < n; ++i)
		{
			get_int (x, y);
			point[i].set (x, y);
			m.x += (double)x;
			m.y += (double)y;
		}
		m.x /= n;
		m.y /= n;
		for (i = 0; i < n; ++i)
		{
			point[i] -= m;
		}

		printf("Case %d: %.2f\n", test_case, min_weight (n));
	}

	return 0;
}
