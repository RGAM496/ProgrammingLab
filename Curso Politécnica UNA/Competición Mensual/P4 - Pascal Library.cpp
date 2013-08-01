#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 100
#define MAX_D 500

int alumni[MAX_N];


inline bool someone_participated_always (int N)
{
	for (int n = 0; n < N; ++n)
	{
		if (alumni[n])
			return true;
	}
	return false;
}


int main ()
{
	int N, D, n, d, v;

	while (cin >> N >> D, N || D)
	{
		fill (alumni, alumni + N, 1);
		for (d = 0; d < D; ++d)
		{
			for (n = 0; n < N; ++n)
			{
				cin >> v;
				alumni[n] &= v;
			}
		}
		cout << (someone_participated_always (N) ? "yes\n" : "no\n");
	}

	return 0;
}