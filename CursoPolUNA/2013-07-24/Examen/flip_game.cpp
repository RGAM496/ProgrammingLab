#include <iostream>

using namespace std;

#define N 4
#define COUNT_MIN 0
#define COUNT_MAX 16
#define MAX_COMBINATIONS 65536
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
		return r == COUNT_MIN || r == COUNT_MAX;
	}
};

Cuad cuad;


inline uint bit (uint it, uint i)
{
	return (it >> i) % 2;
}

inline void coord (uint i, uint &x, uint &y)
{
	x = i / N;
	y = i % N;
}


inline uint min_movements ()
{
	uint min, moves, b, x, y;

	min = N + 1;
	for (uint it = 0; it < MAX_COMBINATIONS; ++it)
	{
		Cuad aux = cuad;
		// cerr << it << '\n'; // ¡CON ESTO NO CUELGA!
		moves = 0;
		for (uint i = 0; i < COUNT_MAX; ++i)
		{
			b = bit (it, i);
			if (b) {
				++moves;
				coord (i, x, y);
				aux.touch (x, y);
			}
		}
		if (aux.uniform ())
		{
			if (min > moves)
				min = moves;
		}
	}

	return min;
}


int main ()
{
	uint m;
	char c;
	for_loop (i)
	{
		for_loop (j)
		{
			cin >> c;
			cuad.c[i][j] = (c == 'b');
		}
		cin >> c;
	}

	m = min_movements ();
	if (m == N + 1)
		cout << "Impossible\n";
	else
		cout << m << endl;

	return 0;
}