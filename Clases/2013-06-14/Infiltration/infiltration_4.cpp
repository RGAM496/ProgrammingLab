#include <cstdio>
#include <algorithm>
#include <bitset>

using std::sort;
using std::bitset;


#define MAX_CELLS 75

typedef bitset<MAX_CELLS>::reference rint;

#ifdef DEBUG
#define dprint(x) x.print()
#else
#define dprint(x) {}
#endif


/*********************************************************/


int CELLS, limit[MAX_CELLS+1];


inline int get_int (int &n)
{
	return scanf ("%d", &n);
}


inline int get_bit (int &n)
{
	return scanf ("%1d", &n);
}

inline int get_bit (rint ref)
{
	int n, r;
	r = get_bit (n);
	ref = n;
	return r;
}


template <typename N>
inline void set_min (N &a, const N &b)
{
	if (a > b)
		a = b;
}


template <typename N>
inline N min (const N &a, const N &b)
{
	return a < b ? a : b;
}


/*********************************************************/


template <typename C, size_t SIZE = MAX_CELLS>
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


/*********************************************************/


struct Control
{
	bitset <MAX_CELLS> c;
	int controlled_cells;

	inline rint operator [] (const size_t n) {return c[n];}
	inline bool operator [] (const size_t n) const {return c[n];}

	inline int count () {
		return c.count ();
	}

	inline void store_count () {
		controlled_cells = count ();
	}

	inline Control & operator |= (const Control &co) {
		c |= co.c;
		return *this;
	}

	inline void combine (const Control &a, const Control &b) {
		*this = a;
		*this |= b;
		store_count ();
	}

	#ifdef DEBUG
	inline void print (FILE *f = stderr) {
		bool ci;
		fprintf(f, "(%d,%d) ", CELLS, controlled_cells);
		for (size_t i = 0; i < CELLS; ++i)
			fprintf (f, "%d", (ci = c[i]));
		fputc ('\n', f);
	}
	#endif
};


struct Cell
{
	int number;
	Control control;

	inline rint operator [] (const size_t n) {return control[n];}
	inline bool operator [] (const size_t n) const {return control[n];}

	inline void operator = (const Cell &c)
	{
		number = c.number;
		control.controlled_cells = c.control.controlled_cells;
	}
};


inline bool operator < (const Control &c1, const Control &c2)
{
	return c1.controlled_cells > c2.controlled_cells;
}


inline bool operator < (const Cell &c1, const Cell &c2)
{
	return c1.control < c2.control;
}


/*********************************************************/


Cell cell_aux[MAX_CELLS], cell[MAX_CELLS];


inline void init ()
{
	size_t i, j, l, pot2;

	pot2 = 1;
	l = 2;
	for (i = 1; i <= MAX_CELLS; ++l)
	{
		pot2 <<= 1;
		for (j = 0; j < pot2 && i <= MAX_CELLS; ++j, ++i)
		{
			limit[i] = l;
		}
	}

	for (i = 0; i < MAX_CELLS; ++i)
		cell_aux[i].number = i;
}


inline void sort_cells ()
{
	int i, j;

	for (i = 0; i < CELLS; ++i) {
		cell_aux[i].control.store_count ();
		cell[i] = cell_aux[i];
	}

	sort (cell, cell + CELLS);

	for (i = 0; i < CELLS; ++i)
	{
		cell[i][i] = 1;
		for (j = i + 1; j < CELLS; ++j)
		{
			cell[i][j] = cell_aux[cell[i].number][cell[j].number];
			cell[j][i] = 1 - cell[i][j];
		}
	}

	#ifdef DEBUG
	for (i = 0; i < CELLS; ++i) {
		fprintf(stderr, "%d: ", cell_aux[i].number);
		dprint(cell_aux[i].control);
	}
	fputc ('\n', stderr);
	for (i = 0; i < CELLS; ++i) {
		fprintf(stderr, "%d: ", cell[i].number);
		dprint(cell[i].control);
	}
	fputc ('\n', stderr);
	fputc ('\n', stderr);
	#endif
}


/*********************************************************/


Stack <int> solution, solution_aux;
Stack <Control> control;


int solve (int start, int current_size, int &l)
{
	int i;

	#ifdef DEBUG_SOLVE
	fprintf(stderr, "\t(%d) %d: ", l, current_size);
	for (i = 0; i < CELLS; ++i)
		fprintf(stderr, "%d", control[current_size-1][i]);
	for (i = 0; i < current_size; ++i)
		fprintf(stderr, " %d", solution_aux[i]);
	fputc ('\n', stdout);
	#endif

	if (current_size < l)
	{
		Control &c = control[current_size - 1];
		if (c.controlled_cells == CELLS)
		{
			l = current_size;
			solution = solution_aux;
		}
		else
		{
			control.push ();
			Control &c_aux = control[current_size];
			++current_size;
			for (int i = start + 1; i < CELLS; ++i)
			{
				solution_aux.push (i);
				c_aux.combine (cell[i].control, c);
				solve (i, current_size, l);
				solution_aux.pop ();
			}
			control.pop ();
		}
	}

	return l;
}


int solve ()
{
	int l, i, r;

	r = l = limit[CELLS];
	solution_aux. clear ();
	control.clear ();

	control.push ();
	for (i = 0; i < CELLS; ++i)
	{
		solution_aux.push (i);
		control[0] = cell[i].control;
		set_min (r, solve (i, 1, l));
		solution_aux.pop ();
	}
	control.pop ();

	return l;
}


/*********************************************************/


int main ()
{
	int i, j, r, test_case;

	init ();
	test_case = 0;

	while (get_int (CELLS) == 1)
	{
		++test_case;
		for (i = 0; i < CELLS; ++i)
		{
			Cell &c = cell_aux[i];
			for (j = 0; j < CELLS; ++j)
			{
				get_bit (c[j]);
			}
			c[i] = 1;
		}

		sort_cells ();
		r = solve ();
		printf("Case %d: %d", test_case, r);
		for (size_t i = 0; i < r; ++i)
			printf(" %d", cell[solution[i]].number + 1);
		putchar ('\n');
	}

	return 0;
}