#include <cstdio>

using namespace std;

typedef unsigned int uint;

#define MAX_CELLS 75


inline int get_uint (uint &n)
{
	return scanf ("%u", &n);
}


inline int get_bit (uint &n)
{
	return scanf ("%1u", &n);
}


template <typename N>
inline N min (const N a, const N b)
{
	return a < b ? a : b;
}


template <class C, size_t SIZE = MAX_CELLS>
struct Stack
{
	C first[SIZE], *last;

	inline void clear () {last = first;}
	inline void push (const C &c) {*last = c; ++last;}
	inline void push () {++last;}
	inline void pop () {--last;}
	inline size_t size () const {return last - first;}
	inline C & operator [] (size_t n) {return first[n];}
	inline C & front () {return *first;}
	inline C & back () {return last[-1];}

	inline Stack <C, SIZE> & operator = (const Stack <C, SIZE> &st) {
		clear ();
		for (const C *p = st.first; p < st.last; ++p) {
			push (*p);
		}
		return *this;
	}
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

	inline Control <SIZE> & operator |= (const Control <SIZE> &co) {
		for (size_t i = 0; i < size; ++i)
			c[i] |= co[i];
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
		*this |= b;
		store_count ();
	}

	/*inline void print (FILE *f = stderr) {
		fprintf(f, "(%u)", size);
		for (size_t i = 0; i < size; ++i)
			fprintf (f, "%u", c[i]);
		fputc ('\n', f);
	}*/
};


typedef Control <MAX_CELLS> Cell;
typedef Stack <uint> Result;


Cell cell[MAX_CELLS];
Result result, r_aux;
Stack <Cell> c_aux;
size_t n;


inline void solve (size_t start, size_t &size)
{
	//fprintf(stderr, "\nsolve (%u, %u)\n", start, size);
	size_t i, st_i;
	Cell &c = c_aux.back ();
	c_aux.push ();
	Cell &nc = c_aux.back ();
	st_i = start++;
	for (i = st_i; i < min (n, st_i + size); ++i)
	{
		//fprintf(stderr, "\ti: %u < %u (%u) (%u)\n", i, min (n, st_i + size), n, size);
		r_aux.push (i);
		nc.store_fusion (c, cell[i]);
		if  (nc.controlled_cells == n)
		{
			size = r_aux.size ();
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
	//fprintf(stderr, "\n\nSOLVE\n\n");
	size_t size, i;

	for (i = 0; i < n; ++i)
	{
		if (cell[i].controlled_cells == n) {
			result.clear ();
			result.push (i);
			return 1;
		}
	}

	r_aux.clear ();
	c_aux.clear ();
	size = n;
	for (i = 0; i < n;)
	{
		r_aux.push (i);
		c_aux.push (cell[i]);
		solve (++i, size);
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
		result.clear ();
		for (size_t i = 0; i < n; ++i)
		{
			result.push (i);
			Cell &c = cell[i];
			c.size = n;
			for (size_t j = 0; j < n; ++j)
			{
				get_bit (c[j]);
			}
			c[i] = 1;
			c.store_count ();
		}

		size = solve ();
		printf("Case %u: %u", test_case, size);
		for (size_t i = 0; i < size; ++i)
			printf(" %u", result[i] + 1);
		putchar ('\n');
	}

	return 0;
}