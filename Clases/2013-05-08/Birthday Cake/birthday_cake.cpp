#include <cstdio>

#define MAX_2N 100
#define MIN_AB -500
#define MAX_AB 500


inline void get_int (int &n)
{
	scanf("%d", &n);
}

inline void get_int (int &n1, int &n2)
{
	scanf("%d %d", &n1, &n2);
}


struct Point
{
	int x, y;

	inline int value (int A, int B) {
		return A*x + B*y;
	}

	inline void readline() {
		get_int (x, y);
	}
};


int main()
{
	int N, balance, value;
	Point p[MAX_2N];
	bool alles_ok, not_finished;

	while (get_int(N), N)
	{
		N *= 2;
		for (int i = 0; i < N; ++i) {
			p[i].readline();
		}

		not_finished = true;
		for (int A = 0; not_finished && A <= MAX_AB; ++A)
		{
			for (int B = MIN_AB; not_finished && B <= MAX_AB; ++B)
			{
				balance = 0;
				alles_ok = true;
				for (int i = 0; i < N; ++i)
				{
					value = p[i].value (A, B);
					if (value < 0)
						--balance;
					else if (value > 0)
						++balance;
					else {
						alles_ok = false;
						break;
					}
				}
				if (alles_ok && balance == 0)
				{
					printf("%d %d\n", A, B);
					not_finished = false;
				}
			}
		}
	}

	return 0;
}