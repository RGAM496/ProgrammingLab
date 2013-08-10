#include <iostream>
#include <cctype>
using namespace std;

#define MAX_LENGTH 5001
#define END -1


int to_number[256];
char to_char[4] = {'p', 'q', 's', 'r'};

struct Region
{

	int c[MAX_LENGTH];
	int length;

	inline int & operator [] (unsigned int i) {return c[i];}
	inline int operator [] (unsigned int i) const {return c[i];}

	inline void operator = (const Region &r)
	{
		length = r.length;
		for( int i = 0; i < length; ++i )
		{
			c[i] = r[i];
		}
	}

	inline void next_up ( Region &r )
	{
		int i;
		r = *this;
		for( i = length - 1; i; --i )
		{
			if( r[i] > 1 )
			{
				r[i] -= 2;
				break;
			}
			else
			{
				r[i] += 2;
			}
		}
		if( i == 0 )
		{
			if( r[i] > 1 )
			{
				r[i] -= 2;
			}
			else
			{
				r[i] = END;
			}
		}
	}

	inline void next_down ( Region &r )
	{
		int i;
		r = *this;
		for( i = length - 1; i; --i )
		{
			if( r[i] < 1 )
			{
				r[i] += 2;
				break;
			}
			else
			{
				r[i] -= 2;
			}
		}
		if( i == 0 )
		{
			if( r[i] < 1 )
			{
				r[i] += 2;
			}
			else
			{
				r[i] = END;
			}
		}
	}

	inline void next_left ( Region &r )
	{
		int i;
		r = *this;
		for( i = length - 1; i; --i )
		{
			if( r[i] % 2 == 1 )
			{
				--r[i];
				break;
			}
			else
			{
				++r[i];
			}
		}
		if( i == 0 )
		{
			if( r[i] % 2 == 1 )
			{
				--r[i];
			}
			else
			{
				r[i] = END;
			}
		}
	}

	inline void next_right ( Region &r )
	{
		int i;
		r = *this;
		for( i = length - 1; i; --i )
		{
			if( r[i] % 2 == 0 )
			{
				++r[i];
				break;
			}
			else
			{
				--r[i];
			}
		}
		if( i == 0 )
		{
			if( r[i] % 2 == 0 )
			{
				++r[i];
			}
			else
			{
				r[i] = END;
			}
		}
	}
};

istream & operator >> ( istream &is, Region &r )
{
	char c;
	do
	{
		c = is.get();
	}
	while( c != 'm' );
	r.length = 0;
	while( c = is.get(), !isspace( c ) )
	{
		r[r.length] = to_number[c];
		++r.length;
	}
	return is;
}

ostream & operator << ( ostream &os, const Region &r )
{
	int i;
	if( r[0] == END )
		os << "<none>";
	else
	{
		os << 'm';
		i = 0;
		do
		{
			os << to_char[ r[i] ];
			++i;
		}
		while( i < r.length );
	}
	return os;
}


inline void init ()
{
	to_number['p'] = 0;
	to_number['q'] = 1;
	to_number['r'] = 3;
	to_number['s'] = 2;
}


Region region, neighbor;


int main ()
{
	int test_cases;

	init();

	cin >> test_cases;
	while( test_cases-- )
	{
		cin >> region;
		region.next_up( neighbor );
		cout << neighbor;
		region.next_down( neighbor );
		cout << ' ' << neighbor;
		region.next_left( neighbor );
		cout << ' ' << neighbor;
		region.next_right( neighbor );
		cout << ' ' << neighbor;
		cout << '\n';
	}

	return 0;
}