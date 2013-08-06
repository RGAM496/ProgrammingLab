#include <iostream>
#include <queue>
#include <string>

using namespace std;

#define N 6
#define W (N + 1)
#define ROWS (N + W)
#define COLUMS ROWS
#define ADYACENCIAS 4


struct Square
{
	int r, c;

	inline void operator += (const Square &s) {
		r += s.r;
		c += s.c;
	}

	inline bool is_invalid () {
		return r < 0 || c < 0 || r >= ROWS || c >= COLUMS;
	}

	inline void set_sum (const Square &a, const Square &b) {
		operator = (a);
		operator += (b);
	}
};

istream & operator >> (istream &is, Square &sq)
{
	return is >> sq.r >> sq.c;
}


const Square ady[ADYACENCIAS] = {
	{ 0, -2},
	{-2,  0},
	{ 0,  2},
	{ 2,  0}
};

const char dir[ADYACENCIAS] = {
	'S',
	'W',
	'N',
	'E'
};


struct Path
{
	Square position;
	string path;

	inline void push (const char d, const Square &s) {
		position = s;
		path += d;
	}
};


struct Grid
{
	bool board[ROWS][COLUMS];

	Grid () : board() {}


	inline void add_wall (const Square &ws, const Square &we)
	{
		int r, c;
		r = ws.r;
		c = ws.c;
		if (r == we.r)
		{
			for (; c <= we.c; ++c)
			{
				board[r][c] = true;
			}
		}
	}


	inline string path (const Square &start, const Square &end)
	{

	}
};


int main ()
{
	return 0;
}