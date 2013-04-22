#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define MAX_BLOCKS 25;


struct Block
{
	int position;
	Block *next_over;
	
	Block () : next_over(0) {}
};


struct Table
{
	vector<Block> block;
	vector<Block*> position;
	Block *first_block;
	
	
	Table (int total_blocks) : block(total_blocks), position(total_blocks) {
		first_block = &block[0];
		for (int i = 0; i < total_blocks; ++i) {
			position[i] = first_block + i;
			block[i].position = i;
		}
	}
	
	int block_number (Block *p) {
		return p - first_block;
	}
	
	bool is_ilegal (int a, int b) {
		return (a == b) || (block[a].position == block[b].position);
	}
	
	Block * last_block_in_position (int b) {
		Block *p = position[b];
		
		if (p)
			while (p->next_over)
				p = p->next_over;
		
		return p;
	}

	Block * last_block_before (int b) {
		Block
			*p = position[block[b].position],
			*pb = first_block + b;

		if (p == pb)
			return 0;

		do {
			p = p->next_over;
		}
		while (p->next_over != pb);

		return p;
	}
	
	void return_blocks_over (Block *b) {
		Block
			*over = b->next_over,
			*last_in_position;
		int over_number;

		while (over) {
			over_number = block_number(over);
			last_in_position = last_block_in_position(over_number);
			
			if (last_in_position)
				last_in_position->next_over = over;
			else
				position[over_number] = over;
			
			b = over;
			over = b->next_over;
			b->next_over = 0;
		}
	}
	
	void move_onto (int a, int b) {
		if (is_ilegal(a,b))
			return;

		Block *p, *pb;

		return_blocks_over(first_block + a);
		return_blocks_over(first_block + b);

		pb = first_block + b;
		p = last_block_before(a);
		if (p) {
			p->next_over->next_over = pb->next_over;
			pb->next_over = p->next_over;
			p->next_over = 0;
		}
		else {
			p = first_block + a;
			p->next_over = pb->next_over;
			pb->next_over = p;
			position[a] = 0;
		}
	}
	
	void move_over (int a, int b) {
		if (is_ilegal(a,b))
			return;

		Block *p, *pb;

		return_blocks_over(first_block + a);

		pb = first_block + b;
		p = last_block_before(a);
		if (p) {
			p->next_over->next_over = pb->next_over;
			pb->next_over = p->next_over;
			p->next_over = 0;
		}
		else {
			p = first_block + a;
			p->next_over = pb->next_over;
			pb->next_over = p;
			position[a] = 0;
		}
	}
	
	void pile_onto (int a, int b) {
		if (is_ilegal(a,b))
			return;

		Block *p, *pb;

		return_blocks_over(first_block + b);

		pb = first_block + b;
		p = last_block_before(a);
		if (p) {
			p->next_over->next_over = pb->next_over;
			pb->next_over = p->next_over;
			p->next_over = 0;
		}
		else {
			p = first_block + a;
			p->next_over = pb->next_over;
			pb->next_over = p;
			position[a] = 0;
		}
	}
	
	void pile_over (int a, int b) {
		if (is_ilegal(a,b))
			return;

		Block *p, *pb;

		pb = first_block + b;
		p = last_block_before(a);
		if (p) {
			p->next_over->next_over = pb->next_over;
			pb->next_over = p->next_over;
			p->next_over = 0;
		}
		else {
			p = first_block + a;
			p->next_over = pb->next_over;
			pb->next_over = p;
			position[a] = 0;
		}
	}
};


int main ()
{
	int total_blocks, a, b;
	char command[2][5];
	scanf("%d", &total_blocks);
	Table table(total_blocks);

	scanf("%s", command[0]);
	while (strcmp(command[0], "quit"))
	{
		scanf("%d %s %d", &a, command[1], &b);

		if (strcmp(command[0], "move") == 0)
			if (strcmp(command[1], "onto") == 0)
				table.move_onto(a,b);
			else
				table.move_over(a,b);
		else
			if (strcmp(command[1], "onto") == 0)
				table.move_onto(a,b);
			else
				table.move_over(a,b);
	}

	return 0;
}