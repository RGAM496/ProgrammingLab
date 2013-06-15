#include <cstdio>
#include <list>

using namespace std;

typedef unsigned int uint;

#define MAX_CELLS 75


inline int get_uint (uint &n)
{
	return scanf ("%u", &n);
}


template <size_t SIZE = MAX_CELLS>
struct Control
{
	uint c[SIZE];
	size_t size;
	uint controlled_cells;

	inline uint & operator [] (const size_t n) {return c[n];}
	inline uint operator [] (const size_t n) const {return c[n];}

	inline Control <SIZE> & operator = (const Control <SIZE> &co) {
		size = co.size;
		for (size_t i = 0; i < size; ++i)
			c[i] = co[i];
		return *this;
	}

	inline Control <SIZE> & operator &= (const Control <SIZE> &co) {
		for (size_t i = 0; i < size; ++i)
			c[i] &= co[i];
		return *this;
	}

	inline uint count () {
		uint r = 0;
		for (size_t i = 0; i < size; ++i)
			r += c[i];
		return r;
	}

	inline void store_count () {
		controlled_cells = count ();
	}

	inline void store_fusion (const Control <SIZE> &a, const Control <SIZE> &b) {
		*this = a;
		*this &= b;
		store_count ();
	}
};

struct Tree;
extern Tree cell[MAX_CELLS];


struct Tree
{
	Control <MAX_CELLS> c;
	size_t start, size;
	Tree *t[MAX_CELLS];

	inline void init (size_t sz, size_t st) {
		start = st;
		sz = size;
		for (size_t i = start; i < size; ++i)
			t[i] = 0;
	}

	inline void clear () {
		for (size_t i = start; i < size; ++i) {
			Tree *&b = t[i];
			if (b) {
				delete b;
				b = 0;
			}
		}
	}

	inline void clear (size_t sz) {
		clear ();
		size = sz;
	}

	inline Tree * branch (size_t n) {
		Tree *&b = t[n];
		if (!b) {
			b = new Tree (size, start + 1);
			b->c.store_fusion (c, cell[n].c);
		}
		return b;
	}	

	inline uint & operator [] (size_t n) {return c[n];}

	Tree (size_t sz = MAX_CELLS, size_t st = 0) {
		init (sz, st);
	}

	~Tree () {
		clear ();
	}
};


Tree cell[MAX_CELLS];





int main ()
{
	size_t n;

	while (get_uint (n) == 1)
	{
		for (size_t i = 0; i < n; ++i)
		{
			Tree &t = cell[i];
			t.clear (n);
			for (size_t j = 0; j < n; ++j)
			{
				get_uint (t[j]);
			}
			t[i] = 1;
		}
	}

	return 0;
}