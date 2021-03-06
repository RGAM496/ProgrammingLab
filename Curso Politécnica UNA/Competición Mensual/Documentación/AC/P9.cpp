#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAX_N 50000
#define MAX_D 10000000000000

typedef long long int dist;
typedef dist coord;


struct Punto
{
	coord x, y;
	size_t ref;
};


bool min_x (const Punto &A, const Punto &B)
{
	return A.x < B.x || (A.x == B.x && A.y < B.y);
}


bool min_y (const Punto &A, const Punto &B)
{
	return A.y < B.y || (A.y == B.y && A.x < B.x);
}


bool operator < (const Punto &A, const Punto &B)
{
	return min_x( A, B );
}


dist distancia (const Punto &A, const Punto &B)
{
	dist x, y;
	x = A.x - B.x; x *= x;
	y = A.y - B.y; y *= y;
	return x + y;
}


istream & operator >> (istream &is, Punto &P)
{
	return is >> P.x >> P.y;
}


ostream & operator << (ostream &os, const Punto &p)
{
	return os << '(' << p.x << ", " << p.y << ')';
}


struct Par
{
	dist d;
	size_t a, b;
};


bool operator < (const Par &p1, const Par &p2)
{
	return p1.d < p2.d;
}


ostream & operator << (ostream &os, const Par &p)
{
	if( p.a > p.b )
		os << p.b << ' ' << p.a;
	else
		os << p.a << ' ' << p.b;
	return os << ' ' << sqrt( (double) p.d );
}


inline void menor_distancia_bruta (const size_t N, const Punto P[], Par &r)
{
	switch( N )
	{
		case 2:
		{
			r.a = P[0].ref;
			r.b = P[1].ref;
			r.d = distancia( P[0], P[1] );
		}
		break;

		case 3:
		{
			dist d;
			menor_distancia_bruta (2, P, r );
			d = distancia( P[0], P[2] );
			if( d < r.d )
			{
				r.d = d;
				r.b = P[2].ref;
			}
			d = distancia( P[1], P[2] );
			if( d < r.d )
			{
				r.d = d;
				r.a = P[1].ref;
				r.b = P[2].ref;
			}
		}
		break;

		default:
		{
			const Punto
				* const pN = P + N,
				* const pn = pN - 1;
			const Punto *pi, *pj;
			dist d;
			menor_distancia_bruta( 2, P, r );
			for( pi = P; pi < pn; ++pi )
			{
				for( pj = pi + 1; pj < pN; ++pj )
				{
					d = distancia( *pi, *pj );
					if( d < r.d )
					{
						r.d = d;
						r.a = pi->ref;
						r.b = pj->ref;
					}
				}
			}
		}
	}
}


void menor_distancia (const size_t N, const Punto X[], const Punto Y[], Par &r)
{
	if( N < 4 )
	{
		menor_distancia_bruta( N, X, r );
	}
	else
	{
		const size_t
			Nizq = (N + 1) / 2,
			Nder = N - Nizq;
		size_t iz, de, vN, vn, lim;
		dist d;
		Punto X_izq[Nizq], Y_izq[Nizq], X_der[Nder], Y_der[Nder], V[N],
			mediana;
		Par r_izq, r_der;

		for( size_t i = 0; i < Nizq; ++i )
			X_izq[i] = X[i];
		mediana = X[Nizq - 1];
		for( size_t i = 0; i < Nder; ++i )
			X_der[i] = X[Nizq + i];
		iz = de = 0;
		for( size_t i = 0; i < N; ++i )
		{
			if( mediana < Y[i] )
				Y_der[de++] = Y[i];
			else
				Y_izq[iz++] = Y[i];
		}

		menor_distancia( Nizq, X_izq, Y_izq, r_izq );
		menor_distancia( Nder, X_der, Y_der, r_der );
		r = min( r_izq, r_der );

		vN = 0;
		for( size_t i = 0; i < N; ++i )
		{
			if( abs( Y[i].x - mediana.x ) < r.d )
			{
				V[vN++] = Y[i];
			}
		}
		if( vN > 1 )
		{
			vn = vN - 1;
			for( size_t i = 0; i < vn; ++i )
			{
				lim = min( i + 8, vN );
				for( size_t j = i + 1; j < lim; ++j )
				{
					d = distancia( V[i], V[j] );
					if( d < r.d )
					{
						r.d = d;
						r.a = V[i].ref;
						r.b = V[j].ref;
					}
				}
			}
		}
	}
}


Punto X[MAX_N], Y[MAX_N];


int main ()
{
	size_t N, i;
	Par p;

	cin >> N;
	for( i = 0; i < N; ++i )
	{
		cin >> X[i];
		X[i].ref = i;
		Y[i] = X[i];
	}
	sort( X, X + N, min_x);
	sort( Y, Y + N, min_y);
	menor_distancia( N, X, Y, p );
	cout << fixed << setprecision( 6 ) << p << endl;

	return 0;
}