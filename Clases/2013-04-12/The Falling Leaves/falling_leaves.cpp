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

	node<E> * go_head () {return v;}
	node<E> * go_most_left () {return most_left;}
	node<E> * go_most_right () {return most_right;}

	node<E> * go_left (node<E> *p) {
		if (p == most_left)
			new_left();
		return p->left;
	}

	node<E> * go_right (node<E> *p) {
		if (p == most_right)
			new_right();
		return p->right;
	}

	void print () {
		for (node<E> *p = most_left; p != most_right; p = p->right) {
			printf("%d ", p->value);
		}
		putchar('\n');
		putchar('\n');
	}
};


inline int get_int (int &n)
{
	return scanf("%d", &n);
}


int main ()
{
	vector<int,80> v;
	int n = EMPTY, test_case = 1;

	get_int(n);
	while (n != EMPTY)
	{
		v.reset();

		/* Do stuff */

		printf("Case %d:\n", test_case);
		v.print();

		get_int(n);
		++test_case;
	}

	return 0;
}