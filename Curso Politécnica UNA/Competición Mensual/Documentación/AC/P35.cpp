#include <iostream>
#include <queue>
#include <string>

using namespace std;

#define N 6
#define W (N + 1)
#define ROWS (N + W)
#define COLUMS ROWS
#define ADYACENCIAS 4
#define WALLS 3


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

	inline void to_wall () {
		r *= 2;
		c *= 2;
	}

	inline void to_grid () {
		to_wall ();
		--r;
		--c;
	}
};

istream & operator >> (istream &is, Square &sq)
{
	return is >> sq.r >> sq.c;
}

inline bool operator == (const Square &a, const Square &b)
{
	return a.r == b.r && a.c == b.c;
}

inline bool operator != (const Square &a, const Square &b)
{
	return a.r != b.r || a.c != b.c;
}


const Square ady[ADYACENCIAS] = {
	{ 0, -2},
	{-2,  0},
	{ 0,  2},
	{ 2,  0}
};

const char dir[ADYACENCIAS] = {
	'N',
	'W',
	'S',
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

	inline void push (const char d) {
		path += d;
	}

	inline void go (int d) {
		position += ady[d];
		path += dir[d];
	}
};


struct Grid
{
	bool board[COLUMS][ROWS];

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
				board[c][r] = true;
			}
		}
		else
		{
			for (; r <= we.r; ++r)
			{
				board[c][r] = true;
			}
		}
	}


	inline bool & at (const Square &sq)
	{
		return board[sq.c][sq.r];
	}


	inline bool & wall_between (const Square &a, const Square &b)
	{
		int r, c;
		r = (a.r + b.r) / 2;
		c = (a.c + b.c) / 2;
		return board[c][r];
	}


	inline string path (const Square &start, const Square &end)
	{
		Path p, p_aux;
		Square sq;
		queue <Path> q;

		p.position = start;
		while (p.position != end)
		{
			at (p.position) = true;
			for (int i = 0; i < ADYACENCIAS; ++i)
			{
				p_aux = p;
				p_aux.go (i);
				if (p_aux.position.is_invalid ())
					continue;
				if (at (p_aux.position))
					continue;
				if (wall_between (p.position, p_aux.position))
					continue;
				q.push (p_aux);
			}

			p = q.front (); q.pop ();
		}

		return p.path;
	}
};


ostream & operator << (ostream &os, const Grid &g)
{
	for (int c = 0; c < COLUMS; ++c)
	{
		for (int r = 0; r < ROWS; ++r)
		{
			os << g.board[c][r];
		}
		os << '\n';
	}
	return os;
}


int main ()
{
	Square start, end, ws, we;

	while (cin >> start, start.r || start.c)
	{
		Grid grid;
		cin >> end;
		start.to_grid ();
		end.to_grid ();
		for (int i = 0; i < WALLS; ++i)
		{
			cin >> ws >> we;
			ws.to_wall ();
			we.to_wall ();
			grid.add_wall (ws, we);
		}
		cout << grid.path (start, end) << endl;
	}

	return 0;
}