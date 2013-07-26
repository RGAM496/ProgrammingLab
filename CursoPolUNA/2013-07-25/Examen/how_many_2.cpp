#include <cstdio>

using namespace std;

typedef unsigned int uint;

template <typename N>
inline void set_min (N &a, const N &b)
{
	if (a < b)
		a = b;
}


inline uint combinacion (uint n, uint r)
{
	uint c = 1;

	set_min (r, n - r);

	for (uint i = 1; i <= r; ++i)
	{
		c *= n--;
		c /= i;
	}

	return c;
}


int main ()
{
	int n, r, k;

	while (scanf ("%u %u %u", &n, &r, &k) == 3)
	{
		n = n - k + 1;
		fprintf(stderr, "(%d)(%d) ", n, r);
		printf("%u\n", combinacion (n, r));
	}

	return 0;
}