#include <cstdio>
#include <vector>

using namespace std;


#define PARENT 'p'
#define FULL 'f'
#define EMPTY 'e'
#define BLACK 1
#define WHITE 0
#define SIDE 32
#define MAX_CHILDS 4


struct Node
{
	int value;
	Node *child[MAX_CHILDS];

	Node () {
		child[0] = 0;
		child[1] = 0;
		child[2] = 0;
		child[3] = 0;
	}
};


class Tree
{
	vector<Node> node;

public:

	void reset() {
		node[0].value = EMPTY;
	}

	Node * new_child () {
		node.push_back(Node());
		return &(node.back());
	}

	Node * head () {
		return &(node.front());
	}

	Node * child (Node *p, size_t ch) {
		Node *&child = p->child[ch];
		if (child == 0)
			child = new_child();
		return child;
	}

	Tree () {
		node.reserve(64);
		node.resize(1);
	}
};


int main ()
{
	#define MAX_DEPTH 5
	int total_cases, c, trees_parsed;
	Tree tree;
	Node *node[MAX_DEPTH];
	int numbering[MAX_DEPTH], depth;

	scanf("%d\n", &total_cases);

	while (total_cases)
	{
		tree.reset();

		/* First parse. */

		depth = 0;
		node[depth] = tree.head();
		numbering[depth] = 0;

		c = getchar();
		while (c != '\n')
		{
			node[depth]->value = c;
			switch (c)
			{
				case PARENT:
				{
					++depth;
					numbering[depth] = 0;
					node[depth] = tree.child(node[depth-1], 0);
					break;
				}

				case FULL:
				case EMPTY:
				{
					++node[depth];
					++numbering[depth];
					if (numbering[depth] == MAX_CHILDS) {
						--depth;
					}
					break;
				}
			}

			c = getchar();
		}

		/* Second parse. */

		depth = 0;
		node[depth] = tree.head();
		numbering[depth] = 0;

		c = getchar();
		while (c != EOF && c != '\n')
		{
			node[depth]->value = c;
			switch (c)
			{
				case PARENT:
				{
					++depth;
					numbering[depth] = 0;
					node[depth] = tree.child(node[depth-1], 0);
					break;
				}

				case FULL:
				case EMPTY:
				{
					++node[depth];
					++numbering[depth];
					if (numbering[depth] == MAX_CHILDS) {
						--depth;
					}
					break;
				}
			}

			c = getchar();
		}
	}

	return 0;
}
