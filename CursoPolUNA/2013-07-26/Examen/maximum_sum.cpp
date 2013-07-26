#include <iostream>
using namespace std;

#define MAX_N 100
#define MIN_VALUE (-128)
#define MIN_SUM (MAX_N * MAX_N * MIN_VALUE)


int array[MAX_N][MAX_N];


inline int sum (int ix, int iy, int fx, int fy)
{
	int s = 0;
	cerr << "\t" << ix << " " << iy << " " << fx << " " << fy << "\t\t";
	for (; ix <= fx; ++ix)
	{
		for (; iy <= fy; ++iy)
		{
			cerr << array[ix][iy] << ' ';
			s += array[ix][iy];
		}
	}
	cerr << "\n\t\t\t\ts: " << s << endl;
	return s;
}


inline int max_sum (int n)
{
	int max = MIN_SUM, s;
	for (int ix = 0; ix < n; ++ix)
	{
		for (int iy = 0; iy < n; ++iy)
		{
			for (int fx = ix; fx < n; ++fx)
			{
				for (int fy = iy; fy < n; ++fy)
				{
					s = sum (ix, iy, fx, fy);
					if (max < s)
						max = s;
				}
			}
		}
	}

	return max;
}


int main ()
{
	int n;

	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> array[i][j];
		}
	}

	cout << max_sum (n) << endl;

	return 0;
}