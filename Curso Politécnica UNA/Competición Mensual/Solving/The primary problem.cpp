#include <cstdio>
#include <set>
using namespace std;

#define MAX_N 1000000
typedef set <int> Set;
typedef Set::iterator Iterator;


bool is_prime[MAX_N] = {false, false, true, true};
const int
	first_primes[] = {2, 3},
	FP = sizeof (first_primes) / sizeof (int);
Set prime_list (first_primes, first_primes + FP);


inline void init ()
{
	int p;
	Iterator it, it_last;
	bool prime_not_found;
	it_last = prime_list.end ();
	--it_last;
	do
	{
		p = *it_last + 2;
		prime_not_found = true;
		while (prime_not_found)
		{
			prime_not_found = false;
			for (it = prime_list.begin (); it != prime_list.end (); ++it)
			{
				if (p % *it == 0)
				{
					prime_not_found = true;
					p += 2;
					break;
				}
			}
		}
		prime_list.insert (it_last, p);
		++it_last;
		//fprintf(stderr, "\t\t%d\n", p);
	}
	while (p <= MAX_N);
}


int main ()
{
	int n, p1, p2;
	Iterator it;
	init ();
	while (scanf("%d", &n), n)
	{
		printf("%d:\n", n);
		//fprintf(stderr,"%d:\n", n);
		int n2 = n / 2;
		it = prime_list.begin ();
		p1 = *it;
		for (; p1 <= n2; ++it, p1 = *it)
		{
			p2 = n - p1;
			//fprintf(stderr, "\tp1: %d\tp2: %d\n", p1, p2);
			if (prime_list.find (p2) != prime_list.end ())
			{
				printf("%d+%d\n", p1, p2);
				break;
			}
		}
		if (p1 > n2)
			puts("NO WAY!");
	}
}