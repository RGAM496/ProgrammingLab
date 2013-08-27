#include <iostream>
#include <set>
using namespace std;

#define MAX_N 1001
#define PERDEDOR 0

typedef set <size_t> Set;
typedef Set::iterator Iterator;


ostream & operator << ( ostream &os, const Set &s )
{
	Iterator it;
	os << '{';
	if( s.size() > 0 )
	{
		it = s.begin();
		os << *it;
		for( ++it; it != s.end(); ++it )
		{
			os << ", " << *it;
		}
	}
	return os << '}';
}


struct Aeropuerto
{
	Set conexion;


	inline void conectar( size_t i ) {
		conexion.insert( i );
	}

	inline void desconectar( size_t i ) {
		conexion.erase( i );
	}
};


struct Grafo
{
	Aeropuerto A[MAX_N];


	inline void conectar( size_t i, size_t j ) {
		A[i].conectar( j );
		A[j].conectar( i );
	}

	inline void explotar( size_t i ) {
		Iterator it;
		Set &c = A[i].conexion;
		for( it = c.begin(); it != c.end(); ++it ) {
			A[*it].desconectar( i );
		}
	}

	inline void restaurar( size_t i ) {
		Iterator it;
		Set &c = A[i].conexion;
		for( it = c.begin(); it != c.end(); ++it ) {
			A[*it].conectar( i );
		}
	}


	size_t jugar( size_t i );
};


size_t Grafo::jugar( size_t i )
{
	Iterator it;
	Set &c = A[i].conexion;
	size_t r = PERDEDOR;

	if( c.size() > 0 )
	{
		explotar( i );
		for( it = c.begin(); it != c.end(); ++it )
		{
			if( jugar( *it) == PERDEDOR )
			{
				r = *it;
				break;
			}
		}
		restaurar( i );
	}

	return r;
}


Grafo grafo;


int main ()
{
	size_t n, k, o, d;

	cin >> n >> k;
	for( size_t i = 1; i < n; ++i )
	{
		cin >> o >> d;
		grafo.conectar( o, d );
	}
	n = grafo.jugar( k );
	if( n == PERDEDOR )
		cout << "First player loses";
	else
		cout << "First player wins flying to airport " << n;

	return 0;
}