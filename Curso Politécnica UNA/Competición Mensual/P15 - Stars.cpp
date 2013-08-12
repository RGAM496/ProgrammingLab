#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 15000


struct Star
{
	int index, x, y;
};

istream & operator >> ( istream &is, Star &s )
{
	return is >> s.x >> s.y;
}

ostream & operator << ( ostream &os, Star &s )
{
	return os << s.x << ' ' << s.y;
}


inline bool less_x( const Star &s, const Star &t )
{
	return s.x < t.x || ( s.x == t.x && s.y < t.y );
}

inline bool less_y( const Star &s, const Star &t )
{
	return s.y < t.y || ( s.y == t.y && s.x < t.x );
}

inline bool operator < ( const Star &s, const Star &t )
{
	return less_y( s, t );
}


struct Map
{
	int level[MAX_N];

	inline int & operator [] ( const Star &s ) {
		return level[s.index];
	}

	inline int & operator [] ( const int i ) {
		return level[i];
	}
};


Map map;
Star star[MAX_N];
int level[MAX_N];


void calculate ( Star *vb, Star *ve )
{
	int B;
	const int n = ve - vb;
	Star *b1, *e1, *b2, *e2, v_aux[n];


	if( n > 1 )
	{
		for( b1 = vb, e2 = v_aux; b1 != ve; ++b1, ++e2 )
		{
			*e2 = *b1;
		}
		b1 = v_aux;
		e1 = b2 = v_aux + ( n / 2 );
		calculate( b1, e1 );
		calculate( b2, e2 );
		B = 0;
		while( b1 != e1 && b2 != e2 )
		{
			if( *b2 < *b1 )
			{
				map[*b2] += B;
				*vb++ = *b2++;
			}
			else
			{
				++B;
				*vb++ = *b1++;
			}
		}
		while( b1 != e1 )
		{
			*vb++ = *b1++;
		}
		while( b2 != e2 )
		{
			map[*b2] += B;
			*vb++ = *b2++;
		}
	}
}



int main ()
{
	int n;

	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		star[i].index = i;
		cin >> star[i];
	}

	sort( star, star + n, less_x );
	for (int i = 0; i < n; ++i)
	{
	}
	calculate( star, star + n );

	for (int i = 0; i < n; ++i)
	{
		++level[ map[i] ];
	}

	for (int i = 0; i < n; ++i)
	{
		cout << level[i] << endl;
	}

	return 0;
}