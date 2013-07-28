#include <iostream>
#include <set>

using namespace std;

#define MAX_B 91


template <typename N>
N abs (const N &n)
{
	return n < 0 ? - n : n;
}


int ball[MAX_B];


int main ()
{
	int n, b, d;
	set <int> diffs;

	while (cin >> n >> b, n || b)
	{
		diffs.clear ();

		for (int i = 0; i < b; ++i)
		{
			cin >> ball[i];
		}

		diffs.insert (0);
		for (int i = 0; i < b; ++i)
		{
			for (int j = i + 1; j < b; ++j)
			{
				d = abs (ball[i] - ball[j]);
				diffs.insert (d);
			}
		}

		if (diffs.size() == n + 1)
			cout << 'Y' << endl;
		else
			cout << 'N' << endl;
	}

	return 0;
}