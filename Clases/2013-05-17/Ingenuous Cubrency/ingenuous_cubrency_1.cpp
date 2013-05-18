#include <cstdio>


#define MAX_COINS 21
#define MAX_CUBRENCY 10000
#define NOT_SET 0

typedef unsigned long long int lint;
typedef unsigned int uint;


/***************************************************************************/


struct Coin
{
	uint c[MAX_COINS];

	inline uint & operator [] (size_t n) {return c[n];}

	Coin () {
		uint i, v;
		for (i = 0; i < MAX_COINS; ++i) {
			v = MAX_COINS - i;
			v = v * v * v;
			c[i] = v;
		}
	}


	void descomponer (uint n, uint r[MAX_COINS], size_t ini = 0) const {
		for (; ini < MAX_COINS; ++ini) {
			r[ini] = n / c[ini];
			n = n % c[ini];
		}
	}
};


/***************************************************************************/


Coin coin;
lint cubrencies[MAX_CUBRENCY] = {NOT_SET};


lint possible_cubrencies (size_t n)
{
	int cubrency[MAX_COINS];

	if (cubrencies[n])
		return cubrencies[n];
};


/***************************************************************************/


int main ()
{
	return 0;
}