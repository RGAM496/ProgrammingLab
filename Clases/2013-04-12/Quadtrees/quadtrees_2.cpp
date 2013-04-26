#include <cstdio>
#include <cctype>
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
	int child[MAX_CHILDS];

	Node () {
		child[0] = -1;
		child[1] = -1;
		child[2] = -1;
		child[3] = -1;
	}
};


class Tree
{
	vector<Node> node;

public:

	void reset() {
		node.resize(0);
		node.push_back(Node());
		node[0].value = EMPTY;
	}

	int new_child () {
		node.push_back(Node());
		return node.size() - 1;
	}

	void new_childs (int p) {
		node[p].child[0] = new_child();
		node[p].child[1] = new_child();
		node[p].child[2] = new_child();
		node[p].child[3] = new_child();
	}

	int child (int p, size_t ch) {
		int &child = node[p].child[ch];
		if (child == -1)
			new_childs(p);
		return child;
	}

	Node * head () {
		return &(node.front());
	}

	int count (int p, int total_pixels) {
		switch (node[p].value)
		{
			case FULL: {
				return total_pixels;
			}
			case EMPTY: {
				return 0;
			}
			case PARENT: {
				int r = 0, child_pixels = total_pixels / MAX_CHILDS;
				r += count(node[p].child[0], child_pixels);
				r += count(node[p].child[1], child_pixels);
				r += count(node[p].child[2], child_pixels);
				r += count(node[p].child[3], child_pixels);
				return r;
			}
		}
	}

	int count () {
		return count (0, SIDE*SIDE);
	}

	Node & operator [] (size_t i) {
		return node[i];
	}

	Tree () {
		node.reserve(64);
	}
};


Tree tree;


void ignore_parsing ()
{
	static int c;
	for (int i = 0; i < MAX_CHILDS; ++i) {
		c = getchar();
		if (c == PARENT)
			ignore_parsing();
	}
}


void first_parse (int index)
{
	static int c;
	Node &node = tree[index];

	c = getchar();
	node.value = c;
	switch (c)
	{
		case PARENT:
		{
			tree.new_childs(index);
			first_parse(node.child[0]);
			first_parse(node.child[1]);
			first_parse(node.child[2]);
			first_parse(node.child[3]);
			break;
		}
	}
}


void second_parse (int index)
{
	static int c;
	Node &node = tree[index];

	c = getchar();
	switch (c)
	{
		case PARENT:
		{
			switch (node.value)
			{
				case EMPTY:
				{
					node.value = c;
					tree.new_childs(index);
					tree[node.child[0]].value = EMPTY;
					tree[node.child[1]].value = EMPTY;
					tree[node.child[2]].value = EMPTY;
					tree[node.child[3]].value = EMPTY;
				}
				case PARENT:
				{
					second_parse(node.child[0]);
					second_parse(node.child[1]);
					second_parse(node.child[2]);
					second_parse(node.child[3]);
					break;
				}

				case FULL:
				{
					ignore_parsing();
					break;
				}
			}
			
			break;
		}

		case FULL:
		{
			node.value = c;
		}
		case EMPTY:
		{
		}
	}
}


int main ()
{
	int total_cases;

	scanf("%d\n", &total_cases);

	while (total_cases)
	{
		tree.reset();

		first_parse(0);
		getchar();

		second_parse(0);
		getchar();

		printf("There are %d black pixels.\n", tree.count());
		--total_cases;
	}

	return 0;
}