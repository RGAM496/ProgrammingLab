#include <cstdio>


#define MAX_BEADS 1000
#define MAX_COLORS 51

#define OUTPUT_LOST "some beads may be lost\n"


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

	inline vtype & last () {return last_edge[-1];}

	inline size_t size () {return last_edge - edge;}
};


/***************************************************/


struct Color;
struct Bead;


struct Bead : public Node <Color *, 2>
{
	bool in_solution;

	inline void clear () {
		Node::clear();
		in_solution = false;
	}
};


struct Color
{
	int color;
	Node <Bead *, MAX_BEADS>
		one_color_bead,
		two_colors_bead;

	inline void clear () {
		one_color_bead.clear();
		two_colors_bead.clear();
	}
};


/***************************************************/


struct Pair
{
	Bead *bead;
	bool reverse;

	inline int color (size_t n) {
		return bead->edge[n ^ reverse]->color;
	}

	inline void set (Bead *bead, bool reverse) {
		this->bead = bead;
		this->reverse = reverse;
	}

	inline void print() {printf("%d %d\n", color(0), color(1));}
};

struct Solution : public Node <Pair, MAX_BEADS> {};


/***************************************************/


struct Graph
{
	Color color[MAX_COLORS];
	Node <Bead, MAX_BEADS> bead;
	Solution solution;
	int beads_left;

	Graph () {
		for (int i = 1; i < MAX_COLORS; ++i)
			color[i].color = i;
	}

	inline void clear () {
		bead.clear();
		for (int i = 1; i < MAX_COLORS; ++i)
			color[i].clear();
	}

	inline void connect (int i, int j) {
		Color *ci, *cj;
		Bead *b;

		ci = color + i;
		cj = color + j;

		b = &bead.push();
		b->clear();
		b->push(ci);
		b->push(cj);

		if (i == j)
		{
			ci->one_color_bead.push(b);
		}
		else
		{
			ci->two_colors_bead.push(b);
			cj->two_colors_bead.push(b);
		}
	}

	inline bool solve ();
	bool solve (int c);

	inline void push_solution (Pair &p) {
		solution.push(p);
		p.bead->in_solution = true;
		--beads_left;
	}

	inline void pop_solution () {
		Pair p;
		p = solution.last();
		solution.pop();
		p.bead->in_solution = false;
		++beads_left;
	}
};


bool Graph::solve ()
{
	int i;

	for (i = 1; i < MAX_COLORS; ++i)
	{
		int s1 = color[i].one_color_bead.size();
		int s2 = color[i].two_colors_bead.size();
		if (s2 % 2 || (s2 == 0 && s1 > 0))
			return false;
	}

	solution.clear();
	beads_left = bead.size();

	// Search first color in use.
	for (i = 1; color[i].two_colors_bead.size() == 0; ++i);

	return solve (i);
}


bool Graph::solve (int c)
{
	Color *pcolor;
	Bead **pbead;
	Pair p;
	bool one_color_beads_in_solution;

	if (beads_left == 0)
		return c == solution.edge[0].color(0);

	pcolor = color + c;
	if (pcolor->one_color_bead.size())
	{
		one_color_beads_in_solution = pcolor->one_color_bead.edge[0]->in_solution;
		if (one_color_beads_in_solution == false)
		{
			p.reverse = false;
			for (pbead = pcolor->one_color_bead.edge; pbead < pcolor->one_color_bead.last_edge; ++pbead)
			{
				p.bead = *pbead;
				push_solution (p);
			}
		}
	}
	else
	{
		one_color_beads_in_solution = true;
	}

	for (pbead = pcolor->two_colors_bead.edge; pbead < pcolor->two_colors_bead.last_edge; ++pbead)
	{
		p.bead = *pbead;
		if (p.bead->in_solution == false)
		{
			p.reverse = (c != p.bead->edge[0]->color);
			push_solution (p);
			if (solve (p.color(1)))
				return true;
			else
				pop_solution ();
		}
	}

	// No solutions found.
	if (one_color_beads_in_solution == false)
	{
		p.reverse = false;
		for (pbead = pcolor->one_color_bead.edge; pbead < pcolor->one_color_bead.last_edge; ++pbead)
		{
			pop_solution ();
		}
	}
	return false;
}


/***************************************************/


Graph graph;

int main ()
{
	int T, beads, test_case, ci, cj;
	Pair *solution;
	
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
				solution->print();
		}
		else
			puts (OUTPUT_LOST);
	}

	return 0;
}