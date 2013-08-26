#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_N 10000

typedef double coord;
typedef double angle;

const angle PI = atan( 1.0 ) * 4,
	MITAD_PI = PI / 2;


struct Punto
{
	coord x, y;
	angle a;
	int index;
};


bool operator < ( const Punto &A, const Punto &B )
{
	return ( A.y == B.y ) ? ( A.x < B.x ) : ( A.y < B.y );
}


bool comp_angulo( const Punto &A, const Punto &B )
{
	return A.a < B.a;
}


istream & operator >> ( istream &is, Punto &P )
{
	return is >> P.x >> P.y;
}


ostream & operator << ( ostream &os, const Punto &P )
{
	return os << (P.index + 2) << ". (" << P.x << ", " << P.y << ')';
}


inline angle angulo( const Punto &A, const Punto &B )
{
	Punto P;
	angle a;
	P.x = B.x - A.x;
	P.y = B.y - A.y;
	if( P.x == 0 )
	{
		return P.y > 0 ? MITAD_PI : - MITAD_PI;
	}
	a = atan( P.y / P.x );
	return a < 0 ? MITAD_PI - a : a;
}


int N;
Punto P[MAX_N], P0;


inline void insertar( const Punto &Pi, int i )
{
	if( Pi < P0 )
	{
		P[i] = P0;
		P0 = Pi;
	}
	else
	{
		P[i] = Pi;
	}
}


int main ()
{
	Punto Q;
	int M;

	cin >> N;
	--N;

	cin >> P0;
	P0.index = -1;
	for( int i = 0; i < N; ++i )
	{
		cin >> Q;
		Q.index = i;
		insertar( Q, i );
	}

	#ifdef DEBUG
	cerr << "\t" << P0 << "\n\n";
	#endif

	for( int i = 0; i < N; ++i )
	{
		P[i].a = angulo( P0, P[i] );
		#ifdef DEBUG
		cerr << "\t" << P[i] << " [" << P[i].a << "]\n";
		#endif
	}
	sort( P, P + N, comp_angulo );

	#ifdef DEBUG
	cerr << "\n";
	for( int i = 0; i < N; ++i )
	{
		cerr << "\t" << P[i] << " [" << P[i].a << "]\n";
	}
	cerr << "\n";
	#endif

	M = N / 2;
	cout << ( P0.index + 2 ) << ' ' << ( P[M].index + 2 );

	return 0;
}