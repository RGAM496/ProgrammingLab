#include <cstdio>
#include <algorithm>

using std::sort;

#define MAX_CELLS 75

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


/*********************************************************/


struct Control
{
	int	c[MAX_CELLS],
		controlled_cells;

	inline int & operator [] (const size_t n) {return c[n];}
	inline int operator [] (const size_t n) const {return c[n];}

	inline int count () {
		int r = 0;
		for (size_t i = 0; i < CELLS; ++i)
			r += c[i];
		return r;
	}

	inline void store_count () {
		controlled_cells = count ();
	}

	inline Control & operator |= (const Control &co) {
		for (size_t i = 0; i < CELLS; ++i)
			c[i] |= co[i];
		return *this;
	}

	inline void combine (const Control &a, const Control &b) {
		*this = a;
		*this |= b;
		store_count ();
	}

	#ifdef DEBUG
	inline void print (FILE *f = stderr) {
		fprintf(f, "(%d,%d) ", CELLS, controlled_cells);
		for (size_t i = 0; i < CELLS; ++i)
			fprintf (f, "%d", c[i]);
		fputc ('\n', f);
	}
	#endif
};


struct Cell
{
	int number;
	Control control;

	inline int & operator [] (const size_t n) {return control[n];}
	inline int operator [] (const size_t n) const {return control[n];}

	inline Cell & operator = (const Cell &c)
	{
		number = c.number;
		control.controlled_cells = c.control.controlled_cells;
		return *this;
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
	size_t i;

	for (i = 1; i <= MAX_CELLS; ++i)
	{
		
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


int main ()
{
	int i, j;

	init ();

	while (get_int (CELLS) == 1)
	{
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
	}

	return 0;
}