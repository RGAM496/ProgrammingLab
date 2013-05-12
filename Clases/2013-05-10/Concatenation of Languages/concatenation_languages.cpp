#include <cstdio>
#include <cstring>


#define MAX_MN 1500
#define MAX_TREE_NODES (1000000)
#define MAX_LOWERCASE ('z' - 'a' + 1)
#define MAX_LENGTH_STRING 12

#define loop(i,n) for (int i = 0; i < n; ++i)


inline int fgets (char *s)
{
	int len;
	fgets (s, MAX_LENGTH_STRING, stdin);
	len = strlen(s);
	s[len-1] = '\0';
}


template <class Vtype, size_t CHILDS>
struct Node
{
	Node *child[CHILDS];
	bool is_leaf;

	inline void clear () {
		loop (i, CHILDS)
			child[i] = 0;
		is_leaf = false;
	}

	Node *& at_child (const char c) {return child[c - 'a'];}
	inline Node *& operator [] (const char c) {return at_child(c);}
};


template <class Vtype, size_t MAX_SIZE>
struct Stack
{
	Vtype first[MAX_SIZE], *last;

	inline void clear () {last = first;}
	inline void push (Vtype &v) {*last = v; ++last;}
	inline void pop () {--last;}
	inline size_t size () {return last - first;}
	inline Vtype & at (size_t n) {return first[n];}
	inline Vtype & operator [] (size_t n) {return at(n);}
};


struct Tree
{
	typedef Node <char, MAX_LOWERCASE> Cnode;

	Cnode node[MAX_TREE_NODES], *last;
	Stack <Cnode *, MAX_MN> prefix;

	inline void clear () {
		last = node;
		last->clear();
		prefix.clear();
	}

	Cnode * new_node () {
		++last;
		last->clear();
		return last;
	}

	Cnode * child (Cnode *n, const char c) {
		Cnode *&cn = n->at_child(c);
		if (cn == 0)
			cn = new_node();
		return cn;
	}

	void add_prefix (const char *c) {
		Cnode *current_node = node;
		for (; *c; ++c) {
			current_node = child(current_node, *c);
		}
		prefix.push(current_node);
	}

	bool concatenate (Cnode *current_node, const char *c) {
		for (; *c; ++c) {
			current_node = child(current_node, *c);
		}
		if (current_node->is_leaf)
			return false;
		else {
			current_node->is_leaf = true;
			return true;
		}
	}

	int operator [] (const char *c) {
		Cnode *current_node;
		int prefix_size, new_strings;
		new_strings = 0;
		prefix_size = prefix.size();
		loop (i, prefix_size) {
			current_node = prefix[i];
			new_strings += concatenate (current_node, c);
		}
		return new_strings;
	}

	void debug () {
		loop (i, prefix.size())
			fprintf(stderr, " %2d", prefix[i] - node);
		fprintf(stderr, "\n\n");
		for (Cnode *n = node; n <= last; ++n) {
			fprintf(stderr, "%2d: [%c]\n", n - node, n->is_leaf ? 'T' : 'F');
			loop (i, MAX_LOWERCASE) {
				if (n->child[i])
					fprintf(stderr, " %2d", n->child[i] - node);
				else
					fprintf(stderr, "  .");
			}
			fprintf(stderr, "\n");
		}
	}
};


Tree tree;


int main ()
{
	int t, test_cases, m, n;
	char s[MAX_LENGTH_STRING];
	int total_strings;

	scanf ("%d", &test_cases);
	for (t = 1; t <= test_cases; ++t)
	{
		tree.clear();
		total_strings = 0;
		scanf ("%d %d%*c", &m, &n);
		loop (i, m) {
			fgets(s);
			tree.add_prefix(s);
		}
		loop (i, n) {
			fgets(s);
			total_strings += tree[s];
		}
		printf("Case %d: %d\n", t, total_strings);
	}

	return 0;
}