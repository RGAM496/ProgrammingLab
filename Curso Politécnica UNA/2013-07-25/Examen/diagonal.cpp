#include <cstdio>
#include <cmath>

using namespace std;


typedef unsigned long long int uint;


inline int get_uint (uint &n)
{
	return scanf ("%llu", &n);
}


inline uint min_sides (uint diagonals)
{
	double d = (double)diagonals;
	d = (3 + sqrt (9 + 8 * d)) / 2;
	return (uint)ceil(d);
}


int main ()
{
	int test_case = 0;
	uint n;

	while (get_uint (n), n != 0)
	{
		++test_case;
		printf("Case %d: %llu\n", test_case, min_sides (n));
	}

	return 0;
}