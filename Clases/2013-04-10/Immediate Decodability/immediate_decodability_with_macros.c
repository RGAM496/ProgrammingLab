#include <stdio.h>

#define bool int
#define false 0
#define true 1


typedef
struct binary_tree {
	struct binary_tree
		*path[2];	/* Representing both 0's and 1's. */
	bool
		is_final;	/* It's a final node for a code. */
} binary_tree;


#define MAX_TREE_NODES 80 /* Upper bound for up to 8 codes of maximun 10 bits each one. */


#define CLEAN_LAST_NODE() \
{ \
	p_last_tree_node->path[0] = 0; \
	p_last_tree_node->path[1] = 0; \
	p_last_tree_node->is_final = false; \
}


#define RESET_TREE_NODES() \
{ \
	p_last_tree_node = tree_node; \
	CLEAN_LAST_NODE(); \
}


#define INSERT_TREE_NODE(path) \
{ \
	++p_last_tree_node; \
	CLEAN_LAST_NODE(); \
	path = p_last_tree_node; \
}

#define GO(dir) \
{ \
	struct binary_tree **destination = &(p_tree_node_iterator->path[dir]); \
	if (!*destination) \
		INSERT_TREE_NODE(*destination); \
	p_tree_node_iterator = *destination; \
}

#define NEW_CODE() \
{ \
	p_tree_node_iterator = tree_node; \
}

#define NEW_GROUP() \
{ \
	NEW_CODE(); \
	RESET_TREE_NODES(); \
}

#define PATH_CONTINUES() \
	(p_tree_node_iterator->path[0] || p_tree_node_iterator->path[1])

#define IS_FINAL() \
	(p_tree_node_iterator->is_final)

#define SET_FINAL() \
{ \
	p_tree_node_iterator->is_final = true; \
}


/* Output templates. */
const char *output[] = {
	"Set %d is not immediately decodable\n",
	"Set %d is immediately decodable\n"
};



/* Everything starts here. :) */
int main ()
{
	int c, set = 1;
	bool is_immediate_decodable = true;

	struct binary_tree
		tree_node[MAX_TREE_NODES],
		*p_tree_node_iterator,
		*p_last_tree_node;

	NEW_GROUP();

	while ((c = getc(stdin)) > 0)
	{
		if (is_immediate_decodable)
		{
			switch (c)
			{
				/* 0 or 1. */
				case '0':
				case '1':
				{
					c -= '0';
					GO(c);
					if (IS_FINAL())
						is_immediate_decodable = false;
					break;
				}

				/* End of a code. */
				case '\n':
				case ' ':
				case '\t':
				{
					/* Checking if is immediate decodable. */
					if (PATH_CONTINUES()) {
						is_immediate_decodable = false;
						continue;
					}
					/* This is a final node for a code. */
					SET_FINAL();
					/* A new group takes place. */
					NEW_CODE();
					break;
				}

				case '9':
				{
					fprintf(stdout, output[is_immediate_decodable], set);
					NEW_GROUP();
					is_immediate_decodable = true;
					++set;
					break;
				}
			}
		}
		else if (c == '9') /* End of a group. */
		{
			fprintf(stdout, output[is_immediate_decodable], set);
			NEW_GROUP();
			is_immediate_decodable = true;
			++set;
		}
	}

	return 0;
}
