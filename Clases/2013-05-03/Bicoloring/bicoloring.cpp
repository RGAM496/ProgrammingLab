#include <cstdio>
#include <queue>

using namespace std;

#define MAX_NODES 200


int get_int (int &n)
{
	return scanf("%d", &n);
}


/*enum Color
{
	UNCOLORED = -1,
	BLACK,
	WHITE
};*/
#define UNCOLORED -1
#define BLACK 0
#define WHITE 1
typedef int Color;


struct Node
{
	Color color;
	Node *edge[MAX_NODES], **last_edge;
	
	void clear () {
		color = UNCOLORED;
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
	Node node[MAX_NODES];
	int total_nodes;
	queue<Node*> q;
	
	Node & operator [] (int n) {return node[n];}
	
	void reset (int n) {
		total_nodes = n;
		for (int i = 0; i < total_nodes; ++i)
			node[i].clear();
	}
	
	void connect (int i, int j) {
		node[i].push (node + j);
		node[j].push (node + i);
	}
	
	bool bicolorable ();

	inline bool is_bicolorable () {
		node[0].color = BLACK;
		q.push(node);
		return bicolorable ();
	}
};


bool Graph::bicolorable ()
{
	Node **edge, *e, *pn;
	
	while (!q.empty())
	{
		pn = q.front(); q.pop();
		for (edge = pn->edge; *edge; ++edge)
		{
			e = *edge;
			if (e->color == UNCOLORED) {
				e->color = pn->color ^ 1;
				q.push (e);
			}
			else if (e->color == pn->color)
				return false;
		}
	}
	
	return true;
}


Graph graph;

int main ()
{
	int nodes, edges, ni, nj, i;
	
	get_int (nodes);
	while (nodes)
	{
		graph.reset (nodes);

		get_int (edges);
		for (i = 0; i < edges; ++i)
		{
			scanf ("%d %d", &ni, &nj);
			graph.connect(ni, nj);
		}
	
		puts (graph.is_bicolorable() ? "BICOLORABLE." : "NOT BICOLORABLE.");
		get_int (nodes);
	}

	return 0;
}
