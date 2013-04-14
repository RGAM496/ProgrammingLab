#include <cstdio>


template <class C>
inline void swap (C &a, C &b)
{
	C c;
	c = a;
	a = b;
	b = c;
}

template <class C>
inline void sort(C &x, C &y, C &z) {
	if (x > y)
		swap(x, y);
	if (x > z)
		swap(x, z);
	if (y > z)
		swap(y, z);
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
		h,
		max_h;

	BlockTree
		*child,
		*siebling;

	inline void reset_height() {
		max_h = 0;
	}

	inline void reset() {
		child = 0;
		siebling = 0;
		reset_height();
	}

	inline int max_height() {
		if (max_h)
			return max_h;
		int mh;
		for (BlockTree *ch = child; ch; ch = ch->siebling) {
			mh = ch->max_height();
			if (max_h < mh)
				max_h = mh;
		}
		return max_h;
	}
};

#define MAX_BLOCKS 30
#define MAX_COMBINATIONS (3*MAX_BLOCKS)
extern struct BlockGraph graph[MAX_COMBINATIONS][MAX_COMBINATIONS];

struct BlockGraph
{
	int
		x,
		y,
		h;

	bool dirty;
};


Block
	block[MAX_COMBINATIONS];
BlockTree
	block_tree[MAX_COMBINATIONS];
struct BlockGraph graph[MAX_COMBINATIONS][MAX_COMBINATIONS];
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