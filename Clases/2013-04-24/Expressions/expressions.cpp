#include <cstdio>
#include <cctype>

#define MAX_LENGTH 10000


inline bool is_operator (int c) {return isupper(c);}
inline bool is_number (int c) {return islower(c);}


/************************************************/


template <class E>
struct Node
{
	E value;
	Node<E> *left, *right;
};


template <class E>
struct Stack
{
	E v[MAX_LENGTH];
	E *front, *rear;

	inline void reset () {rear = front;}

	inline bool is_empty () {return front == rear;}

	inline void push (E c) {*++rear = c;}
	inline E pop () {return *rear--;}

	Stack () {front = v - 1;}
};


template <class E>
struct Tree
{
	Node<E> v[MAX_LENGTH];
	Node<E> *last;

	inline void reset () {last = v - 1;}
	inline int size () {return last - v + 1;}

	inline Node<E> * create (E &value, Node<E> *left = 0, Node<E> *right = 0) {
		++last;
		last->left = left;
		last->right = right;
		last->value = value;
		return last;
	}
};


/************************************************/


int main ()
{
	int test_cases, c;
	Stack<Node<int>*> stack;
	Tree<int> tree;
	Node<int> *a, *b;

	scanf("%d ", &test_cases);

	while (test_cases)
	{
		stack.reset();
		tree.reset();
		c = getchar();
		while (!isspace(c) && c != EOF)
		{
			if (is_number(c))
			{
				stack.push(tree.create(c));
			}
			else
			{
				a = stack.pop();
				b = stack.pop();
				stack.push(tree.create(c, b, a));
			}

			c = getchar();
		}

		c = tree.size();
		for (int i = 0; i < c; ++i)
		{
			a = stack.v[i];
			if (is_operator(a->value))
			{
				stack.push(a->left);
				stack.push(a->right);
			}
		}

		while (c--)
		{
			a = stack.v[c];
			putchar(a->value);
		}
		putchar('\n');

		--test_cases;
	}

	return 0;
}