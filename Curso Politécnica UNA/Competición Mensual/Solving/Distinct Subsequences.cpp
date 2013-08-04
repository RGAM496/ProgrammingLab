#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

#define MOD 1000000007

typedef unordered_map <char, int> Map;
typedef Map::iterator Iterator;


int combination (int n, int r)
{
	int c = 1;
	r = min (r, n - r);
	for (int i = 1; i <= r; ++i, --n)
	{
		c = (c * n); // % MOD;
		c = (c / i); // % MOD;
	}
	return c;
}


Map charlist;
string str;

int main ()
{
	int test_cases;

	cin >> test_cases;
	while (test_cases--)
	{
		charlist.clear ();
		cin >> str;
		for (char c : str)
			++charlist[c];

	}

	return 0;
}