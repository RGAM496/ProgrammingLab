#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_SEGMENTS 100000

typedef int stype;


template <typename N>
inline void set_max (N &a, const N &b)
{
	if (a < b)
		a = b;
}


struct Segment
{
	stype start, finish;
};


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
Segment choosed[MAX_SEGMENTS];
stype minimum, maximum;
int n;


inline int min_subset ()
{
	int count, i;
	Segment f;

	sort (segment, segment + n);
	if (segment[0].start > minimum)
		return 0;

	minimum = 0;
	count = 0;
	for (i = 0; i < n;)
	{
		f.finish = minimum;
		for (; i < n && segment[i].start <= minimum; ++i)
		{
			if (f.finish < segment[i].finish) {
				f = segment[i];
			}
		}
		if (f.finish <= minimum)
			return 0;
		choosed[count] = f;
		++count;
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
		for (int i = 0; i < subset; ++i)
		{
			cout << choosed[i] << endl;
		}
		cout << endl;
	}

	return 0;
}