#include <iostream>
#include <string>

using namespace std;

#define N 10
#define COUNT_MIN 0
#define COUNT_MAX 100
#define MAX_COMBINATIONS 1024
#define for_loop(i) for (uint i = 1; i <= N; ++i)

typedef unsigned int uint;

struct Cuad
{
	bool c[N+2][N+2];

	inline void flip (uint x, uint y) {
		c[x][y] ^= 1;
	}

	inline void touch (uint x, uint y) {
		flip (x, y);
		flip (x-1, y);
		flip (x+1, y);
		flip (x, y-1);
		flip (x, y+1);
	}

	inline int count () {
		uint r = 0;
		for_loop (i) {
			for_loop (j)
				r += c[i][j];
		}
		return r;
	}

	inline bool uniform () {
		uint r = count ();
		return r == COUNT_MIN;
	}
};

ostream & operator << (ostream &os, const Cuad c)
{
	for_loop (x)
	{
		for_loop (y)
		{
			os << c.c[x][y];
		}
		os << '\n';
	}
	return os;
}

Cuad cuad;


inline uint bit (uint it, uint i)
{
	return (it >> i) % 2;
}

inline void coord (uint i, uint &x, uint &y)
{
	x = (i / N) + 1;
	y = (i % N) + 1;
}


inline uint min_movements ()
{
	uint min, moves, b, x, y;
	Cuad aux;

	if (cuad.uniform ())
	{
		min = 0;
	}
	else
	{
		min = COUNT_MAX + 1;
		for (uint it = 0; it < MAX_COMBINATIONS; ++it)
		{
			aux = cuad;
			moves = 0;
			for (uint i = 0; i < N; ++i)
			{
				b = bit (it, i);
				if (b) {
					++moves;
					coord (i, x, y);
					aux.touch (x, y);
				}
			}
			for (x = 1; x < N; ++x)
			{
				for (y = 1; y <= N; ++y)
				{
					if (aux.c[x][y])
					{
						++moves;
						aux.touch (x + 1, y);
					}
				}
			}
			for (y = 1; y <= N; ++y)
			{
				if (aux.c[x][y])
				{
					moves = COUNT_MAX + 1;
					break;
				}
			}
			if (min > moves)
			{
				min = moves;
			}
		}
	}
	
	return min;
}


int main ()
{
	int m;
	char c;
	string name;
	while (cin >> name, name != "end")
	{
		for_loop (i)
		{
			for_loop (j)
			{
				cin >> c;
				cuad.c[i][j] = (c == 'O');
			}
		}

		m = min_movements ();

		if (m > COUNT_MAX)
			m = -1;

		cout << name << ' ' << m << endl;
	}

	return 0;
}