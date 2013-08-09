#include <iostream>
#include <cmath>
using namespace std;

#define MAX_R 1000
#define MAX_C 1000


template <typename N>
inline void set_min( N &a, const N &b )
{
	if( a > b )
		a = b;
}

template <typename N>
inline void set_max( N &a, const N &b )
{
	if( a < b )
		a = b;
}


struct Point
{
	int r, c;
};


int R, C, P, m[ MAX_R ][ MAX_C ];
Point point[ MAX_R * MAX_C ];


inline void reset()
{
	P = 0;
}


inline int max_square( const Point &p )
{
	int r, c, rows, cols;
	Point q = {R - 1, C - 1};
	rows = 1;
	cols = C - p.c;
	for( r = p.r; r <= q.r; ++r )
	{
		for( c = p.c; m[r][c] && c <= q.c; ++c );
		set_min( q.c, --c );
		cols = q.c - p.c + 1;
		if (rows == cols)
			return rows;
		else if (rows > cols)
			return rows - 1;
		++rows;
	}
	return rows - 1;
}


int main ()
{
	Point p;
	int &r = p.r, &c = p.c,
		maximum, max_possible;

	while( cin >> R >> C, R || C )
	{
		maximum = 0;
		reset();
		for( r = 0; r < R; ++r )
		{
			for( c = 0; c < C; ++c )
			{
				cin >> m[r][c];
				if( m[r][c] )
				{
					point[P++] = p;
				}
			}
		}
		max_possible = min( min( R, C ), (int)sqrt( (double)P ) );
		for( r = 0; r < P; ++r )
		{
			set_max( maximum, max_square( point[r] ) );
			if( maximum == max_possible )
				break;
		}
		cout << maximum << endl;
	}

	return 0;
}