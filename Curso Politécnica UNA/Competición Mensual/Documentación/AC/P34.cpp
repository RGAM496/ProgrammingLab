#include <iostream>
#include <set>
using namespace std;

#define MAX_N 101
#define UNKNOWN 0
typedef set <int> Set;
typedef Set::iterator Iterator;


inline void switch_team ( int &t )
{
	t = 3 - t;
}


struct Node
{
	int team;
	Set friends;

	inline void add_friend( int f ) {
		friends.insert( f );
	}

	inline void delete_friend( int f ) {
		friends.erase( f );
	}
};


struct Graph
{
	Node member[MAX_N];
	int N;

	inline void add_friend( int i, int j ) {
		member[i].add_friend( j );
	}


	void set_teams( int i, int t )
	{
		int j;
		Iterator it;
		Node &mi = member[i];

		mi.team = t;
		switch_team( t );
		while( !mi.friends.empty() )
		{
			it = mi.friends.begin();
			j = *it;
			Node &mj = member[j];
			mi.friends.erase( it );
			mj.delete_friend( i );
			if( mj.team == UNKNOWN )
				set_teams( j, t );
		}
	}

	inline int calculate_teams()
	{
		int count = 0;
		for( int i = 1; i <= N; ++i )
		{
			switch( member[i].team )
			{
				case UNKNOWN:
					set_teams( i, 1 );
				case 1:
					++count;
			}
		}
		return count;
	}
};

Graph graph;


int main ()
{
	int f;
	cin >> graph.N;
	for( int i = 1; i <= graph.N; ++i )
	{
		cin >> f;
		if( f == 0 )
		{
			cout << 0 << endl;
			return 0;
		}
		do
		{
			graph.add_friend( i, f );
			cin >> f;
		}
		while( f );
	}
	cout << graph.calculate_teams() << endl;
	cout << 1;
	for (int i = 2; i <= graph.N; ++i)
	{
		if( graph.member[i].team == 1 )
			cout << ' ' << i;
	}
	cout << endl;

	return 0;
}