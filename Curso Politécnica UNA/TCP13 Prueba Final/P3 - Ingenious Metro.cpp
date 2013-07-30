#include <iostream>

using namespace std;

#define MAX_T 100000
#define MAX_Q 10

#define YES 'Y'
#define NO 'N'


int t, t0, mcd;


template <typename N>
N abs (const N &n)
{
	return n < 0 ? -n : n;
}


inline int mod (const int &a, const int &b)
{
	return b ? a % b : a;
}


inline int gcd (int a, int b)
{
	int r;

	if (b == 0)
		return a;
	
	while (r = a % b)
	{
		a = b;
		b = r;
	}

	return b;
}


inline void _gcd_differences (int t)
{
	int tn;
	cin >> t0;
	//cerr << "\t" << t0;
	mcd = 0;
	while (--t)
	{
		cin >> tn;
		//cerr << " " << tn;
		mcd = gcd (mcd, tn - t0);
	}
	//cerr << "\tmcd: " << mcd;
}


inline bool _answer_query (int s, int d, int mcd)
{
	d -= s;
	if (d == 0)
		return true;
	if (d % 2)
		return false;
	if (t == 1)
		return 2 * (t0 - s) == d;
	if (mod (d, mcd) == 0)
		return true;
	mcd = gcd (mcd, t0 - s);
	return mod (d, mcd) == 0;
}


int main ()
{
	int q, s, d;

	while (cin >> t >> q, t || q)
	{
		_gcd_differences (t);
		//cerr << "\tt: " << t << endl;
		while (q--)
		{
			cin >> s >> d;
			cout << (_answer_query (s, d, mcd) ? YES : NO);
			if (q) cout << ' ';
		}
		cout << '\n';
	}

	return 0;
}