#include <iostream>
#include <map>
#include <deque>
using namespace std;


typedef deque <int> Vector;
typedef map <Vector, int> Map;
typedef Map::iterator Iterator;
typedef pair <Iterator, bool> Pair;
#define MAX_LENGTH 1000
#define MAX_CUTS 50
#define MAX_STICKS (MAX_CUTS + 1)
#define MAX_COST (MAX_CUTS * MAX_LENGTH)


template <typename E>
inline int sum (const deque <E> &v)
{
	typename deque <E>::const_iterator it;
	int s = 0;
	for( it = v.begin(); it != v.end(); ++it )
	{
		s += *it;
	}
	return s;
}


Vector stick;
Map cost;

inline void reset ()
{
	stick.clear();
}


int min_cost (const Vector &v)
{
	Iterator it;
	it = cost.lower_bound( v );
	if( it == cost.end() || v < it->first ) // Not found.
	{
		int cost_value, cost_base, cost_aux;
		switch( v.size() )
		{
			case 1:
			{
				cost_value = 0;
				break;
			}
			case 2:
			{
				cost_value = v[0] + v[1];
				break;
			}
			default:
			{
				Vector::const_iterator v_it;
				v_it = v.begin();
				++v_it;
				Vector
					v1( v.begin(), v_it ),
					v2( v_it, v.end() );
				cost_base = sum( v );
				cost_value = MAX_COST;
				for( ; v_it != v.end(); ++v_it )
				{
					cost_aux = min_cost( v1 ) + min_cost( v2 );
					if( cost_aux < cost_value )
						cost_value = cost_aux;
					v1.push_back( v2.front() );
					v2.pop_front();
				}
				cost_value += cost_base;
			}
		}
		if( it != cost.begin() )
			--it;
		cost.insert( it, make_pair( v, cost_value ) );
		return cost_value;
	}
	else // Found.
	{
		return it->second;
	}
}


int main ()
{
	int length, cuts, c, c_old;

	while( cin >> length, length )
	{
		cin >> cuts;
		reset();
		c_old = 0;
		for( int i = 0; i < cuts; ++i )
		{
			cin >> c;
			stick.push_back( c - c_old );
			c_old = c;
		}
		stick.push_back( length - c );
		cout << "The minimum cutting is " << min_cost( stick ) << ".\n";
	}

	return 0;
}