#include <iostream>
using namespace std;


struct Elecciones
{
	int s, max1, max2;

	void check_max( int votos ) {
		if (votos > max1) {
			max2 = max1;
			max1 = votos;
		}
		else if (votos > max2) {
			max2 = votos;
		}
	}

	void get (int votos) {
		s += votos;
		check_max (votos);
	}

	int ronda () {
		// max1 >= 0.45 s --> 100 max1 >= 45 s
		// max1 >= 0.40 s --> 100 max1 >= 40 s
		// max1 - max2 >= 0.10 s --> 100 max1 - 100 max2 >= 10 s
		max1 *= 100;
		max2 *= 100;
		if (max1 >= 45 * s)
			return 1;
		if (max1 >= 40 * s && max1 - max2 >= 10 * s)
			return 1;
		return 2;
	}
};



Elecciones e = {0};


int main ()
{
	int n, v;

	cin >> n;
	while (n--) {
		cin >> v;
		e.get(v);
	}
	cout << e.ronda() << endl;

	return 0;
}