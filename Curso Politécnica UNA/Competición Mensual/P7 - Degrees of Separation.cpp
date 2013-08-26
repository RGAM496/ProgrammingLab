#include <iostream>
#include <string>
#include <map>
using namespace std;

#define MAX_P 50
#define INF 1000000
typedef map <string, int> Map;
typedef Map::iterator Iterator;

int graph[MAX_P][MAX_P], P;


inline void floyd ()
{
	int path;
	for (int k = 0; k < P; ++k)
	{
		for (int i = 0; i < P; ++i)
		{
			for (int j = 0; j < P; ++j)
			{
				int &gij = graph[i][j];
				path = graph[i][k] + graph[k][j];
				if( gij > path )
					gij = path;
			}
		}
	}
}


#ifdef DEBUG
inline void debug()
{
	cerr << '\n';
	for (int i = 0; i < P; ++i)
	{
		for (int j = 0; j < P; ++j)
		{
			cerr << '\t' << (graph[i][j] >= INF ? -1 : graph[i][j]);
		}
		cerr << '\n';
	}
	cerr << '\n';
}
#else
#define debug() {}
#endif


struct Index
{
	Map map;
	size_t s;

	Index() : s(0) {}

	inline void clear () {
		s = 0;
		map.clear();
	}

	inline int & operator [] ( const string &str ) {
		pair <Iterator, bool> p;
		Iterator &it = p.first;
		it = map.find( str );
		if( it == map.end() ) {
			pair <string, int> ins( str, s++ );
			p = map.insert( ins );
		}
		return it->second;
	}

	inline int & index( const string &str ) {
		return operator [] ( str );
	}

	inline void add_relationship( const string &str_i, const string &str_j ) {
		size_t i, j;
		i = index( str_i );
		j = index( str_j );
		#ifdef DEBUG
		cerr << "\tindex[\" " << str_i << "\" ]:\t" << i << "\n";
		cerr << "\tindex[\" " << str_j << "\" ]:\t" << j << "\n";
		#endif
		graph[i][j] = graph[j][i] = 1;
	}
};


Index index;


inline void reset ()
{
	index.clear();
	for( int i = 0; i < P; ++i )
	{
		for( int j = 0; j < i; ++j )
		{
			graph[i][j] = INF;
		}
		for( int j = i + 1; j < P; ++j )
		{
			graph[i][j] = INF;
		}
	}
}


int main ()
{
	int R, gij, network;
	string str_i, str_j;

	network = 0;
	while( cin >> P >> R, P || R )
	{
		++network;
		reset();
		debug();
		while( R-- )
		{
			cin >> str_i >> str_j;
			index.add_relationship( str_i, str_j );
		}
		debug();
		floyd();
		debug();
		R = 0;
		for (int i = 0; i < P; ++i)
		{
			for (int j = 0; j < P; ++j)
			{
				gij = graph[i][j];
				if( R < gij)
					R = gij;
			}
		}
		cout << "Network " << network << ": ";
		if( R >= INF )
			cout << "DISCONNECTED\n\n";
		else
			cout << R << "\n\n";
	}

	return 0;
}