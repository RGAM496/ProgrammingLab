#include <iostream>
using namespace std;


struct Vector
{
	int *begin, *end;

	inline int & operator [] (size_t i) {return begin[i];}
	inline int operator [] (size_t i) const {return begin[i];}

	inline int size () const
	{
		return end - begin;
	}
};

bool operator < (const Vector &v1, const Vector &v2)
{
	int s1, s2;
	s1 = v1.size();
	s2 = v2.size();
	if( s1 == s2 )
	{
		const int *i1, *i2;
		i1 = v1.begin;
		i2 = v2.begin;
		while( i1 != v1.end && *i1 == *i2 )
		{
			++i1;
			++i2;
		}
		return i1 != v1.end && *i1 < *i2;
	}
	else
	{
		return s1 < s2;
	}
}


#define MAX_LENGTH 1001
#define MAX_CUTS 52
#define MAX_COST (MAX_CUTS * MAX_LENGTH)
#define UNKNOWN MAX_COST

int cuts[MAX_CUTS], cost[MAX_LENGTH][MAX_LENGTH];
Vector vec = {cuts};

inline void reset (int length)
{
	vec.end = cuts;
	for( int i = 0; i <= length; ++i )
	{
		for( int j = 0; j <= length; ++j )
		{
			cost[i][j] = UNKNOWN;
		}
	}
}


int min_cost (const Vector &v)
{
	int &begin = *v.begin,
		&end = *v.end,
		&cost_value = cost[begin][end];
	if( cost_value == UNKNOWN )
	{
		int cost_base, cost_aux;
		cost_base = end - begin;
		switch( v.size() - 1 )
		{
			case 0:
			{
				cost_value = 0;
				break;
			}
			case 1:
			{
				cost_value = cost_base;
				break;
			}
			default:
			{
				Vector v1, v2;
				v1.begin = v.begin;
				v2.end = v.end;
				cost_value = MAX_COST;
				for( int *p = v.begin + 1; p != v.end; ++p )
				{
					v1.end = v2.begin = p;
					cost_aux = min_cost( v1 ) + min_cost( v2 );
					if( cost_aux < cost_value )
						cost_value = cost_aux;
				}
				cost_value += cost_base;
			}
		}
	}
	return cost_value;
}


int main ()
{
	int length, cuts;

	while( cin >> length, length )
	{
		reset( length );
		cin >> cuts;
		for( int i = 0; i < cuts; ++i )
		{
			cin >> *++vec.end;
		}
		*++vec.end = length;
		cout << "The minimum cutting is " << min_cost( vec ) << ".\n";
	}

	return 0;
}