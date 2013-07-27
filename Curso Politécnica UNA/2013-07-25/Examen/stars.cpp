#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 15000

struct Star
{
	int x, y;
};


bool operator < (const Star &s, const Star &t)
{
	return s.x <= t.x && s.y <= t.y;
}

istream & operator >> (istream &s, Star &st)
{
	return s >> st.x >> st.y;
}

ostream & operator << (ostream &s, Star &st)
{
	return s << st.x << ' ' << st.y;
}


Star star[MAX_N];
int level[MAX_N];


int main ()
{
	int n, l;

	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		cin >> star[i];
	}

	sort (star, star + n);

	for (int i = 0; i < n; ++i)
	{
		l = 0;
		for (int j = 0; j < i; ++j)
		{
			l += (star[j] < star[i]);
		}
		cerr << "\t" << star[i] << "\t" << l << endl;
		++level[l];
	}

	for (int i = 0; i < n; ++i)
	{
		cout << level[i] << endl;
	}

	return 0;
}