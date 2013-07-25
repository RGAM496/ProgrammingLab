#include <iostream>
#include <set>
#include <deque>

using namespace std;

struct Segment;
typedef set <Segment> Set;
typedef Set::iteretor Iterator;
typedef deque <Segment> Vector;


struct Segment
{
	int l, r;

	inline bool out_of_range (int min) {
		return r <= min;
	}

	inline bool out_of_range (int min, int max) {
		return r <= min || l >= max;
	}

	inline void set (int i, int j) {
		if (i > j) {
			l = j;
			r = i;
		}
		else {
			l = i;
			r = j;
		}
	}
};


istream & operator >> (istream &is, Segment &seg)
{
	is >> seg.l >> seg.r;
}

ostream & operator << (ostream &os, Segment &seg)
{
	os << seg.l << ' ' << seg.r;
}


inline void purge (Set &s, Iterator &it)
{
	if (it == s.begin ()) {
		s.erase (it);
		it = s.begin ();
	}
	else {
		Iterator it_aux = it;
		--it;
		s.erase (it_aux);
	}
}


inline bool operator < (const Segment &a, const Segment &b)
{
	return a.l < b.l || (a.l == b.l && a.r > b.r);
}


inline bool choose_best (Set &segment, int min, Segment &seg)
{
	Iterator it = set.begin ();
	Segment aux;
	seg = *it;
	if (seg.l > min)
		return false;
	for (++it; it != segment.end(); ++it) 
	{
		aux = *it;
		if (aux.out_of_range (min)) {
			purge (segment, it);
			continue;
		}
		if (aux.l > min)
			break;
		if (seg.r < aux.r)
			seg = aux;
	}

	return true;
}


int main ()
{
	int min, max, test_cases, l, r;
	Segment seg;

	cin >> test_cases;
	while (test_cases--)
	{
		Set segment;
		Vector list;
		min = 0;
		cin >> max;
		while (cin >> seg, seg.l != 0 || seg.r != 0)
		{
			if (seg.l == seg.r || seg.out_of_range (min, max))
				continue;
			seg.set (seg.l, seg.r);
			segment.insert (seg);
		}

		while (min < max)
		{
			if (! choose_best (segment, min, seg)) {
				cout << 0 << '\n';
				break;
			}
			list.push_back (seg);
			segment.erase (seg);
			min = seg.r;

			int size = list.size();
			cout << s << '\n';
			for (int i = 0; i < s; ++i)
				cout << list[i] << '\n';
		}

		if (test_cases)
			cout << '\n';
	}

	return 0;
}