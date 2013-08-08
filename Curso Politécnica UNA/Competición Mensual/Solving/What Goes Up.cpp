#include <iostream>
#include <set>
#include <deque>
#include <list>

using namespace std;

#define NP -1


struct Pair
{
	int first, second;
};

inline bool operator < ( const Pair &p, const Pair &q )
{
	return p.first < q.first;
}


typedef deque <Pair> Sequence;
typedef list <int> Subsequence;
typedef set <Pair> Set;
typedef Set::iterator Iterator;


template <typename E>
ostream & operator << (ostream &os, const set <E> &s)
{
	typename set <E>::const_iterator it;
	os << '{';
	if (! s.empty ())
	{
		it = s.begin ();
		os << *it;
		for (++it; it != s.end (); ++it)
			os << ", " << *it;
	}
	os << '}';
	return os;
}

template <typename E>
ostream & operator << (ostream &os, const deque <E> &s)
{
	typename deque <E>::const_iterator it;
	os << '{';
	if (! s.empty ())
	{
		it = s.begin ();
		os << *it;
		for (++it; it != s.end (); ++it)
			os << ", " << *it;
	}
	os << '}';
	return os;
}

ostream & operator << (ostream &os, const Pair &p)
{
	return os << '<' << p.first << ", " << p.second << '>';
}


Sequence seq;
Subsequence l;


inline int lis ()
{
	Set s;
	Iterator it;
	int n = seq.size();
	Pair p;
	int &i = p.second;

	for( i = 0; i < n; ++i )
	{
		p.first = seq[i].first;
		it = s.insert( p ).first;
		if( it != s.begin() )
		{
			Iterator it_aux = it;
			--it_aux;
			seq[i].second = (*it_aux).second;
		}
		if( ++it != s.end() )
			s.erase( it );
	}

	p = *( s.rbegin() );
	do
	{
		p = seq[i];
		l.push_front (p.first);
	}
	while (i != NP);

	return s.size();
}


int main ()
{
	Pair p;
	Subsequence::iterator it;

	p.second = NP;
	while( !cin.eof() )
	{
		cin >> p.first;
		seq.push_back( p );
	}

	cout << lis() << "\n-\n";
	for( it = l.begin(); it != l.end(); ++it )
	{
		cout << *it << '\n';
	}

	return 0;
}