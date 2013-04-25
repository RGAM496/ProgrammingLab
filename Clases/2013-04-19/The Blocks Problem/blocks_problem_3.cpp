#include <cstdio>
#include <cstring>


struct Block
{
	Block
		*up,
		*down,
		*position;

	inline bool is_final () {return up == position;}
	inline void set_final () {position->down = this;}
};


struct Table
{
	Block
		*block,
		*position;
	int total_blocks;

	Table (int max_blocks);
	~Table ();

	inline int block_number (Block *b) {return b - block;}
	inline int position_number (Block *p) {return p - position;}
	inline Block * last_block (int pos) {return position[pos].down;}
	inline Block * last_block (Block *b) {return b->position->down;}

	inline void desenlazar (Block *b);
	inline void desenlazar (Block *ini, Block *fin);
	inline void enlazar (Block *under, Block *over);
	inline void enlazar (Block *under, Block *over_ini, Block *over_fin);
	inline void retornar (Block *b);
	inline void retornar_encima (Block *b);
	inline void put_over (Block *a, Block *b);

	inline bool is_ilegal (int a, int b);
	void move_onto (int a, int b);
	void move_over (int a, int b);
	void pile_onto (int a, int b);
	void pile_over (int a, int b);

	void print ();

	int debug (int pos) {
		if (block + pos < position)
			return pos;
		return -(pos - total_blocks);
	}
	void debug (Block *b) {
		printf ("% d (% d, % d) [% d]\n",
			debug ((int)(b - block)),
			debug ((int)(b->down - block)),
			debug ((int)(b->up - block)),
			debug ((int)(b->position - block)));
	}
};


/***************************************************/


Table::Table (int max_blocks) : total_blocks(max_blocks)
{
	Block *b, *p;

	block = new Block[2*total_blocks];
	position = block + total_blocks;
	for (b = block, p = position; b < position; ++b, ++p)
	{
		b->down = p;
		b->up = p;
		b->position = p;
		p->down = b;
		p->up = b;
		p->position = p;
	}
}

Table::~Table ()
{
	delete[] block;
}


/***************************************************/


bool Table::is_ilegal (int a, int b)
{
	return (a == b) || (block[a].position == block[b].position);
}


void Table::desenlazar (Block *b)
{
	b->down->up = b->up;
	b->up->down = b->down;
	if (b->is_final())
		b->down->set_final();
}

void Table::desenlazar (Block *ini, Block *fin)
{
	ini->down->up = fin->up;
	fin->up->down = ini->down;
	if (fin->is_final())
		ini->down->set_final();
}


void Table::enlazar (Block *under, Block *over)
{
	over->down = under;
	over->up = under->up;
	under->up = over;
	over->position = under->position;
	if (over->is_final())
		over->set_final();
}

void Table::enlazar (Block *under, Block *over_ini, Block *over_fin)
{
	over_ini->down = under;
	over_fin->up = under->up;
	under->up = over_ini;
	while (over_ini != over_fin) {
		over_ini->position = under->position;
		over_ini = over_ini->up;
	}
	over_fin->position = under->position;
	if (over_fin->is_final())
		over_fin->set_final();
}


void Table::retornar (Block *b)
{
	Block * pos_dest;

	pos_dest = b + total_blocks;
	pos_dest = last_block (pos_dest);
	desenlazar (b);
	enlazar (pos_dest, b);
}


void Table::retornar_encima (Block *b)
{
	while (!b->is_final())
		retornar (b->up);
}


void Table::put_over (Block *a, Block *b)
{
	Block *la, *lb;

	la = last_block (a);
	lb = last_block (b);
	desenlazar (a, la);
	enlazar (lb, a, la);
}


/***************************************************/


void Table::move_onto (int a, int b)
{
	if (is_ilegal(a,b))
		return;

	Block *pa, *pb;

	pa = block + a;
	pb = block + b;
	retornar_encima (pa);
	retornar_encima (pb);
	put_over (pa, pb);
}


void Table::move_over (int a, int b)
{
	if (is_ilegal(a,b))
		return;

	Block *pa, *pb;

	pa = block + a;
	pb = block + b;
	retornar_encima (pa);
	put_over (pa, pb);
}


void Table::pile_onto (int a, int b)
{
	if (is_ilegal(a,b))
		return;

	Block *pa, *pb;

	pa = block + a;
	pb = block + b;
	retornar_encima (pb);
	put_over (pa, pb);
}


void Table::pile_over (int a, int b)
{
	if (is_ilegal(a,b))
		return;

	Block *pa, *pb;

	pa = block + a;
	pb = block + b;
	put_over (pa, pb);
}


/***************************************************/


void Table::print ()
{
	Block *p;
	for (int i = 0; i < total_blocks; ++i)
	{
		printf("%d:", i);
		p = position[i].up;
		while (p != p->position) {
			printf(" %d", block_number(p));
			p = p->up;
		}
		putchar('\n');
	}
}


/***************************************************/


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
				table.pile_onto(a,b);
			else
				table.pile_over(a,b);

		scanf("%s", command[0]);
	}

	table.print();

	return 0;
}