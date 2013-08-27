#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_N 2000
#define INF 1000000

typedef double coord;
typedef double angle;

const angle PI = atan( 1.0 ) * 4,
	MITAD_PI = PI / 2;


struct Punto
{
	coord x, y;
	angle a;
};


bool operator < ( const Punto &A, const Punto &B )
{
	return ( A.x == B.x ) ? ( A.y < B.y ) : ( A.x < B.x );
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
	return os << '(' << P.x << ", " << P.y << ')';
}


inline angle angulo( const Punto &A, const Punto &B )
{
	Punto P;
	angle a;
	P.x = B.x - A.x;
	P.y = B.y - A.y;
	if( P.x == 0 )
	{
		return P.y > 0 ? INF : - INF;
	}
	return P.y / P.x;
}


inline angle direccion_angulo( const Punto &A, const Punto &B, const Punto &C )
{
	angle r;
	r = ( B.x - A.x ) * ( C.y - A.y ) - ( B.y - A.y ) * ( C.x - A.x );
	return r;
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
	int N_AUX;
	Punto Q;

	while( cin >> N, N )
	{
		N_AUX = N - 1;
		cin >> P0;
		for( int i = 0; i < N_AUX; ++i )
		{
			cin >> Q;
			insertar( Q, i );
		}
		for( int i = 0; i < N_AUX; ++i )
		{
			P[i].a = angulo( P0, P[i] );
		}
		sort( P, P + N_AUX, comp_angulo );
	}

	return 0;
}