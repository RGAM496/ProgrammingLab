#include <cstdio>
#include <list>

using namespace std;

typedef unsigned int uint;

#define MAX_CELLS 75


inline int get_uint (uint &n)
{
	return scanf ("%u", &n);
}


template <class C, size_t SIZE = MAX_CELLS>
struct Stack
{
	C first[SIZE], *last;

	inline void clear () {last = first;}
	inline void push (const C &c) {*last = c; ++last;}
	inline void push () {++last;}
	inline void pop () {--last;}
	inline C & operator [] (size_t n) {return first[n];}
};


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


typedef Control <MAX_CELLS> Cell;
typedef Stack <uint> Result;


Cell cell[MAX_CELLS];
Result result, r_aux;
Stack <Cell> c_aux;
size_t n;


inline void solve (size_t start, size_t &size)
{
	size_t i;
	Cell &c = c_aux[start];
	++start;
	c_aux.push ();
	Cell &nc = c_aux[start];
	for (i = start; i < size; ++i)
	{
		r_aux.push (i);
		nc.store_fusion (c, cell[i]);
		if  (nc.controlled_cells == n)
		{
			size = i;
			result = r_aux;
		}
		else
		{
			solve (start, size);
		}
		r_aux.pop ();
	}
	c_aux.pop ();
}


inline size_t solve ()
{
	size_t size, i;
	r_aux.clear ();
	c_aux.clear ();
	size = n;
	for (i = 0; i < n; ++i)
	{
		c_aux.push (cell[i]);
		r_aux.push (i);
		solve (0, size);
		c_aux.pop ();
		r_aux.pop ();
	}
	return size;
}


int main ()
{
	size_t size, test_case;
	test_case = 0;
	while (get_uint (n) == 1)
	{
		++test_case;
		for (size_t i = 0; i < n; ++i)
		{
			Cell &c = cell[i];
			c.size = n;
			for (size_t j = 0; j < n; ++j)
			{
				get_uint (c[j]);
			}
			c[i] = 1;
		}

		size = solve ();
		printf("Case %u: %u ", test_case, size);
		for (size_t i = 0; i < size; ++i)
			printf(" %u", result[i]);
		putchar ('\n');
	}

	return 0;
}