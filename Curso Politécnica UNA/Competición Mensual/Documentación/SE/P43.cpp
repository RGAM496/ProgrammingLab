#include <iostream>
using namespace std;

#define MAX_R 1000
#define MAX_C 1000
#define DIRTY -1

int ms, msc[MAX_R][MAX_C], m[MAX_R][MAX_C];

inline void reset( int R, int C )
{
	ms = 0;
	for (int i = 0; i < R; ++i)
	{
		for (int j = 0; j < C; ++j)
		{
			msc[i][j] = DIRTY;
		}
	}
}

int maximum_square_corner( int r, int c )
{
	int &result = msc[r][c], r_aux;

	if( result == DIRTY )
	{
		r_aux = r * c;
		if( r > 0 )
		{
			r_aux = min( r_aux, maximum_square_corner( r - 1, c ) );
			if( c > 0 )
			{
				r_aux = min( r_aux, maximum_square_corner( r - 1, c - 1 ) );
			}
		}
		if( c > 0 )
		{
			r_aux = min( r_aux, maximum_square_corner( r, c - 1 ) );
		}
		if( r == 0 && c == 0 )
		{
			r_aux = 0;
		}
		++r_aux;
		result = m[r][c] ? r_aux : 0;
		ms = max( ms, result );

	}

	return result;
}


inline int maximum_square( int R, int C )
{
	maximum_square_corner( R - 1, C - 1 );
	return ms;
}


int main ()
{
	int R, C, r, c;

	while( cin >> R >> C, R || C )
	{
		reset( R, C );
		for( r = 0; r < R; ++r )
		{
			for( c = 0; c < C; ++c )
			{
				cin >> m[r][c];
			}
		}
		cout << maximum_square( R, C ) << endl;
	}

	return 0;
}