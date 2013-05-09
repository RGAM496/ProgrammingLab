#include <cstdio>


#define MAX_BEADS 1000
#define MAX_COLORS 51

#define OUTPUT_LOST "some beads may be lost\n"

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

	inline vtype & last () {return last_edge[-1];}

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

typedef Node <Bead, MAX_BEADS> Solution;


/***************************************************/


struct Graph
{
	Color color[MAX_COLORS];
	Solution solution;
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
	bool solve (int c);

	inline void push_solution (int i, int j, int t = 1) {
		Bead b;
		b.set (i, j, t);
		solution.push (b);
		disconnect (b);
	}

	inline void pop_solution () {
		Bead b;
		b = solution.last();
		solution.pop();
		connect (b);
	}
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
	return solve (first_color);
}


/***************************************************/


bool Graph::solve (int c)
{
	int self_connections;
	Color *current_color;

	if (total_edges == 0)
		return c == solution[0].color[0];

	current_color = color + c;
	self_connections = current_color->edge[c] / 2;
	if (self_connections)
		push_solution (c, c, self_connections);

	for_color (i)
	{
		if (current_color->edge[i])
		{
			push_solution (c, i);
			if (solve (i))
				return true;
			else
				pop_solution ();
		}
	}

	if (self_connections)
		pop_solution ();
	return false;
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
			for (solution = graph.solution.edge; solution < graph.solution.last_edge; ++solution)
				solution->display();
		}
		else
			puts (OUTPUT_LOST);
	}

	return 0;
}