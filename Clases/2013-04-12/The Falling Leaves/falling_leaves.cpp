#include <cstdio>
#include <vector>


#define MAX_NODES 80
#define EMPTY -1


template <typename E>
struct node
{
	E value;

	node<E>
		*left,
		*right;
};


template <typename E, int N>
class vector
{
	node<E>
		v[N],
		*last_used,
		*most_left,
		*most_right;

public:

	void reset () {
		last_used = most_left = most_right = v;
		last_used->value = E();
		last_used->left = 0;
		last_used->right = 0;
	}

	void new_node () {
		++last_used;
		last_used->value = E();
	}

	void new_left () {
		new_node();
		last_used->left = 0;
		last_used->right = most_left;
		most_left->left = last_used;
		most_left = last_used;
	}

	void new_right () {
		new_node();
		last_used->right = 0;
		last_used->left = most_right;
		most_right->right = last_used;
		most_right = last_used;
	}

	inline node<E> * go_head () {return v;}
	inline node<E> * go_most_left () {return most_left;}
	inline node<E> * go_most_right () {return most_right;}

	inline node<E> * go_left (node<E> *p) {
		if (p == most_left)
			new_left();
		return p->left;
	}

	inline node<E> * go_right (node<E> *p) {
		if (p == most_right)
			new_right();
		return p->right;
	}

	void print () {
		for (node<E> *p = most_left; p; p = p->right) {
			printf("%d ", p->value);
		}
		putchar('\n');
	}
};


inline int get_int (int &n)
{
	return scanf("%d", &n);
}


vector<int,80> tree;
int n = EMPTY;


template <typename E>
void parse (node<E> *p)
{
	p->value += n;

	get_int(n);
	if (n != EMPTY)
		parse(tree.go_left(p));

	get_int(n);
	if (n != EMPTY)
		parse(tree.go_right(p));
}


int main ()
{
	int test_case = 1;
	node<int> *head;

	get_int(n);
	while (n != EMPTY)
	{
		tree.reset();

		head = tree.go_head();
		parse(head);

		printf("\nCase %d:\n", test_case);
		tree.print();

		get_int(n);
		++test_case;
	}

	return 0;
}