#include <cstdio>


#define MAX_H 200
#define MAX_W 50
#define SIZE MAX_H
#define T_SIZE (SIZE + 2)

#define VECINOS 4

#define WHITE 0
#define BLACK 1
#define FONDO 2
#define HUECO 3
#define COLOR 4

#define ANKH 'A'
#define WEDJAT 'J'
#define DJED 'D'
#define SCARAB 'S'
#define WAS 'W'
#define AKHET 'K'

#define TOTAL_HIEROGLYPHS 6

// DEBUG
const int print[] = {
	'.',
	'X',
	'"'
};

const char hieroglyphs [] = {
	WAS,	// 'W' 4
	ANKH,	// 'A' 0
	AKHET,	// 'K' 5
	WEDJAT,	// 'J' 1
	SCARAB,	// 'S' 3
	DJED	// 'D' 2
};

const int holes_alpha[] = {
	1,	// 0 ANKH
	5,	// 1 DJED
	3,	// 2 WEDJAT
	2,	// 3 AKHET
	4,	// 4 SCARAB
	0,	// 5 WAS
};

const int holes[] = {
	5,	// 0 WAS
	0,	// 1 ANKH
	3,	// 2 AKHET
	2,	// 3 WEDJAT
	4,	// 4 SCARAB
	1,	// 5 DJED
};


/*************************************************/


struct Coord
{
	int x, y;

	inline Coord & operator += (const Coord &c) {
		x += c.x;
		y += c.y;
		return *this;
	}
};


/*************************************************/


#define FnRellenado(f) int f (const Coord &c)
struct RellenoColor;
typedef FnRellenado ((*FuncionRellenado));

FnRellenado (rellenar_fondo);
FnRellenado (rellenar_jeroglifico);
FnRellenado (rellenar_hueco);

struct RellenoColor
{
	int fin;
	FuncionRellenado fr;
};

RellenoColor
	fondo = {FONDO, rellenar_fondo},
	jeroglificos = {COLOR, rellenar_jeroglifico},
	huecos = {HUECO, rellenar_hueco};


/*************************************************/


template <typename C>
struct Tapiz
{
	C m[T_SIZE][T_SIZE];

	C color_ini, color_fin;
	size_t w, h, tw, th;

	static const Coord vecino[VECINOS];
	static const int digit[16][4];
	
	inline C * operator [] (size_t n) {return m[n];}
	inline C & operator [] (Coord c) {return m[c.x][c.y];}
	inline C & tapiz (Coord c) {return m[c.x][c.y];}

	inline void clear (size_t H, size_t W) {
		h = H;
		w = W;
		th = h + 1;
		tw = w + 1;
		m[0][0] = m[th][0] = m[0][tw] = m[th][tw] = 0;
		for (size_t i = 1; i < th; ++i)
			m[i][0] = m[i][tw] = 0;
		for (size_t i = 1; i < tw; ++i)
			m[0][i] = m[th][i] = 0;
		++th;
		++tw;
		jeroglificos.fin = COLOR;
	}

	inline bool is_invalid (const Coord &c)
	{
		return c.x < 0 || c.y < 0 || c.x >= th || c.y >= tw;
	}


	inline void read (size_t H, size_t W)
	{
		int n, nk;

		clear (H, W * 4);

		for (size_t i = 1; i <= H; ++i)
		{
			nk = 1;
			for (size_t j = 0; j < W; ++j)
			{
				scanf("%1x", &n);
				for (size_t k = 0; k < 4; ++k, ++nk)
				{
					m[i][nk] = digit[n][k];
				}
			}
			getchar();
		}
	}
};


template <typename C>
const Coord Tapiz<C>::vecino[VECINOS] = {
	{-1,  0},
	{ 0, -1},
	{ 0,  1},
	{ 1,  0}
};


