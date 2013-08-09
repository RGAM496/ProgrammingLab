#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
using namespace std;

#define MAX_LENGTH 2001
#define UNKNOWN 2002
typedef unsigned int uint;

struct String
{
	char str[MAX_LENGTH];
	uint len;

	inline char & operator [] (uint n) {return str[n];}
};

istream & operator >> (istream &is, String &s)
{
	is >> s.str;
	s.len = strlen( s.str );
	return is;
}


struct Strings
{
	String str_a, str_b;
	uint ED[ MAX_LENGTH ][ MAX_LENGTH ];

	inline void reset ()
	{
		for (uint a = 0; a < str_a.len; ++a)
		{
			for (uint b = 0; b < str_b.len; ++b)
			{
				ED[a][b] = UNKNOWN;
			}
		}
	}

	
	uint edit_distance (uint a, uint b)
	{
		if( !str_a[a] )
			return str_b.len - b;
		if( !str_b[b] )
			return str_a.len - a;

		uint &c = ED[a][b];
		if (c == UNKNOWN)
		{
			c = edit_distance( a + 1, b + 1 );
			if (str_a[a] != str_b[b])
			{
				uint ma, mb;
				ma = edit_distance( a + 1, b );
				mb = edit_distance( a, b + 1 );
				c = min( min( ma, mb ), c ) + 1;
			}
		}
		return c;
	}


	inline uint edit_distance ()
	{
		return edit_distance( 0, 0 );
	}
};


istream & operator >> (istream &is, Strings &s)
{
	is >> s.str_a >> s.str_b;
	s.reset();
	return is;
}


Strings s;


int main ()
{
	uint t;
	cin >> t;
	while (t--)
	{
		cin >> s;
		cout << s.edit_distance() << endl;
	}
	return 0;
}