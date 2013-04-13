#include "<cstdio>"


template <class C>
inline void swap (C &a, C &b)
{
	C c;
	c = a;
	a = b;
	b = c;
}


template <class C>
inline void sort (C &x, C &y, C &z)
{
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

	inline void scanf() {
		scanf("%d %d %d", &x, &y, &z);
	}

	inline void sort() {
		sort(x, y, z);
	}

	inline int max_height_alone() {
		if (z == y || y == x)
			return z;
	}
};


#define MAX_BLOCKS 30
Block block[MAX_BLOCKS];
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
		for (int i = 0; i < total_blocks; ++i)
		{
			current_block = block[i];
			current_block->scanf();
			current_block->sort();
			partial_height[i] = current_block->max_height_alone();
		}

		printf("Case %d: maximum height = %d\n", test_case, maximum_height);
		++test_case;

		scanf("%d", &total_blocks);
	}

	return 0;
}