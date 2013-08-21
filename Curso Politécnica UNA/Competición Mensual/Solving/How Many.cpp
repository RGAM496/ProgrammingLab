#include <iostream>

using namespace std;

#define MAX_LENGTH 40
#define MAX_HEIGHT 20
#define MAX_PEAKS 20
#define MAX_HEIGHT_PEAK 20
#define UNKNOWN 0
#define INVALID -1

typedef long long int uint;


uint paths (int x, int y, int r, int h)
{
	static uint path[MAX_LENGTH][MAX_HEIGHT][MAX_PEAKS][MAX_HEIGHT_PEAK] = {0};

	uint &p = path[x][y][r][h];
	const int
		max_x = x - h - 2 * ( r - 1 ),
		max_diff = max_x + 2 - h,
		diff_xy = x - y;

	if( p == UNKNOWN )
	{
		if( sum_xy < max_xy )
		{
			return 0;
		}
	}

	return p;
}


int main ()
{
	return 0;
}