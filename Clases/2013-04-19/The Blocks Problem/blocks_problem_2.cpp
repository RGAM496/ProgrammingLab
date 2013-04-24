#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;


struct Block
{
	Block
		*up,
		*down;
	int position;
	
	Block () : up(0), down(0) {}
};


struct Table
{
	vector<Block>
		block,
		position;
	Block *first_block;
	int total_blocks;

	void move_onto (int a, int b);
	void move_over (int a, int b);
	void pile_onto (int a, int b);
	void pile_over (int a, int b);

	void print();
	void debug();

	inline bool is_ilegal (int a, int b);

	inline Table (int num_blocks);

	inline void enlazar (Block &under, Block &over);
	inline void enlazar (Block *under, Block *over);
	inline int block_number (Block *p_block);
	inline Block * last_block_in_position (int pos);
	inline void set_as_last_block (Block *b);
	inline void put_over (Block *b, int pos);
	inline void return_block (Block *b);
	inline void return_blocks_over (Block *b);
	inline void update_blocks_over (Block *b);
};


Table::Table (int num_blocks)
: block(num_blocks), position(num_blocks), total_blocks(num_blocks)
{
	first_block = &block[0];
	for (int i = 0; i < total_blocks; ++i)
	{
		block[i].position = i;
		enlazar (position[i], block[i]);
		set_as_last_block (&block[i]);
	}
}


void Table::enlazar (Block &under, Block &over)
{
	enlazar (&under, &over);
}
void Table::enlazar (Block *under, Block *over)
{
	under->up = over;
	over->down = under;
}


int Table::block_number (Block *p_block)
{
	return p_block - first_block;
}


Block * Table::last_block_in_position (int pos)
{
	return position[pos].down;
}


void Table::set_as_last_block (Block *b)
{
	b->up = 0;
	position[b->position].down = b;
}


void Table::put_over (Block *b, int pos)
{
	if (b->down != &position[b->position])
		set_as_last_block (b->down);
	else
		position[b->position].up = 0;
	enlazar (last_block_in_position(pos), b);
	b->position = pos;
}


void Table::return_block (Block *b)
{
	int pos = block_number(b);
	if (b->down)
		b->down->up = b->up;
	if (b->up)
		b->up->down = b->down;
	enlazar (last_block_in_position(pos), b);
	b->position = pos;
	set_as_last_block (b);
}

void Table::return_blocks_over (Block *b)
{
	while (b->up)
	{
		b = b->up;
		return_block (b);
	}
	set_as_last_block (b);
}


void Table::update_blocks_over (Block *b)
{
	int pos = b->position;
	while (b->up)
	{
		b = b->up;
		b->position = pos;
	}
	position[pos].down = b;
}


bool Table::is_ilegal (int a, int b)
{
	return (a == b) || (block[a].position == block[b].position);
}


/* Move Onto */
void Table::move_onto (int a, int b)
{
	if (is_ilegal(a,b))
		return;

	Block
		*pa = first_block + a,
		*pb = first_block + b;
	puts("Legal");

	return_blocks_over (pa);
	return_blocks_over (pb);
	puts("Returned");

	put_over (pa, pb->position);
	puts("Putted Over");
	update_blocks_over (pa);
}


/* Move Over */
void Table::move_over (int a, int b)
{
	if (is_ilegal(a,b))
		return;

	Block
		*pa = first_block + a,
		*pb = first_block + b;

	return_blocks_over (pa);
	return_blocks_over (pb);

	put_over (pa, pb->position);
	update_blocks_over (pa);
}


/* Pile Onto */
void Table::pile_onto (int a, int b)
{
	if (is_ilegal(a,b))
		return;
}


/* Pile Over */
void Table::pile_over (int a, int b)
{
	if (is_ilegal(a,b))
		return;
}


void Table::print () {
	Block *p;
	for (int i = 0; i < total_blocks; ++i)
	{
		printf("\n%d:", i);
		p = position[i].up;
		if (p) {
			do {
				printf(" %d", block_number(p));
				p = p->up;
			}
			while (p);
		}
	}
}


void Table::debug () {
	Block *p;
	printf("\nBlock[0]: %p\nPosition[0]: %p\n", &block[0], &position[0]);
	for (int i = 0; i < total_blocks; ++i)
	{
		printf("\n%d:", i);
		p = position[i].up;
		if (p) {
			do {
				//printf(" %d", block_number(p));
				printf("\t%d (%d) [%p, %p]", block_number(p), p->position, p->down, p->up);
				p = p->up;
			}
			while (p);
		}
	}
	putchar('\n');
}


/* Main. */

int main ()
{
	int total_blocks, a, b;
	char command[2][5];
	scanf("%d", &total_blocks);
	Table table(total_blocks);

	table.debug();
	scanf("%s", command[0]);
	while (strcmp(command[0], "quit"))
	{
		scanf("%d %s %d", &a, command[1], &b);
		printf("\n\t%s %d %s %d\n", command[0], a, command[1], b);

		if (strcmp(command[0], "move") == 0)
			if (strcmp(command[1], "onto") == 0)
				table.move_onto(a,b);
			else
				table.move_over(a,b);
		else
			if (strcmp(command[1], "onto") == 0)
				table.pile_onto(a,b);
			else
				table.pile_over(a,b);

		table.debug();
		scanf("%s", command[0]);
	}

	table.print();

	return 0;
}