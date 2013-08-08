#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

#define MOD 1000000007
#define FIRST ('A' - 1)
#define LAST 'Z'
#define LETTERS (LAST - FIRST + 1)

typedef stack <int> Stack;


struct Sub
{
	int count, previous;
};


ostream & operator << (ostream &os, const Sub &sub)
{
	return os << sub.count << ' ' << sub.previous;
}


int distinct_subsequences( Stack &st )
{
	Sub sub[LETTERS] = {{1, 0}}, old;
	int c_old, c;
	c = 0;
	while( !st.empty() )
	{
		c_old = c;
		c = st.top(); st.pop();
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


Stack st;

int main ()
{
	int test_cases;
	char c;

	cin >> test_cases;
	cin.ignore();
	while (test_cases--)
	{
		while( ( cin.get( c ), isupper( c ) ) && !cin.eof() )
		{
			st.push( c - FIRST );
		}
		cout << distinct_subsequences( st ) << endl;
	}

	return 0;
}