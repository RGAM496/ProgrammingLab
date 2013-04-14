#include <cstdio>
#include <cctype>
#include <vector>

using namespace std;


inline int get_char (int &c)
{
	return scanf(" %c", &c);
}

inline int get_int (int &n)
{
	return scanf("%d", &n);
}

/* Returns false if is an empty tree.
   Otherwise, returns true and sets it's value to n. */
inline bool next_tree (int &n)
{
	static int c;
	get_char(c); // c == '('
	if (get_int(n))
		return true;
	get_char(c); // c == ')'
	return false;
}


std::vector<int> tree_sum(20);
int depth, compare;


bool parse_subtree()
{
	static int n;
	bool is_a_leaf;

	is_a_leaf = true;

	if (next_tree(n)) {
		is_a_leaf = false;
		n += tree_sum[depth];
		++depth;
		tree_sum[depth] = n;
		if (parse_subtree())
			return true;
		--depth;
	}

	if (next_tree(n)) {
		is_a_leaf = false;
		n += tree_sum[depth];
		++depth;
		tree_sum[depth] = n;
		if (parse_subtree())
			return true;
		--depth;
	}

	get_char(n);

	if (is_a_leaf) {
		return compare == tree_sum[depth];
	}

	return false;
}


inline void go_to_next_test()
{
	static int c;
	while (depth) {
		get_char(c);
		switch (c) {
			case '(':
				++depth;
				break;
			case ')':
				--depth;
				break;
		}
	}
}


int main ()
{
	int n;

	while (get_int(compare) > 0)
	{
		if (next_tree(tree_sum[0]))
		{
			depth = 0;
			if (parse_subtree()){
				puts("yes");
				go_to_next_test();
			}
			else {
				puts("no");
			}
		}
		else
		{
			puts("no");
			continue;
		}
	}

	return 0;
}