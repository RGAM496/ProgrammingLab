#include <iostream>
using namespace std;


#define MAX_N 100
#define MIN_VALUE (-256)
#define MIN_SUM (MAX_N * MAX_N * MIN_VALUE)


struct Sum
{
	int value;
	bool updated;
};


int maximum_sum = MIN_SUM;


int array[MAX_N][MAX_N];
Sum store_row_sum[MAX_N][MAX_N][MAX_N] = {0};


inline void compare_maximum_sum (int s)
{
	if (maximum_sum < s)
		maximum_sum = s;
}


int row_sum (int x, int y, int l)
{
	Sum &s = store_row_sum[x][y][l];

	if (s.updated)
		return s.value;

	s.value = l > 1
		? row_sum (x, y, l - 1)
		: 0;
	s.value += array[x][y + l - 1];

	compare_maximum_sum (s.value);

	s.updated = true;

	return s.value;
}


int rect_sum (int x, int y, int l, int a)
{
	int s;
	s = a > 1
		? rect_sum (x + 1, y, l, a - 1)
		: 0;
	s += row_sum (x, y, l);

	compare_maximum_sum (s);

	#ifdef DEBUG_RECT_SUM
	cerr << "rect_sum[" << x << "][" << y << "][" << l << "][" << a << "] = "
		<< s << "\n";
	#endif

	return s;
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

	#ifdef DEBUG
	for (int x = 0; x < n; ++x)
	{
		for (int y = 0; y < n; ++y)
		{
			cerr << "\t" << array[x][y];
		}
		cerr << endl;
	}
	cerr << endl;

	for (int x = 0; x < n; ++x)
	{
		for (int y = 0; y < n; ++y)
		{
			for (int l = 1; l <= n - y; ++l)
			{
				cerr << "row_sum[" << x << "][" << y << "][" << l << "] = "
					<< row_sum (x, y, l) << "\n";
			}
			cerr << "\n";
		}
	}

	for (int x = 0; x < n; ++x)
	{
		for (int y = 0; y < n; ++y)
		{
			for (int l = 1; l <= n - y; ++l)
			{
				for (int a = 1; a <= n - x; ++a)
				{
					cerr << "rect_sum[" << x << "][" << y << "][" << l << "][" << a << "] = "
						<< rect_sum (x, y, l, a) << "\n";
				}
				cerr << "\n";
			}
		}
	}
	#endif

	for (int y = 0; y < n; ++y)
	{
		for (int l = 1; l <= n - y; ++l)
		{
			for (int a = 1; a <= n; ++a)
			{
				rect_sum (0, y, l, a);

				#ifdef DEBUG_RECT_SUM
				cerr << endl;
				#endif
			}
		}
	}
	
	cout << maximum_sum << endl;

	return 0;
}