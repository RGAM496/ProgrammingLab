#include <cstdio>

#define MAX_TURTLES 5607


/*********************************************************************/


template <typename N>
inline void min (N &d, const N &s)
{
	if (d > s)
		d = s;
}

template <typename N>
inline void max (N &d, const N &s)
{
	if (d < s)
		d = s;
}


/*********************************************************************/


template <class v_type, size_t MAX_EDGES>
struct Node
{
	v_type
		value;
	Node
		*first[MAX_EDGES],
		**last;

	inline void clear () {last = first;}

	inline void push (Node *n) {*last = n; ++last;}

	inline Node * edge (size_t n) {return first[n];}
	inline Node * operator [] (size_t n) {return first[n];}
};


/*********************************************************************/


template <class v_type, size_t SIZE>
struct Graph
{
	typedef Node <v_type, SIZE-1> GraphNode;

	GraphNode first[SIZE], *last;

	inline void clear () {last = first;}
	inline size_t size () {return last - first;}

	inline void push (const v_type &v) {last->clear(); last->value = v; ++last;}
	inline void push () {last->clear(); ++last;}

	inline v_type & vertex (size_t n) {return first[n].value;}
	inline GraphNode & operator [] (size_t n) {return first[n];}

	inline void connect (size_t vs, size_t vd) {first[vs].push(first+vd);}
	inline void connect (GraphNode *s, GraphNode *d) {s->push(d);}
};


/*********************************************************************/


struct Turtle
{
	int weight;
	int strength;
	int marked;

	inline void operator = (const Turtle &t) {
		weight = t.weight;
		strength = t.strength;
	}

	inline void operator += (const Turtle &t) {
		weight += t.weight;
		strength -= t.weight;
		if (strength > t.strength)
			strength = t.strength;
	}

	inline bool is_valid () {
		return strength >= 0;
	}

	inline bool is_invalid () {
		return strength < 0;
	}
};


/*********************************************************************/

typedef Graph <Turtle *, MAX_TURTLES> GraphTurtles;
typedef GraphTurtles::GraphNode TurtleNode;

Turtle turtle[MAX_TURTLES], turtle_aux[MAX_TURTLES];
GraphTurtles graph_turtles;


inline void init ()
{
	graph_turtles.clear();
	for (int i = 0; i < MAX_TURTLES; ++i)
		graph_turtles.push(turtle + i);
}


int max_stack (TurtleNode *vertex, size_t not_marked)
{
	return 0;
}


inline int max_stack ()
{
	TurtleNode *vertex;
	int result, r_aux;
	size_t not_marked;

	not_marked = graph_turtles.size() - 1;
	result = 0;
	for (vertex = graph_turtles.first; vertex < graph_turtles.last; ++vertex)
	{
		vertex->value->marked = true;
		r_aux = max_stack(vertex, not_marked);
		min(result,r_aux);
		vertex->value->marked = false;
	}

	return 0;
}


/*********************************************************************/


int main ()
{
	Turtle *t = turtle;
	TurtleNode
		*n_aux[2],
		*&node = n_aux[0],
		*&last_node = n_aux[1] = graph_turtles.first;

	init();

	graph_turtles.clear();
	while (scanf("%d %d", &t->weight, &t->strength) == 2)
	{
		graph_turtles.push();
		t->strength -= t->weight;
		t->marked = false;
		++t;
		for (node = graph_turtles.first; node < last_node; ++node)
		{;
			Turtle t_aux[2];
			int selected;
			t_aux[0] = *node->value; t_aux[0] += *last_node->value;
			t_aux[1] = *last_node->value; t_aux[1] += *node->value;
			selected = t_aux[0].strength > t_aux[1].strength ? 0 : 1;
			if (t_aux[selected].is_valid())
				graph_turtles.connect(n_aux[selected], n_aux[selected^1]);
		}
		++last_node;
	}

	return 0;
}