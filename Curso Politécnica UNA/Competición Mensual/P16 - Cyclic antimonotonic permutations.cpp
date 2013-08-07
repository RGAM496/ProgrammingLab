#include <iostream>
#include <algorithm>

using namespace std;

#define N 1000001

int list[N] = {3, 1};


inline void reset ()
{
	list[2] = 2;
}


int main ()
{
	int n, i;

	while (cin >> n, n)
	{
		reset ();

		for (i = 4; i <= n; ++i)
		{
			int &p0 = list[i-3];
			int &p1 = list[i-2];
			int &p2 = list[i-1];
			p2 = i;
			if (p0 > p1)
				swap (p0, p2);
			else
				swap (p1, p2);
		}

		cout << list[0] << ' ' << list[1];
		for (i = 2; i < n; ++i)
			cout << ' ' << list[i];
		cout << '\n';
	}

	return 0;
}