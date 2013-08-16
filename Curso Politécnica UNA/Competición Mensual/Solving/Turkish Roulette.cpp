#include <iostream>

using namespace std;

#define MAX_S 250
#define MAX_B 125
#define MAX_ARRAY (2 * MAX_S)
#define UNKNOWN (-2000000)
#define IMPOSSIBLE (UNKNOWN + 1)


struct Roulette
{
	int S, B, s[MAX_ARRAY], b[MAX_B], m[MAX_B][MAX_ARRAY][MAX_ARRAY];

	inline void reset () {
		for (int i = 0; i < S; ++i) {
			s[i] = s[S+i] = 0;
			for (int j = 0; j < B; ++j) {
				for (int k = 0; k < S; ++k) {
					m[j][i][k] = m[j][S+i][k] = UNKNOWN;
					m[j][i][k+S] = m[j][S+i][k+S] = UNKNOWN;
				}
			}
		}
	}


	int maximum_profit (int ball, int position, int limit )
	{
		int &r = m[ball][position][limit],
			balls_left, l, p;


		if (r == UNKNOWN)
		{
			balls_left = B - 1 - ball;
			l = limit - balls_left;
			if (position < l)
			{
				if (balls_left)
				{
					p = maximum_profit( ball + 1, position + 2, limit );
					if (p != IMPOSSIBLE)
						p += b[ball] * s[position];
					p = max(
						p,
						maximum_profit( ball, position + 1, limit )
						);
				}
				else
				{
					p = max(
						b[ball] * s[position],
						maximum_profit( ball, position + 1, limit )
						);
				}
				r = max( r, p );
			}
			else
			{
				r = IMPOSSIBLE;
			}
		}
		return r;
	}


	inline int maximum_profit ()
	{
		int mp = UNKNOWN, p, limit;

		for (int i = 0; i < S; ++i)
		{
			limit = i + S - 1;
			p = maximum_profit( 1, i + 2, limit );
			if (p != IMPOSSIBLE)
				p += b[0] * s[i];
			mp = max( mp, p );
		}
		return mp;
	}
};


Roulette r;


int main ()
{
	int &S = r.S, &B = r.B, c;

	while (cin >> S >> B, S || B)
	{
		r.reset();
		cin >> c;
		r.s[0] = r.s[S] = c;
		r.s[S-1] = r.s[S+S-1] = c;
		for (int i = 1; i < S; ++i)
		{
			cin >> c;
			r.s[i-1] = r.s[S+i-1] +=c;
			r.s[i] = r.s[S+i] +=c;
		}
		for (int i = 0; i < B; ++i)
		{
			cin >> c;
			r.b[i] = -c;
		}
		cout << r.maximum_profit() << endl;
	}

	return 0;
}