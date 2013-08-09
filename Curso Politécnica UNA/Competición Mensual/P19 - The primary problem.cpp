#include <cstdio>
#include <cmath>

#define MAX_N 1000000


int PL = 2,
	prime_list[MAX_N] = {2, 3};
bool is_prime[MAX_N+6] = {false, false, true, true};


inline void init ()
{
	int p, i;
	const int SQN = (int) sqrt ((double)MAX_N);
	
	for (p = 1; p <= MAX_N; p += 6)
	{
		is_prime[p] = true;
		is_prime[p + 4] = true;
	}

	for (p = 5; p <= MAX_N; ++p)
	{
		while (is_prime[p] == false)
		{
			++p;
			if (p > MAX_N)
				return;
		}
		prime_list[PL++] = p;
		if (p <= SQN)
		{
			for (i = p * p; i <= MAX_N; i += p)
			{
				is_prime[i] = false;
			}
		}
	}
}


int main ()
{
	int n, p1, p2;
	init ();
	while (scanf("%d", &n), n)
	{
		printf("%d:\n", n);
		int n2 = n / 2;
		p1 = prime_list[0];
		for (int i = 0; p1 <= n2; ++i, p1 = prime_list[i])
		{
			p2 = n - p1;
			if (is_prime[p2])
			{
				printf("%d+%d\n", p1, p2);
				break;
			}
		}
		if (p1 > n2)
			puts("NO WAY!");
	}
}