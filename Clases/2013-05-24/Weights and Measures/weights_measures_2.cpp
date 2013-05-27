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


bool operator < (const Turtle &t1, const Turtle &t2)
{
	return t1.strength < t2.strength || t1.weight > t2.weight;
}


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
	Turtle
		&prev_t = turtle_aux[not_marked],
		&curr_t = turtle_aux[not_marked-1];
	TurtleNode **next_vertex;
	int result, r_aux;

	if (not_marked == 1)
	{
		for (next_vertex = vertex->first; next_vertex < vertex->last; ++next_vertex)
		{
			Turtle &t = *(*next_vertex)->value;
			if (t.marked)
				continue;

			curr_t = prev_t;
			curr_t += t;
			return 1 + curr_t.is_valid();
		}
	}

	result = 0;
	--not_marked;

	for (next_vertex = vertex->first; next_vertex < vertex->last; ++next_vertex)
	{
		Turtle &t = *(*next_vertex)->value;
		if (t.marked)
			continue;

		curr_t = prev_t;
		curr_t += t;
		if (curr_t.is_invalid())
			continue;

		t.marked = true;
		r_aux = max_stack(*next_vertex, not_marked);
		t.marked = false;
		max(result, r_aux);
	}

	return ++result;
}


inline int max_stack ()
{
	TurtleNode *vertex;
	int result, r_aux;
	size_t not_marked = graph_turtles.size() - 1;
	Turtle &t_aux = turtle_aux[not_marked];

	result = 0;
	for (vertex = graph_turtles.first; vertex < graph_turtles.last; ++vertex)
	{
		t_aux = *vertex->value;
		vertex->value->marked = true;
		r_aux = max_stack(vertex, not_marked);
		vertex->value->marked = false;
		max(result,r_aux);
	}

	return result;
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

	printf("%d\n", max_stack());

	return 0;
}