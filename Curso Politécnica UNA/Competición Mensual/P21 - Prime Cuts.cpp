#include <cstdio>

#define MAX_N 1001


int total_primes_until[MAX_N] = {0,1,2,3};
int prime_list[MAX_N] = {1,2,3};


int prime (size_t pos)
{
	bool prime_not_found;

	int &p = prime_list[pos];
	if (p)
		return p;

	p = prime(pos-1) + 2;
	prime_not_found = true;
	while (prime_not_found)
	{
		prime_not_found = false;
		for (int *pp = prime_list + 1; pp < &p; ++pp)
		{
			if (p % *pp == 0)
			{
				prime_not_found = true;
				p += 2;
				break;
			}
		}
	}

	const int &tp = total_primes_until[prime_list[pos-1]];
	const int limit = p < MAX_N ? p : MAX_N;
	for (int i = prime_list[pos - 1] + 1; i < limit; ++i)
		total_primes_until[i] = tp;
	if (p < MAX_N)
		total_primes_until[p] = tp + 1;

	return p;
}


int main ()
{
	int n, c, t, ini, fin;

	prime (1000);
	/*for (int i = 0; i < MAX_N; ++i)
		fprintf(stderr, "%4d: %d\n", i, prime(i));*/

	while (scanf ("%d %d", &n, &c) == 2)
	{
		printf ("%d %d:", n, c);

		t = total_primes_until[n];
		ini = (t + 1) / 2 - c;
		if (ini < 0)
			ini = 0;
		fin = t - ini;

		for (int i = ini; i < fin; ++i)
			printf(" %d", prime_list[i]);
		putchar ('\n');
		putchar ('\n');
	}

	return 0;
}