#include <cstdio>
//#define DEBUG


#define MAX_BEADS 1000
#define MAX_COLORS 51

#define OUTPUT_LOST "some beads may be lost"

#define for_color(i) for (int i = 1; i < MAX_COLORS; ++i)


/***************************************************/


int get_int (int &n)
{
	return scanf("%d", &n);
}


/***************************************************/


template <class vtype, size_t MAX_EDGES>
struct Node
{
	vtype edge[MAX_EDGES], *last_edge;

	inline void clear () {
		last_edge = edge;
	}
	
	inline void push (vtype & p) {
		*last_edge = p;
		++last_edge;
	}

	inline vtype & push () {
		++last_edge;
		return last ();
	}

	inline void pop () {
		--last_edge;
	}

	inline vtype & operator [] (size_t n) {return edge[n];}
	inline vtype & at (size_t n) {return edge[n];}
	inline vtype * p_at (size_t n) {return edge + n;}

	inline vtype & last () {return last_edge[-1];}
	inline vtype * p_last () {return last_edge - 1;}

	inline size_t size () {return last_edge - edge;}
};


/***************************************************/


struct Color
{
	int edge[MAX_COLORS], total_edges;

	inline void clear () {
		for_color (i)
			edge[i] = 0;
		total_edges = 0;
	}

	inline void connect (int color) {
		++edge[color];
		++total_edges;
	}

	inline void connect (int color, int times) {
		edge[color] += times;
		total_edges += times;
	}

	inline void disconnect (int color) {
		--edge[color];
		--total_edges;
	}

	inline void disconnect (int color, int times) {
		edge[color] -= times;
		total_edges -= times;
	}
};


/***************************************************/


struct Bead
{
	int color[2], times;

	inline int & operator[] (size_t n) {return color[n];}

	inline void set (int c1, int c2, int t = 1) {
		color[0] = c1;
		color[1] = c2;
		times = t;
	}

	inline void display() {
		for (int i = 0; i < times; ++i)
			printf("%d %d\n", color[0], color[1]);
	}
};

typedef Node <Bead, MAX_BEADS> Sol;
typedef Node <Sol, MAX_BEADS / 2> Solution;


/***************************************************/


struct Graph
{
	Color color[MAX_COLORS];
	Solution solution;
	Sol sol_aux;
	int total_edges;

	inline void clear () {
		for_color (i)
			color[i].clear();
		total_edges = 0;
	}

	inline void connect (int i, int j) {
		color[i].connect (j);
		color[j].connect (i);
		++total_edges;
	}

	inline void connect (int i, int j, int t) {
		color[i].connect (j, t);
		color[j].connect (i, t);
		total_edges += t;
	}

	inline void connect (const Bead &b) {connect (b.color[0], b.color[1], b.times);}

	inline void disconnect (int i, int j) {
		color[i].disconnect(j);
		color[j].disconnect(i);
		--total_edges;
	}

	inline void disconnect (int i, int j, int t) {
		color[i].disconnect (j, t);
		color[j].disconnect (i, t);
		total_edges -= t;
	}

	inline void disconnect (const Bead &b) {disconnect (b.color[0], b.color[1], b.times);}

	inline bool solve ();
	void solve (int c);
	inline bool check_solution ();
	inline void combine_necklaces (Sol *si, Sol *sj, Bead *bi, Bead *bj);

	inline void push_solution (int i, int j, int t = 1) {
		Sol &sol = solution.last();
		Bead b;
		b.set (i, j, t);
		sol.push (b);
		disconnect (b);
	}

	inline void pop_solution () {
		Sol &sol = solution.last();
		Bead b;
		b = sol.last();
		sol.pop();
		connect (b);
	}

