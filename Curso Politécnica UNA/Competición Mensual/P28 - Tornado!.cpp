#include <iostream>

using namespace std;

#define N 5000

bool post[2*N];


inline int wooden_posts (int n)
{
	int r, c, i = 0;
	r = 0;
	while (post[i] == false && i < n)
		++i;
	if (i >= n)
		return (n - 1) / 2 + 1;
	while (i < n)
	{
		++i;
		c = 0;
		while (post[i] == false)
		{
			++i;
			++c;
		}
		r += c / 2;
	}
	return r;
}


int main ()
{
	int n;
	bool p;

	while (cin >> n, n)
	{
		for (int i = 0; i < n; ++i)
		{
			cin >> p;
			post[i] = post[i + n] = p;
		}

		cout << wooden_posts (n) << endl;
	}

	return 0;
}