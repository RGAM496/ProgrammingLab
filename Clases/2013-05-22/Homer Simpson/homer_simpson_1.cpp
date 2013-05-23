#include <cstdio>

//#define DEBUG

#ifdef DEBUG
#define debug(expr, ...) fprintf(stderr, expr, __VA_ARGS__);
#else
#define debug(expr, ...) {}
#endif


#define MAX 10000

typedef unsigned int uint;


template <typename N>
inline void sort (N &a, N &b)
{
	N c;
	if (a > b)
	{
		c = a;
		a = b;
		b = c;
	}
}


template <typename N>
inline N gcd (N a, N b)
{
	N r = a % b;
	while (r) {
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}


template <typename N>
inline N extended_gcd (N a, N b, N &s, N &t)
{
	N	q, r,
		x[2] = {1,0},
		y[2] = {0,1};

	while (r = a % b)
	{
		q = a / b;
		s = x[0] - q * x[1];
		t = y[0] - q * y[1];
		x[0] = x[1]; x[1] = s;
		y[0] = y[1]; y[1] = t;
		a = b;
		b = r;
	}

	return b;
}


template <typename N>
inline N mod_inverse (N num, N mod)
{
	N	q, r, s, m,
		x[2] = {1,0};

	m = mod;
	while (r = num % mod)
	{
		q = num / mod;
		s = x[0] - q * x[1];
		x[0] = x[1]; x[1] = s;
		num = mod;
		mod = r;
	}

	while (s < 0)
		s += m;

	return s;
}


int main ()
{
	int
		m, n, t,
		min_r, r, mcd, taux, tm, tn;
	while (scanf("%d %d %d", &m, &n, &t) == 3)
	{
		sort(m,n);
		mcd = gcd(m,n);
		min_r = t % mcd;
		t -= min_r;
		m /= mcd; n /= mcd; t /= mcd;
		debug("\tm: %d n: %d t: %d\n", m, n, t)
		tn = (t * mod_inverse(n,m)) % m;
		tm = (t - n * tn) / m;
		if (tm < 0) {
			tm = t / m;
			tn = 0;
		}
		debug("\ttn: %d tm: %d\n", tn, tm)
		r = min_r + (t - m * tm - n * tn);
		debug("\tmin_r: %d r: %d\n", min_r, r)
		if (r)
			printf("%d %d\n", tm + tn, r);
		else
			printf("%d\n", tm + tn);
	}
	return 0;
}