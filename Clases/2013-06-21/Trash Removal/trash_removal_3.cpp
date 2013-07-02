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
};


struct Line
{

private:

	double dd;

public:

	double a, b, c;

	inline void set (const Point &A, const Point &B) {
		dd = sqrt (a * a + b * b);
	}

	inline double distance (const Point &P)
	{
		return (a * P.x + b * P.y + c) / dd;
	}
};


/**********************************************************/


int main ()
{
	return 0;
}