#include <iostream>

using namespace std;

#define MAX_N 44
#define MAX_K 1000000000


struct Range
{
	int ini, fin;
};


Range range[MAX_N] = {
	{1, 1},
	{2, 2}
	// Fill with init ().
};


ostream & operator << (ostream &os, const Range &r)
{
	return os << r.ini << ' ' << r.fin;
}


inline void init ()
{
	Range *r, *last;
	last = range + MAX_N;
	for (r = range + 2; r < last; ++r)
	{
		r->ini = r[-1].fin + 1;
		r->fin = r[-1].fin + r[-2].fin;
	}
}


int main ()
{
	int n, k;

	init ();

	cin >> n >> k;

	if (k > range[n].fin)
	{
		cout << -1;
	}
	else
	{
		while (n)
		{
			if (range[n].ini > k)
			{
				cout << 0;
			}
			else
			{
				cout << 1;
				k -= range[n-1].fin;
			}
			--n;
		}
	}

	cout << endl;

	return 0;
}