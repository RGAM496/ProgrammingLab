#include <cstdio>
#include <algorithm>

using std::sort;


#define MIN_X 1
#define MAX_X 500
#define MIN_Y 1
#define MAX_Y 500
#define MIN_D 1
#define MAX_D 1000000000
#define MIN_H 0
#define MAX_H 1000000000

#define MAX_XY (MAX_X * MAX_Y)
#define NOT_EVALUATED -1

#define for_int(i,n) for (int i = 0; i < n; ++i)


/**********************************************************/


struct Point
{
	int h, flood_zone;

	inline void set (int h, int flood_zone) {
		this->h = h;
		this->flood_zone = flood_zone;
	}
};


struct Coord
{
	int x, y;

	inline void set (int x, int y) {
		this->x = x;
		this->y = y;
	}

	inline Coord & operator += (const Coord &c) {
		this->x += c.x;
		this->y += c.y;
		return *this;
	}
};


bool operator < (const Coord &c1, const Coord &c2);


/**********************************************************/


template <class v_type, size_t SIZE>
struct Queue
{
	v_type buffer[SIZE];
	size_t first, last;
	enum Operation {POP, PUSH} last_operation;

	inline void next (size_t &index) {index = (index + 1) % SIZE;}
	inline void previous (size_t &index) {index = (SIZE - 1 + index) % SIZE;}

	inline void clear () {last = first = 0; last_operation = POP;}
	inline bool empty () {return first == last && last_operation == POP;}

	inline size_t size () {return first < last ? last - first : SIZE + last - first;}

	inline v_type & front () {return buffer[first];}
	inline v_type & back () {return buffer[last-1];}

	inline void push (const v_type &v) {buffer[last] = v; next(last); last_operation = PUSH;}
	inline void pop () {next(first); last_operation = POP;}
};


/**********************************************************/


struct Map
{
	Point point[MAX_X][MAX_Y];
	Coord coord[MAX_X*MAX_Y];
	Queue <Coord, MAX_XY> not_evaluated;
	int X, Y, D;

	inline void read ();

	inline Point & get_point (const Coord &c) {return point[c.x][c.y];}
	inline Point & operator [] (const Coord &c) {return get_point (c);}

	inline bool is_invalid (const Coord &c) {
		return c.x < 0 || c.y < 0 || c.x >= X || c.y >= Y;
	}

	int summits ();
};


/**********************************************************/


void Map::read ()
{
	int h, i;
	scanf ("%d %d %d", &X, &Y, &D);
	i = 0;
	for_int (x, X)
	{
		for_int (y, Y)
		{
			scanf ("%d", &h);
			point[x][y].set (h, NOT_EVALUATED);
			coord[i].set (x, y);
			++i;
		}
	}
}


int Map::summits ()
{
	static Coord neighbor[4] = {{-1,0}, {0,-1}, {0,1}, {1,0}};
	const int AREA = X * Y;
	int result, candidates, pd;
	bool found_summits;
	
	sort (coord, coord + AREA);
	not_evaluated.clear();
	result = 0;

	for_int (i, AREA)
	{
		Coord &c = coord[i];
		Point &p = get_point (c);
		
		if (p.flood_zone == NOT_EVALUATED)
		{
			pd = p.h - D;
			candidates = 0;
			found_summits = true;
			p.flood_zone = p.h;
			not_evaluated.push (c);

			while (not_evaluated.empty() == false)
			{
				Coord ec = not_evaluated.front(); not_evaluated.pop();
				Point &ep = get_point (ec);

				candidates += ep.h == p.h;

				for_int (n, 4)
				{
					Coord nc = ec;
					nc += neighbor[n];
					if (is_invalid (nc))
						continue;
					Point &np = get_point (nc);

					if (np.flood_zone == NOT_EVALUATED)
					{
						np.flood_zone = p.h;
						if (np.h > pd)
							not_evaluated.push (nc);
					}
					else if (np.flood_zone > ep.h)
					{
						if (np.h > pd && np.flood_zone > p.h)
							found_summits = false;
					}
				}
			}

			if (found_summits)
				result += candidates;
		}
	}

	return result;
}


/**********************************************************/


Map map;


bool operator < (const Coord &c1, const Coord &c2)
{
	return map[c1].h > map[c2].h;
}


/**********************************************************/


int main ()
{
	int T;

	scanf ("%d", &T);
	for_int (test_case, T)
	{
		map.read();
		printf ("%d\n", map.summits());
	}

	return 0;
}