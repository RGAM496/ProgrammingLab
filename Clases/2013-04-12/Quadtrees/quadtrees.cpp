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
#define MAX_DEPTH 6


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
		node.resize(1);
		node[0].value = EMPTY;
	}

	Node * new_child () {
		node.push_back(Node());
		return &(node.back());
	}

	void new_childs (Node * p) {
		p->child[0] = new_child();
		p->child[1] = new_child();
		p->child[2] = new_child();
		p->child[3] = new_child();
	}

	Node * head () {
		return &(node.front());
	}

	Node * child (Node *p, size_t ch) {
		Node *&child = p->child[ch];
		if (child == 0)
			new_childs(p);
		printf(" [%d]", child-head());
		return child;
	}

	int count (Node *p, int total_pixels) {
		printf("%c: [%d] %d\n", p->value, p-head(), total_pixels);
		switch (p->value)
		{
			case FULL: {
				return total_pixels;
			}
			case EMPTY: {
				return 0;
			}
			case PARENT: {
				int r = 0, child_pixels = total_pixels / 2;
				r += count(p->child[0], child_pixels);
				r += count(p->child[1], child_pixels);
				r += count(p->child[2], child_pixels);
				r += count(p->child[3], child_pixels);
				return r;
			}
		}
	}

	int count () {
		return count (head(), SIDE*SIDE);
	}

	Tree () {
		node.reserve(64);
	}
};


int main ()
{
	int total_cases, c, trees_parsed;
	Tree tree;
	Node *node[MAX_DEPTH];
	int numbering[MAX_DEPTH], depth;

	scanf("%d\n", &total_cases);

	while (total_cases)
	{
		tree.reset();

		/* First parse. */
		puts("\n\nFirst parse.");

		depth = 0;
		node[depth] = tree.head();
		numbering[depth] = 0;

		c = getchar();
		printf("\n%c: [%d] %d %d", c, node[depth]-tree.head(), depth, numbering[depth]);
		while (c != '\n')
		{
			node[depth]->value = c;
			++numbering[depth];

			switch (c)
			{
				case PARENT:
				{
					++depth;
					numbering[depth] = 0;
					node[depth] = tree.child(node[depth-1], 0);
					++node[depth-1];
					break;
				}

				case FULL:
				case EMPTY:
				{
					++node[depth];
					if (numbering[depth] >= MAX_CHILDS) {
						--depth;
					}
					break;
				}
			}

			c = getchar();
			printf("\n%c: [%d] %d %d", c, node[depth]-tree.head(), depth, numbering[depth]);
		}

		printf("There are %d black pixels.\n", tree.count());

		/* Second parse. */
		puts("\n\nSecond parse.");

		depth = 0;
		node[depth] = tree.head();
		numbering[depth] = 0;

		c = getchar();
		printf("\n%c: [%d] %d %d", c, node[depth]-tree.head(), depth, numbering[depth]);
		while (c != EOF && c != '\n')
		{
			++numbering[depth];

			switch (c)
			{
				case PARENT:
				{
					switch (node[depth]->value)
					{
						case EMPTY:
						{
							node[depth]->value = c;
						}
						case PARENT:
						{
							++depth;
							numbering[depth] = 0;
							putchar('c');
							node[depth] = tree.child(node[depth-1], 0);
							++node[depth-1];
							putchar('h');
							break;
						}

						case FULL:
						{
							node[depth]->value = c;
							break;
						}
					}
					
					break;
				}

				case FULL:
				{
					node[depth]->value = c;
				}
				case EMPTY:
				{
					++node[depth];
					if (numbering[depth] == MAX_CHILDS) {
						--depth;
					}
					break;
				}
			}

			c = getchar();
			printf("\n%c: [%d] %d %d", c, node[depth]-tree.head(), depth, numbering[depth]);
		}

		puts("\nBP");
		printf("There are %d black pixels.\n", tree.count());
		--total_cases;
	}

	return 0;
}
