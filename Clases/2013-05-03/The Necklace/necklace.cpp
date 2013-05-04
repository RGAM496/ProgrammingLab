#include <cstdio>

#define MAX_BEADS 1000
#define MAX_COLORS 51

#define OUTPUT_LOST "some beads may be lost\n"


int get_int (int &n)
{
	return scanf("%d", &n);
}

struct Bead
{
	int c1, c2; // Colors.
};


struct Node
{
	Node *edge[MAX_BEADS], **last_edge;
	
	void clear () {
		last_edge = edge;
		*last_edge = 0;
	}
	
	void push (Node *pn) {
		*last_edge = pn;
		++last_edge;
		*last_edge = 0;
	}
	
	int size () {return last_edge - edge;}
};


struct Graph
{
	Node color[MAX_COLORS];
	// Estructura solution.
	
	Node & operator [] (int n) {return color[n];}
	
	void reset () {
		for (int i = 0; i < MAX_COLORS; ++i)
			color[i].clear();
	}
	
	void connect (int i, int j) {
		if (i != j) {
			color[i].push (color + j);
			color[j].push (color + i);
		}
	}
	
	bool solve ()
	{
		for (int i = 1; i < MAX_COLORS; ++i)
		{
			if (color[i].size() % 2)
				return false;
		}
		return true;
	}
};


Graph graph;

int main ()
{
	int T, beads, test_case, ci, cj;
	
	get_int(T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		printf("Case #%d\n", test_case);
		graph.reset();
		
		get_int(beads);
		for (int i = 0; i < beads; ++i)
		{
			scanf ("%d %d", &ci, &cj);
			graph.connect(ci, cj);
		}
		
		puts (graph.solve() ? "is solvable\n" : OUTPUT_LOST);
	}

	return 0;
}