	#ifdef DEBUG
	inline void debug_solution () {
		fprintf(stderr, "\nSize: %d\n", solution.size());
		for (int i = 0; i < solution.size() - 1; ++i) {
			for (int j = 0; j < solution[i].size(); ++j) {
				Bead &b = solution[i][j];
				fprintf(stderr, " (%d,%d)", b.color[0], b.color[1]);
			}
			fprintf(stderr, "\n\n");
		}
	}
	#else
	#define debug_solution() {}
	#endif
};


/***************************************************/


bool Graph::solve ()
{
	int connections, first_color;
	Color *current_color;

	first_color = 0;
	for_color (i)
	{
		current_color = color + i;
		connections = current_color->total_edges;
		if (connections)
		{
			if (connections % 2 || (connections == current_color->edge[i] && connections != total_edges))
				return false;
			if (!first_color)
				first_color = i;
		}
	}

	solution.clear();
	solution.push();
	solution.last().clear();
	solve (first_color);
	while (total_edges)
	{
		for_color (i)
		{
			if (color[i].total_edges)
				solve (i);
		}
	}

	debug_solution ();

	return check_solution ();
}


/***************************************************/


bool Graph::check_solution ()
{
	Sol *si, *sl;
	Bead *bi, *bl;
	size_t limit_i, limit_l;
	int i, l;
	bool not_success;

	while (solution.size() != 2)
	{
		sl = solution.p_last() - 1;
		limit_l = sl->size();
		not_success = true;
		for (si = solution.p_at(0); not_success && si < sl; ++si)
		{
			limit_i = si->size();
			for (i = 0, bi = si->p_at(0); not_success && i < limit_i; ++i, ++bi)
			{
				for (l = 0, bl = sl->p_at(0); not_success && l < limit_l; ++l, ++bl)
				{
					if (bi->color[0] == bl->color[0])
					{
						combine_necklaces (si, sl, bi, bl);
						solution.pop();
						not_success = false;
					}
				}
			}
		}

		debug_solution ();

		if (not_success)
			return false;
	}

	return true;
}


void Graph::combine_necklaces (Sol *si, Sol *sj, Bead *bi, Bead *bj)
{
	Bead *i, *j, *li, *lj, *aux_ini, *aux_fin;

	li = si->p_last();
	lj = sj->p_last();
	aux_ini = sol_aux.p_at(0);

	sol_aux.clear();
	for (i = li; i >= bi; --i)
	{
		sol_aux.push (*i);
		si->pop();
	}
	for (j = bj; j <= lj; ++j)
		si->push (*j);
	for (j = sj->p_at(0); j < bj; ++j)
		si->push (*j);
	aux_fin = sol_aux.p_last();
	for (i = aux_fin; i >= aux_ini; --i)
		si->push (*i);
}


/***************************************************/


void Graph::solve (int c)
{
	#ifdef DEBUG
	fprintf(stderr, " %d", c);
	#endif
	int self_connections;
	Color *current_color;

	if (total_edges == 0)
		return;

	current_color = color + c;
	self_connections = current_color->edge[c] / 2;
	if (self_connections)
		push_solution (c, c, self_connections);

	for_color (i)
	{
		if (current_color->edge[i])
		{
			push_solution (c, i);
			if (i == solution.last()[0].color[0]) {
				solution.push();
				solution.last().clear();
			}
			solve (i);
			return;
		}
	}
}


/***************************************************/


Graph graph;

int main ()
{
	int T, beads, test_case, ci, cj;
	Bead *solution;
	
	get_int(T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		printf("Case #%d\n", test_case);
		graph.clear();
		
		get_int(beads);
		for (int i = 0; i < beads; ++i)
		{
			scanf ("%d %d", &ci, &cj);
			graph.connect(ci, cj);
		}
		
		if (graph.solve())
		{
			for (solution = graph.solution[0].edge; solution < graph.solution[0].last_edge; ++solution)
				solution->display();
		}
		else
			puts (OUTPUT_LOST);

		if (test_case < T)
			putchar('\n');
	}

	return 0;
}