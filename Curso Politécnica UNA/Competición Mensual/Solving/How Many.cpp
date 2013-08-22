#include <iostream>
#ifdef DEBUG
#include <sstream>
#include <deque>
#endif

using namespace std;

#define MAX_LENGTH 40
#define MAX_HEIGHT 20
#define MAX_PEAKS 20
#define MAX_HEIGHT_PEAK 20

typedef long long int uint;


#ifdef DEBUG
struct Debug
{
	int call;
	string message;

	Debug () {}
	Debug (int c) : call(c) {}
};

bool operator < (const Debug &d1, const Debug &d2)
{
	return d1.call < d2.call;
}

deque <Debug> debug;

ostream & operator << (ostream &os, const deque <Debug> &v)
{
	deque <Debug>::const_iterator it;
	for( it = v.begin(); it != v.end(); ++it )
	{
		os << it->call << '\t' << it->message << '\n';
	}
	return os;
}
#endif


uint paths (int x, int y, int r, int h)
{
	static uint path[MAX_LENGTH][MAX_HEIGHT][MAX_PEAKS][MAX_HEIGHT_PEAK] = {0};
	static bool updated[MAX_LENGTH][MAX_HEIGHT][MAX_PEAKS][MAX_HEIGHT_PEAK] = {false};

	#ifdef DEBUG
	stringstream ss;
	debug.push_back( Debug() );
	Debug &d = debug.back();
	d.call = debug.size();
	ss << "PATHS"
		<< "\t" << x
		<< "\t" << y
		<< "\t" << r
		<< "\t" << h;
	cerr << d.call << '\t' << ss.str() << '\n';
	#endif

	uint &p = path[x][y][r][h];
	bool &u = updated[x][y][r][h];

	if( x < 0 || y < 0 )
	{
		#ifdef DEBUG
		ss << "\t\t" << 0
			<< "\t(out of range)";
		d.message = ss.str();
		cerr << 'F' << d.call << '\t' << d.message << '\n';
		#endif
		return 0;
	}

	if( u == false )
	{
		const int
			min_x = h + 2 * ( r - 1 ),
			min_diff = min_x + 2 - h,
			min_sum = min_x + h,
			diff_xy = x - y,
			sum_xy = x + y;
		u = true;
		if( diff_xy <= 0 )
		{
			p = diff_xy == 0 && !r;
			#ifdef DEBUG
			ss << "\t\t" << p
				<< "\t(difference 0)";
			#endif
		}
		else if( r && ( diff_xy < min_diff || sum_xy < min_sum ) )
		{
			p = 0;
			#ifdef DEBUG
			ss << "\t\t" << p
				<< "\t(path overflow)"
				<< "\tmin_diff: " << min_diff
				<< "\tmin_sum: " << min_sum;
			#endif
		}
		else
		{
			if( y == h - 1 )
			{
				if( r )
				{
					p += paths( x - 2, y, r - 1, h );
					#ifdef DEBUG
					cerr << '_' << d.call << '\t' << ss.str() << '\n';
					#endif
				}
				p += paths( x - 2, y + 2, r, h );
				#ifdef DEBUG
				cerr << '_' << d.call << '\t' << ss.str() << '\n';
				#endif
			}
			else
			{
				p += paths( x - 1, y + 1, r, h );
				#ifdef DEBUG
				cerr << '_' << d.call << '\t' << ss.str() << '\n';
				#endif
			}
			if( y > 0 )
			{
				p += paths( x - 1, y - 1, r, h );
			}
			#ifdef DEBUG
			ss << "\t\t" << p;
			#endif
		}
	}
	else
	{
		#ifdef DEBUG
		ss << "\t\t" << p
			<< "\t[r]";
		#endif
	}

	#ifdef DEBUG
	d.message = ss.str();
	cerr << 'F' << d.call << '\t' << d.message << '\n';
	#endif
	return p;
}


int main ()
{
	int n, r, k;

	while( !cin.eof() )
	{
		cin >> n >> r >> k;
		#ifdef DEBUG
		cerr << "\nTEST CASE"
			<< "\t" << n
			<< "\t" << r
			<< "\t" << k
			<< "\n\n"
			<< "\t     \tx\ty\tr\th\t\tp\n\n";
		#endif
		cout << paths( n + n, 0, r, k ) << endl;
		#ifdef DEBUG
		cerr << '\n' << debug << '\n';
		#endif
	}

	return 0;
}