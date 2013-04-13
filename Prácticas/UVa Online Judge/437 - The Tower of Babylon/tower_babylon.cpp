#include <cstdio>


template <class C>
inline void swap (C &a, C &b)
{
	C c;
	c = a;
	a = b;
	b = c;
}


struct Block
{
	int x, y, z;

	inline void readline() {
		scanf("%d %d %d", &x, &y, &z);
	}

	inline void sort() {
		if (x > y)
			swap(x, y);
		if (x > z)
			swap(x, z);
		if (y > z)
			swap(y, z);
	}

	inline int max_height_alone() {
		if (z == y || y == x)
			return z;
		return x + z;
	}
};


struct BlockTree
{
	int
		x,
		y,
		h;
	BlockTree
		*child,
		*siebling;
};


#define MAX_BLOCKS 30
Block
	block[MAX_BLOCKS];
BlockTree
	block_tree[3*MAX_BLOCKS];
int partial_height[MAX_BLOCKS];


int main()
{
	int
		test_case = 1,
		total_blocks,
		maximum_height;
	Block *current_block;

	scanf("%d", &total_blocks);

	while (total_blocks)
	{
		maximum_height = 0;
		for (int i = 0; i < total_blocks; ++i)
		{
			current_block = block + i;
			current_block->readline();
			current_block->sort();
			maximum_height += partial_height[i] = current_block->max_height_alone();
			printf("%d: %d (%d, %d, %d)\n", i, partial_height[i], current_block->x, current_block->y, current_block->z);
		}

		printf("Case %d: maximum height = %d\n", test_case, maximum_height);
		++test_case;

		scanf("%d", &total_blocks);
	}

	return 0;
}