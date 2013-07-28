#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

#define MAX_SEGMENTS 50000


template <typename N>
inline void set_max (N &a, const N &b)
{
	if (a < b)
		a = b;
}


struct Segment
{
	int start, finish;
};

typedef set <Segment> Set;
typedef Set::iterator Iterator;


inline bool operator < (const Segment &a, const Segment &b)
{
	return (a.start < b.start) || (a.start == b.start && a.finish > b.finish);
}

istream & operator >> (istream &s, Segment &a)
{
	return s >> a.start >> a.finish;
}

ostream & operator << (ostream &s, Segment &a)
{
	return s << a.start << ' ' << a.finish;
}


Segment segment[MAX_SEGMENTS];
int minimum, maximum, n;
Set choosed;


inline int min_subset ()
{
	int count, i;
	Segment f;

	sort (segment, segment + n);
	choosed.clear ();
	minimum = 0;
	if (segment[0].start > minimum)
		return 0;
	minimum = segment[0].finish;
	choosed.insert (segment[0]);

	count = 1;
	if (minimum >= maximum)
		return count;
	for (i = 1; i < n;)
	{
		f.finish = minimum;
		for (; i < n && segment[i].start <= minimum; ++i)
		{
			if (f.finish < segment[i].finish)
				f = segment[i];
		}
		if (f.finish == minimum)
			return 0;
		++count;
		choosed.insert (f);
		if (f.finish >= maximum)
			return count;
		minimum = f.finish;
	}

	return 0;
}


int main ()
{
	int test_cases, subset;
	Segment seg;

	cin >> test_cases;
	while (test_cases--)
	{
		cin >> maximum;
		n = 0;
		while (cin >> seg, seg.start || seg.finish)
		{
			if (seg.finish <= 0)
				continue;
			segment[n] = seg;
			++n;
		}

		subset = min_subset ();
		cout << subset << endl;
		if (subset)
		{
			for (Iterator it = choosed.begin(); it != choosed.end(); ++it)
			{
				seg = *it;
				cout << seg << endl;
				//cout << *it << endl;
			}
		}
		cout << endl;
	}

	return 0;
}