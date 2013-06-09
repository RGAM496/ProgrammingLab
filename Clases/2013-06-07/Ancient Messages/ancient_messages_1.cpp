#include <cstdio>

#define SIZE 512
#define T_SIZE (SIZE + 2)

#define VECINOS 8

#define BLACK 0
#define WHITE 1
#define FONDO 2
#define HUECO 3
#define COLOR 4

#define ANKH 'A'
#define WEDJAT 'J'
#define DJED 'D'
#define SCARAB 'S'
#define WAS 'W'
#define AKHET 'K'



struct Coord
{
	int x, y;

	inline Coord & operator += (const Coord &c) {
		x += c.x;
		y += c.y;
		return *this;
	}
};


template <typename COLOR>
struct Tapiz
{
	COLOR m[T_SIZE][T_SIZE];

	COLOR color_ini, color_fin;
	size_t size, t_size;

	static const Coord vecino[VECINOS] = {
		{-1, -1},
		{-1,  0},
		{-1,  1},
		{ 0, -1},
		{ 0,  1},
		{ 1, -1},
		{ 1,  0},
		{ 1, -1}
	};
	
	inline COLOR *& operator [] (size_t n) {return m[n];}
	inline COLOR & operator [] (Coord c) {return m[c.x][c.y];}
	inline COLOR & tapiz (Coord c) {return m[c.x][c.y];}

	inline void clear (size_t s) {
		size_t l = s + 1;
		m[0][0] = m[l][0] = m[0][l] = m[l][l] = 0;
		for (size_t i = 1; i < l; ++i)
			m[0][i] = m[i][0] = m[i][l] = m[l][i] = 0;
		size = s;
		t_size = ++l;
	}

	inline bool is_invalid (const Coord &c)
	{
		return c.x < 0 || c.y < 0 || c.x >= t_size || c.y >= t_size;
	}

	void rellenar (const Coord &c);

	inline void rellenar (const Coord &c, int color) {
		color_ini = tapiz (c);
		color_fin = color;
		rellenar (c);
	}
};


template <typename COLOR>
void Tapiz <COLOR>::rellenar (Coord c)
{
	Coord a;

	for (size_t i = 0; i < VECINOS; ++i)
	{
		a = c;
		c += vecino[i];
		if (is_invalid (c))
			continue;
		if (tapiz (a) == color_ini)
			rellenar (a);
	}
	tapiz (c) = color_fin;
}


int main ()
{
	return 0;
}