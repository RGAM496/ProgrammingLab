#include <iostream>
#include <set>

using namespace std;

#define MAX_N 101

typedef set <int> Vector;
typedef Vector::iterator Iterator;

#define iterate(it,st) for (it = st.begin(); it != st.end(); ++it)

struct Node
{
	Vector parent;
	Vector child;
};


struct Tree
{
	Node node[MAX_N];
	int N;

	inline void reset (int n = MAX_N) {
		N = n;
		for (int i = 1; i <= N; ++i)
			node[i].parent.empty();
	}

	inline void connect (int i, int j) {
		node[j].parent.insert (i);
		node[i].child.insert (j);
	}

	inline void execute_task (int n) {
		Iterator it;
		iterate (it, node[n].child)
		{
			node[*it].parent.erase (n);
		}
	}

	void list_dfs (int n) {
		Iterator it;
		cout << n << ' ';
		iterate (it, node[n].child)
		{
			list_dfs (*it);
		}
	}

	inline void list_tasks ()
	{
		Vector tasks;
		Iterator it;
		for (int i = 1; i <= N; ++i)
		{
			tasks.insert (i);
		}

		while (!tasks.empty())
		{
			iterate (it, tasks)
			{
				if (node[*it].parent.empty())
				{
					cout << *it << ' ';
					execute_task (*it);
					tasks.erase (it);
					break;
				}
			}
		}
	}
};

Tree tree;


int main ()
{
	int m, n, i, j;

	while (cin >> n >> m, m != 0 || n != 0)
	{
		tree.reset (n);
		while (m--)
		{
			cin >> i >> j;
			tree.connect (i, j);
		}

		

		tree.list_tasks ();
		cout << endl;
	}

	return 0;
}