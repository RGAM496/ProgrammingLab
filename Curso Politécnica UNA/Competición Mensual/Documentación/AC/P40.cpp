#include <iostream>
#include <cctype>

using namespace std;

#define MOD 1000000007
#define FIRST ('A' - 1)
#define LAST 'Z'
#define LETTERS (LAST - FIRST + 1)


struct Sub
{
	int count, previous;
};


inline int distinct_subsequences()
{
	Sub sub[LETTERS] = {{1, 0}}, old;
	int c_old, c;
	char ch;
	c = 0;
	while( ( cin.get( ch ), isupper( ch ) ) && !cin.eof() )
	{
		c_old = c;
		c = ch - FIRST;
		old = sub[c_old];
		//sub[c].count = 2 * old.count;
		sub[c].count = ( 2 * old.count ) % MOD;
		if( sub[c].count )
		{
			//sub[c].count -= sub[c].previous;
			sub[c].count += MOD - sub[c].previous;
			sub[c].count %= MOD;
		}
		sub[c].previous = old.count;
	}
	return sub[c].count;
}

int main ()
{
	int test_cases;
	char c;

	cin >> test_cases;
	cin.ignore();
	while (test_cases--)
	{
		cout << distinct_subsequences() << endl;
	}

	return 0;
}