#include <cstdio>


typedef
struct binary_tree
{
	struct binary_tree
		*path[2];	// Representing both 0's and 1's.
}
binary_tree;


#define MAX_TREE_NODES 80 // Upper bound for up to 8 codes of maximun 10 bits each one.

struct binary_tree
	tree_node[MAX_TREE_NODES] = {0},
	*p_tree_node_iterator = tree_node,
	*p_last_tree_node = tree_node;


inline void RESET_LAST_NODE()
{
	p_last_tree_node->path[0] = 0;
	p_last_tree_node->path[1] = 0;
}


inline void RESET_TREE_NODES()
{
	p_last_tree_node = tree_node;
	RESET_LAST_NODE();
}


inline void INSERT_TREE_NODE(struct binary_tree *&path)
{
	path = p_last_tree_node;
	++p_last_tree_node;
	RESET_LAST_NODE();
}

inline void GO(unsigned int dir)
{
	struct binary_tree *&destination = p_tree_node_iterator->path[dir];
	if (!destination)
		INSERT_TREE_NODE(destination);
	p_tree_node_iterator = destination;
}

inline void NEW_CODE()
{
	p_tree_node_iterator = tree_node;
}

inline void NEW_GROUP()
{
	NEW_CODE();
	RESET_TREE_NODES();
}

inline bool PATH_CONTINUES()
{
	return (p_tree_node_iterator->path[0] || p_tree_node_iterator->path[1]);
}


// Output templates.
const char *output[] = {
	"Set %d is not immediately decodable",
	"Set %d is immediately decodable"
};



/* Everything starts here. :) */
int main ()
{
	int c, set = 1;
	bool is_immediate_decodable = true;

	while (c = getc(stdin))
	{
		// End of group.
		if (c == '9')
		{
			fprintf(stdout, output[is_immediate_decodable], set);
			NEW_GROUP();
			is_immediate_decodable = true;
			++set;
			break;
		}
		else if (is_immediate_decodable)
		{
			switch (c)
			{
				// End of code.
				case '\n':
				case ' ':
				case '\t':
				{
					// Checking if is immediate decodable.
					if (PATH_CONTINUES()) {
						is_immediate_decodable = false;
						continue;
					}
					// A new group takes place.
					NEW_CODE();
					break;
				}

				// 0 or 1.
				default:
				{
					c -= '0';
					GO(c);
				}
			}
		}
	}

	return 0;
}