template <typename C>
const int Tapiz<C>::digit[16][4] = {
	{0,0,0,0},	//  0 = 0000
	{0,0,0,1},	//  1 = 0001
	{0,0,1,0},	//  2 = 0010
	{0,0,1,1},	//  3 = 0011
	{0,1,0,0},	//  4 = 0100
	{0,1,0,1},	//  5 = 0101
	{0,1,1,0},	//  6 = 0110
	{0,1,1,1},	//  7 = 0111
	{1,0,0,0},	//  8 = 1000
	{1,0,0,1},	//  9 = 1001
	{1,0,1,0},	// 10 = 1010
	{1,0,1,1},	// 11 = 1011
	{1,1,0,0},	// 12 = 1100
	{1,1,0,1},	// 13 = 1101
	{1,1,1,0},	// 14 = 1110
	{1,1,1,1}	// 15 = 1111
};


/*************************************************/


Tapiz <int> tapiz;


int rellenar (const Coord &c, RellenoColor &rc)
{
	Coord a;
	int r, r_aux;

	r = 0;
	tapiz[c] = rc.fin;
	for (size_t i = 0; i < VECINOS; ++i)
	{
		a = c;
		a += tapiz.vecino[i];
		if (tapiz.is_invalid (a))
			continue;
		r_aux = rc.fr (a);
		if (r_aux > r)
			r = r_aux;
	}

	return r;
}


FnRellenado (rellenar_fondo)
{
	static int d = 0;
	//fprintf(stderr, "fondo[%d]: %d %d (%c)\n", d++, c.x, c.y, tapiz[c] < 3 ? print[tapiz[c]] : tapiz[c] + '0');
	switch (tapiz[c])
	{
		case WHITE:
			rellenar (c, fondo);
			break;
		case BLACK:
			rellenar (c, jeroglificos);
			++jeroglificos.fin;
	}
	--d;

	return 0;
}


FnRellenado (rellenar_jeroglifico)
{
	//fprintf(stderr, "jeroglifico: %d %d (%c)\n", c.x, c.y, tapiz[c] < 3 ? print[tapiz[c]] : tapiz[c] + '0');
	switch (tapiz[c])
	{
		case BLACK:
			rellenar (c, jeroglificos);
	}

	return 0;
}


FnRellenado (rellenar_hueco)
{
	//fprintf(stderr, "hueco: %d %d (%c)\n", c.x, c.y, tapiz[c] < 3 ? print[tapiz[c]] : tapiz[c] + '0');
	int t = tapiz[c];
	switch (t)
	{
		case WHITE:
			return rellenar (c, huecos);
		default:
			return t;
	}
}


/*************************************************/


int main ()
{
	int H, W, test_case = 1;

	int hieroglyphs_count[TOTAL_HIEROGLYPHS];

	while (scanf ("%d %d", &H, &W), H || W)
	{
		Coord c_ini = {0,0};

		for (size_t i = 0; i < TOTAL_HIEROGLYPHS; ++i)
			hieroglyphs_count[i] = 0;

		tapiz.read (H, W);

		rellenar (c_ini, fondo);

		const int COLOR_FIN = jeroglificos.fin;
		int color_count[COLOR_FIN];
		for (size_t i = COLOR; i < COLOR_FIN; ++i)
			color_count[i] = 0;

		for (c_ini.x = 0; c_ini.x < tapiz.th; ++c_ini.x)
		{
			for (c_ini.y = 0; c_ini.y < tapiz.tw; ++c_ini.y)
			{
				if (tapiz[c_ini] == WHITE)
				{
					++color_count[rellenar (c_ini, huecos)];
				}
			}
		}

		for (size_t i = COLOR; i < COLOR_FIN; ++i)
			++hieroglyphs_count[holes[color_count[i]]];
		printf("Case %d: ", test_case);
		for (size_t i = 0; i < TOTAL_HIEROGLYPHS; ++i)
		{
			int	c = hieroglyphs[holes_alpha[i]],
				h = hieroglyphs_count[i];
			for (size_t j = 0; j < h; ++j)
				putchar (c);
		}
		putchar ('\n');

		++test_case;
	}

	return 0;
}