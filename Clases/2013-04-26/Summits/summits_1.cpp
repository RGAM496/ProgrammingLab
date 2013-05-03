#include <cstdio>
#include <deque>

using namespace std;

#define MAX_W 500
#define MAX_H 500

typedef unsigned int uint;


/************************************************/


inline int get_uint (uint &n)
{
	return scanf ("%u", &n);
}


/************************************************/


enum Exploration
{
	UNKNOWN,
	SUMMIT,
	NO_SUMMIT
};


struct Coord
{
	uint x, y;

	inline void set (uint x, uint y) {
		this->x = x;
		this->y = y;
	}

	Coord (uint x, uint y) : x(x), y(y) {}
	Coord () {}
};


struct Point
{
	uint height;
	Exploration type;

	uint highest_neighbor;
	bool was_in_queue;

	inline Point & operator = (uint h) {
		this->height = h;
		return *this;
	}

	inline Point & operator = (Exploration e) {
		this->type = e;
		return *this;
	}
};


template <class value_type>
struct Matrix
{
	value_type m[MAX_H][MAX_W];

	inline value_type * operator [] (uint n) {return m[n];}

	inline value_type & operator [] (const Coord &c) {return m[c.x][c.y];}
};


struct Map
{
	Matrix<Point> point;
	uint h, w, d, max, min, summits_found;
	deque<Coord> coord;

	inline void reset (uint h, uint w, uint d) {
		this->h = h;
		this->w = w;
		this->d = d;
		summits_found = 0;
	}

	inline void add_summit (const Coord &c) {
		point[c] = SUMMIT;
		++summits_found;
	}


	inline void add_to_queue (const Coord &c) {
		coord.push_back (c);
		point[c].was_in_queue = true;
	}

	inline uint neighbors (const Coord &c, Coord *store);

	inline void readlines ();
	inline void set_height (uint x, uint y, uint h);
	inline void flood ();
};


/************************************************/


uint Map::neighbors (const Coord &c, Coord *store)
{
	uint index = 0;

	if (c.x > 0)
	{
		store[index].set (c.x - 1, c.y);
		++index;
	}
	if (c.x < this->h)
	{
		store[index].set (c.x + 1, c.y);
		++index;
	}
	if (c.y > 0)
	{
		store[index].set (c.x, c.y - 1);
		++index;
	}
	if (c.y < this->w)
	{
		store[index].set (c.x, c.y + 1);
		++index;
	}

	return index;
}


void Map::readlines ()
{
	uint h, i, j;

	get_uint (h);
	point[0][0] = h;
	point[0][0] = UNKNOWN;
	point[0][0].was_in_queue = false;
	this->max = h;
	this->min = h;
	for (i = 1; i < this->w; ++i)
	{
		get_uint (h);
		this->set_height (0, i, h);
	}
	for (i = 1; i < this->h; ++i)
	{
		for (j = 0; j < this->w; ++j)
		{
			get_uint (h);
			this->set_height (i, j, h);
		}
	}

	j = coord.size();
	for (i = 0; i < j; ++i) {
		point[coord[i]].was_in_queue = true;
		add_summit (coord[i]);
	}
}


void Map::set_height (uint x, uint y, uint h)
{
	Coord c;
	point[x][y] = h;
	point[x][y] = UNKNOWN;
	point[x][y].was_in_queue = false;
	if (h > this->max) {
		this->max = h;
		coord.clear ();
		c.set (x, y);
		coord.push_back (c);
	}
	else if (h == this->max) {
		c.set (x, y);
		coord.push_back (c);
	}
	else if (h < this->min)
		this->min = h;
}


void Map::flood ()
{
	Coord c, vecino[4];
	int total_vecinos, min_summit = this->min + this->d;
	Point *p, *v;

	#ifdef DEBUG
		#define debug_queue() \
			for (int i = 0; i < coord.size(); ++i) \
				printf(" (%d,%d)", coord[i]); \
			puts("\n")
		#define debug_summits() printf("\t%d\n", summits_found)
		#define debug_points() \
			for (int i = 0; i < this->h; ++i) { \
				for (int j = 0; j < this->w; ++j) \
					printf(" %c", c.x == i && c.y == j ? 'X' : point[i][j].was_in_queue ? 'O' : '.'); \
				puts("\n"); \
			}
	#else
		#define debug_queue() {}
		#define debug_summits() {}
		#define debug_points() {}
	#endif

	debug_queue();
	while (! coord.empty ())
	{
		c = coord.front ();
		coord.pop_front ();
		p = &point[c];

		total_vecinos = neighbors (c, vecino);
		point[c].highest_neighbor = point[vecino[0]].height;
		for (int i = 0; i < total_vecinos; ++i)
		{
			v = &point[vecino[i]];
			if (p->highest_neighbor < v->height)
				p->highest_neighbor = v->height;
			if (p->height > v->height)
				v->type = NO_SUMMIT;
			else if (p->height == v->height)
				v->type = p->type;

			if (v->was_in_queue == false)
				add_to_queue (vecino[i]);
		}

		if (p->type == UNKNOWN) {
			if (p->height < min_summit)
				p->type = NO_SUMMIT;
			else if (p->height >= p->highest_neighbor + this->d)
				add_summit (c);
		}

		debug_points();
		debug_queue();
	}

	debug_points();
}


/************************************************/


Map map;

int main ()
{
	uint test_cases, h, w, d;

	get_uint (test_cases);
	while (test_cases)
	{
		scanf("%u%u%u", &h, &w, &d);
		map.reset (h, w, d);
		map.readlines ();
		map.flood ();

		printf ("%u\n", map.summits_found);
		--test_cases;
	}

	return 0;
}