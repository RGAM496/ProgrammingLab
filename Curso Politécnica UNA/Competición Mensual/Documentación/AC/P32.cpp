#include <iostream>

using namespace std;

#define MAX_DIGITS 10

typedef unsigned int uint;

uint digit_count[MAX_DIGITS];


int main ()
{
	uint n, d, dc;
	char c;

	cin >> n;

	if (n == 1)
		cout << n << endl;
	else if (n == 0)
		cout << 10 << endl;
	else
	{
		for (d = MAX_DIGITS - 1; n > 1 && d >= 2; )
		{
			if (n % d)
				--d;
			else
			{
				++digit_count[d];
				n /= d;
			}
		}
		if (n > 1)
			cout << -1 << endl;
		else
		{
			for (d = 2; d < MAX_DIGITS; ++d)
			{
				dc = digit_count[d];
				c = d + '0';
				while (dc--)
					cout << c;
			}
			cout << '\n';
		}
	}

	return 0;
}