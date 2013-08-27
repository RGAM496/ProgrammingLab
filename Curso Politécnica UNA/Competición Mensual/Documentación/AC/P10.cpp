#include <iostream>


using namespace std;

#define MAX_LENGTH 40
#define MAX_HEIGHT 20
#define MAX_PEAKS 20
#define MAX_HEIGHT_PEAK 20

typedef long long int uint;





uint paths (int x, int y, int r, int h)
{
	static uint path[MAX_LENGTH][MAX_HEIGHT][MAX_PEAKS][MAX_HEIGHT_PEAK] = {0};
	static bool updated[MAX_LENGTH][MAX_HEIGHT][MAX_PEAKS][MAX_HEIGHT_PEAK] = {false};

	

	uint &p = path[x][y][r][h];
	bool &u = updated[x][y][r][h];

	if( x < 0 || y < 0 )
	{
		
		return 0;
	}

	if( u == false )
	{
		const int
			min_x = h + 2 * ( r - 1 ),
			min_diff = min_x + 2 - h,
			min_sum = min_x + h,
			diff_xy = x - y,
			sum_xy = x + y;
		u = true;
		if( diff_xy <= 0 )
		{
			p = diff_xy == 0 && !r;
			
		}
		else if( r && ( diff_xy < min_diff || sum_xy < min_sum ) )
		{
			p = 0;
			
		}
		else
		{
			if( y == h - 1 )
			{
				if( r )
				{
					p += paths( x - 2, y, r - 1, h );
					
				}
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
	else
	{
		
	}

	
	return p;
}


int main ()
{
	int n, r, k;

	while( cin >> n >> r >> k, !cin.fail() )
	{
		
		cout << paths( n + n, 0, r, k ) << endl;
		
	}

	return 0;
}