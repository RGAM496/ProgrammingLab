#include <iostream>

using namespace std;

#define MAX_LENGTH 40
#define MAX_HEIGHT 20
#define MAX_PEAKS 20
#define MAX_HEIGHT_PEAK 20

typedef long long int uint;


uint paths (int x, int y, int r, int h)
{
	cerr << "\nPATHS"
		<< "\t" << x
		<< "\t" << y
		<< "\t" << r
		<< "\t" << h;
	static uint path[MAX_LENGTH][MAX_HEIGHT][MAX_PEAKS][MAX_HEIGHT_PEAK] = {0};
	static bool updated[MAX_LENGTH][MAX_HEIGHT][MAX_PEAKS][MAX_HEIGHT_PEAK] = {false};

	uint &p = path[x][y][r][h];
	bool &u = updated[x][y][r][h];

	if( u == false )
	{
		const int
			max_x = x - h - 2 * ( r - 1 ),
			min_diff = max_x + 2 - h,
			min_sum = max_x + h,
			diff_xy = x - y,
			sum_xy = x + y;
		u = true;
		if( diff_xy <= 0 || ( r && ( diff_xy <= min_diff || sum_xy < min_sum ) ) )
		{
			p = 0;
			cerr << "\t\t" << p;
		}
		else
		{
			if( y == h - 1 )
			{
				if( r )
					p += 1 + paths( x - 2, y, r - 1, h );
				p += paths( x - 2, y + 2, r, h );
			}
			else
			{
				p += paths( x - 1, y + 1, r, h );
			}
			if( y > 0 )
			{
				p += paths( x - 1, y - 1, r, h );
			}
		}
	}

	return p;
}


int main ()
{
	int n, r, k;

	while( !cin.eof() )
	{
		cin >> n >> r >> k;
		cerr << "\n\nTEST CASE"
			<< "\t" << n
			<< "\t" << r
			<< "\t" << k
			<< "\n";
		cout << paths( n + n, 0, r, k ) << endl;
	}

	return 0;
}