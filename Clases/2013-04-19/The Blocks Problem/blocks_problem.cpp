#include <cstdio>
#include <vector>

using namespace std;

#define MAX_BLOCKS 25;


struct Block
{
	position;
	Block *next_over;
	
	Block () : next_over(0) {}
};


struct Table
{
	vector<Block> block;
	vector<Block*> position;
	Block *first_block;
	
	
	Table (int total_blocks) : block(total_blocks) position(total_blocks) {
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
	
	void return_blocks_over (Block *b) {
		Block
			*over = b->next_over,
			*last_in_position;
		int over_number;
		

		while (over) {
			over_number = block_number(over);
			last_in_position = last_block_in_position(over_number);
			
			
			
			b = over;
			over = b->next_over;
		}
	}
	
	void move_onto (int a, int b) {
		if (is_ilegal(a,b))
			return;
	}
	
	void move_over (int a, int b) {
		if (is_ilegal(a,b))
			return;
	}
	
	void pile_onto (int a, int b) {
		if (is_ilegal(a,b))
			return;
	}
	
	void pile_over (int a, int b) {
		if (is_ilegal(a,b))
			return;
	}
};