#include <cstdio>


#define MAX_COINS 21
#define BIG_COINS (MAX_COINS - 1)
#define LAST_BIG_COIN (BIG_COINS - 1)
#define MAX_AMMOUNT 10000

typedef unsigned long long int lint;
typedef unsigned int uint;
typedef int Change[BIG_COINS];


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


	inline void descomponer (uint n, Change r, size_t ini = 0) const {
		for (; ini < BIG_COINS; ++ini) {
			r[ini] = n / c[ini];
			n = n % c[ini];
		}
	}

	inline size_t biggest_index (Change r, size_t i = 0) {
		for (; i < LAST_BIG_COIN; ++i)
			if (r[i])
				break;
		return i;
	}
};


/***************************************************************************/

Coin coin;
lint cubrencies[MAX_AMMOUNT][BIG_COINS];


lint count_cubrencies (size_t n, Change change, size_t ini)
{
	int &count = change[ini];
	uint &value = coin[ini];
	size_t n_aux, ini_aux;
	lint &ans = cubrencies[n][ini], partial_ans;

	if (ini == LAST_BIG_COIN)
		return count + 1;

	++ini;
	n_aux = n - count * value;

	for (; count >= 0; --count, n_aux += value)
	{
		coin.descomponer (n_aux, change, ini);
		ini_aux = ini; //coin.biggest_index (change, ini);
		partial_ans = cubrencies[n_aux][ini_aux]
			? cubrencies[n_aux][ini_aux]
			: count_cubrencies (n_aux, change, ini_aux);
		for (size_t i = ini; i < ini_aux; ++i)
			cubrencies[n][i] += partial_ans;
		ans += partial_ans;
	}

	return ans;
}


lint possible_cubrencies (size_t n)
{
	Change change;
	size_t degree;
	lint ans;

	if (cubrencies[n][0])
		return cubrencies[n][0];

	coin.descomponer (n, change);
	degree = coin.biggest_index (change);
	ans = count_cubrencies (n, change, degree);
	for (size_t i = 0; i < degree; ++i)
		cubrencies[n][i] = ans;

	return ans;
};


/***************************************************************************/


int main ()
{
	uint ammount;
	while (scanf ("%d", &ammount) == 1)
		printf("%llu\n", possible_cubrencies(ammount));
	return 0;
}
