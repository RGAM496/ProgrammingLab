#include <cstdio>

#define MAX_TURTLES 5607

struct Turtle
{
	int weight;
	int strength;
	bool marked;

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


/**************************************************************/


Turtle
	turtle[MAX_TURTLES],
	t_aux[MAX_TURTLES],
	*last_turtle;


int max_stack (int not_marked)
{
	Turtle
		&t = t_aux[not_marked],
		&prev_t = t_aux[not_marked+1],
		*pt;
	int result, stack;

	if (not_marked == 0)
	{
		for (pt = turtle; pt < last_turtle; ++pt)
		{
			if (pt->marked)
				continue;

			t = prev_t;
			t += *pt;
			//fprintf(stderr, "%*c%4d %4d      (!)", 2*(last_turtle-turtle-1-not_marked), ' ', pt->weight, pt->strength);
			//fprintf(stderr, "  %c\n", t.is_valid() ? 'V' : 'i');
			return 1 + t.is_valid();
		}
	}

	result = 0;
	--not_marked;

	for (pt = turtle; pt < last_turtle; ++pt)
	{
		if (pt->marked)
			continue;

		t = prev_t;
		t += *pt;
		//fprintf(stderr, "%*c%4d %4d%*c(%d)", 2*(last_turtle-turtle-2-not_marked), ' ', pt->weight, pt->strength, 2*(not_marked+2), ' ', not_marked+1);
		//fprintf(stderr, "  %c %d\n", t.is_valid() ? 'V' : 'i', result);
		if (t.is_invalid())
			continue;
		pt->marked = true;
		stack = max_stack(not_marked);
		pt->marked = false;
		if (result < stack)
		{
			result = stack;
			if (result > not_marked)
				return ++result;
		}
	}

	return ++result;
}


inline int max_stack (Turtle *last)
{
	int not_marked, result, stack;

	last_turtle = last;
	not_marked = last_turtle - turtle - 1;

	Turtle &t = t_aux[not_marked];
	--not_marked;
	result = 0;

	for (last = turtle; last < last_turtle; ++last)
	{
		//fprintf(stderr, "%d %d\n", last->weight, last->strength);
		t = *last;
		last->marked = true;
		stack = max_stack(not_marked);
		last->marked = false;
		if (result < stack)
			result = stack;

	}

	return result;
}


/**************************************************************/


int main ()
{
	Turtle *t = turtle;

	while (scanf("%d %d", &t->weight, &t->strength) == 2)
	{
		t->strength -= t->weight;
		t->marked = false;
		++t;
	}
	printf("%d\n", max_stack(t));

	return 0;
}
