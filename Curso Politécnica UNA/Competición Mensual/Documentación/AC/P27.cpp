#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 10001

#define for_edge(i,l) for (int i = 1; i < l; ++i)

typedef vector <int> Children;


struct Node
{
	Children child;

	inline void add_child (int c) {
		child.push_back (c);
	}
};


struct Graph
{
	Node node[MAX_N];
	bool marked[MAX_N];

	inline int connect (int i, int j) {
		node[i].add_child (j);
		node[j].add_child (i);
	}

	int longest_path (int n)
	{
		int c, s, max, l;
		Children &ch = node[n].child;

		max = -1;
		marked[n] = true;
		s = ch.size();
		for (int i = 0; i < s; ++i)
		{
			c = ch[i];
			if (marked[c])
				continue;
			l = longest_path (c);
			if (max < l)
				max = l;
		}
		marked[n] = false;
		return max + 1;
	}

	int longest_bipath (int n)
	{
		int c, s, max[2], l;
		Children &ch = node[n].child;

		max[0] = max[1] = -1;
		marked[n] = true;
		s = ch.size();
		for (int i = 0; i < s; ++i)
		{
			c = ch[i];
			if (marked[c])
				continue;
			l = longest_path (c);
			if (max[0] < l) {
				max[1] = max[0];
				max[0] = l;
			}
			else if (max[1] < l) {
				max[1] = l;
			}
		}
		return max[0] + max[1] + 2;
	}

	int dfs (int n, int &z)
	{
		int c, s, max, l, aux;
		Children &ch = node[n].child;

		max = -1;
		marked[n] = true;
		s = ch.size();
		for (int i = 0; i < s; ++i)
		{
			c = ch[i];
			if (marked[c])
				continue;
			l = dfs (c, aux);
			if (max < l)
			{
				max = l;
				z = aux;
			}
		}
		if (max == -1)
			z = n;
		marked[n] = false;
		return max + 1;
	}
};


Graph graph;


int main ()
{
	int n, u, v;

	cin >> n;
	if (n == 1)
		cout << 0;
	else
	{
		while (--n > 0)
		{
			cin >> u >> v;
			graph.connect (u, v);
		}

		graph.dfs (u, v);

		cout << graph.dfs (v, u);
	}
	cout << endl;

	return 0;
}