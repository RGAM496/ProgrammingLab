#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define MAX_N 100

const double PI = 3.1415926535897932384626433832795;


struct Punto
{
	double x, y;
};


istream & operator >> (istream &s, Punto &P)
{
	return s >> P.x >> P.y;
}


inline double distancia (const Punto &A, const Punto &B)
{
	double x, y;
	x = A.x - B.x;
	y = A.y - B.y;
	x *= x;
	y *= y;
	return sqrt (x + y);
}


Punto P[MAX_N];


int main ()
{
	int n;
	double r, d;

	cin >> n >> r;

	cin >> P[0];
	d = 0;
	for (int i = 1; i < n; ++i)
	{
		cin >> P[i];
		d += distancia (P[i], P[i-1]);
	}
	d += distancia (P[0], P[n-1]);
	d += PI * r * 2;

	cout << fixed << setprecision (2) << d << endl;
}